//------------------------------------------------------------------------------
//	bpitch_shift
//					Shoichi Ikeda
//------------------------------------------------------------------------------
#ifndef	_BPITCH_SHIT_H
#define	_BPITCH_SHIT_H

#include <cmath>
#include "bosc.h"
#include "ringbuff.h"

//==============================================================================
template <class TDATA>
class BPitchShiftLFO 
{
	BOscSaw<TDATA>	lfo;
	float		ringSample;
	float		delta;
	float		rate;
	float		cent;

	TDATA invertLFO(TDATA in)
	{
		const TDATA offset = 1.0; const TDATA max = 1.0;

		TDATA out = in + offset;
		if(max <= out)	out -= (max + max);
		
		return out;
	}

	TDATA tri(TDATA in)
	{
		in += TDATA(1.0);
		if(1.0 <= in)	in = TDATA(2.0) - in;
		
		return in;
	}
	
	void calc()
	{
		delta = 1.f - pow(2.f, cent/1200.f);
	
		if(0.0 == delta)	return;

		rate = fabs(ringSample/Fs.getFreq()/delta);

		lfo.setRate(rate);
	}
public:
	BPitchShiftLFO(float ringSample = 44100/10, float cent = 1200.f) : ringSample(ringSample), cent(cent)
	{ 
	}

	void setCent(float cent)
	{
		this->cent = cent;
		calc();
	}

	void setRingSample(float sample)
	{
		ringSample = sample;
		calc();
	}


	void setSampleFreq(float freq)
	{
		calc();
	}

	void process(TDATA* adrs0, TDATA* fade0, TDATA* adrs1, TDATA* fade1)
	{
		TDATA saw0 = lfo.process();
		TDATA saw1 = invertLFO(saw0);
		TDATA tri0 = tri(saw0);
		TDATA tri1 = tri(saw1);

		saw0 = TDATA(0.5)*(saw0 + TDATA(1.0));
		if(delta < 0) { saw0 = -saw0 + TDATA(1.0); } 
		*adrs0 = saw0 * ringSample;

		saw1 = TDATA(0.5)*(saw1 + TDATA(1.0));
		if(delta < 0) { saw1 = -saw1 + TDATA(1.0); } 
		*adrs1 = saw1 * ringSample;

		*fade0 = tri0;
		*fade1 = tri1;
	}
};


//==============================================================================
template <class TDATA, std::size_t ringSize>
class BPitchShift : public BPitchShiftLFO<TDATA>
{
	RingBuff<TDATA, ringSize>	buf;
	float	preDelaySample;
public:
	BPitchShift(float ringSample = float(ringSize), float cent = 1200.f, float preDelaySample = 0.f) : BPitchShiftLFO<TDATA>(ringSample, cent), preDelaySample(preDelaySample) {}

	TDATA process(TDATA in)
	{
		buf.decBP();
		buf[0] = in;
		
		float adrs0, adrs1;
		float fade0, fade1;
		BPitchShiftLFO<TDATA>::process(&adrs0, &fade0, &adrs1, &fade1);

		return fade0*buf.lerpRead(adrs0 + preDelaySample) + fade1*buf.lerpRead(adrs1 + preDelaySample);
	}
};

#endif	/* _BPITCH_SHIT_H */
//------------------------------------------------------------------------------
//	End
//------------------------------------------------------------------------------
