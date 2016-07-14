/*==============================================================================
	bfilter.h:	Digital Filters
						Shoichi Ikeda
==============================================================================*/
#ifndef	_BFILTER_H
#define	_BFILTER_H

#include <cmath>
#if !defined(M_PI)
#define M_PI       3.14159265358979323846
#endif  /* M_PI */

#include "s2z.h"
#include "ringbuff.h"
#include "fs.h"


/*==============================================================================
	Filter Class
==============================================================================*/
class BFilter 
{
public:
	typedef enum {
		kPassTypeLPF = 0,
		kPassTypeBPF,
		kPassTypeHPF,
		kPassTypeAPF,
		kNumOfPassType,
	} PassType;
private:
	virtual void calcCoef() { };
protected:
	float	freq;
	PassType	passType;
	float freq2wc(float f) { return float(2.0*M_PI)*f; }
public:
	BFilter(PassType pt = kPassTypeLPF, float f = 1000.0) : passType(pt), freq(f)  { calcCoef(); }

	void setSampleFreq(float freq) { calcCoef(); }
	
	virtual void setPassType(PassType type) { passType = type; calcCoef(); }
	virtual void setFreq(float freq) { this->freq = freq; calcCoef(); }

	PassType getPassType() const { return passType; }
	float getFreq() const { return freq; }
	
};


/*------------------------------------------------------------------------------
	class BFilterIIR1D
------------------------------------------------------------------------------*/
template <class TDATA>
class BFilterIIR1D : public BFilter
{
	RingBuff<TDATA, 2> buf;
	float	coef[3];
	void calcCoef()
	{
		if(freq <= 0.0)	return;

		float wc = s2zPrewarping(freq2wc(freq), Fs.getRate());

		float a[2], b[2];	
		float c[2], d[2];	

		switch(passType) {
		case kPassTypeAPF:
			a[0] = wc; a[1] = -1.0;
			b[0] = wc; b[1] = 1.0;
			break;
		case kPassTypeHPF:
			a[0] = 0.0; a[1] = 1.0;
			b[0] = wc;b[1] = 1.0;
			break;
		case kPassTypeLPF:
		default:
			a[0] = wc; a[1] = 0.0;
			b[0] = wc; b[1] = 1.0;
			break;
		}

		s2z(a, b, c, d, 1, Fs.getRate());

		coef[0] = c[0];
		coef[1] = c[1];
		coef[2] = -1.f*d[1];
	}

public:
	BFilterIIR1D(PassType pt = kPassTypeLPF, float f = 1000.0) : BFilter(pt, f) { calcCoef(); }

	TDATA process(TDATA in)
	{
		buf.decBP();

		TDATA 
		acc  = coef[2] * buf[1] + in;
		
		acc  = coef[0] * (buf[0] = acc);
		acc += coef[1] * buf[1];

		return acc;
	}
};

/*------------------------------------------------------------------------------
	class BFilterIIR2D
------------------------------------------------------------------------------*/
template <class TDATA>
class BFilterIIR2D : public BFilter
{
	RingBuff<TDATA, 3> buf;
	float	Q;
	float	coef[5];

	void calcCoef()
	{
		if(freq <= 0.0)	return;
		if(Q <= 0.0)	return;

		float wc = s2zPrewarping(freq2wc(freq), Fs.getRate());

		float a[3], b[3];	
		float c[3], d[3];	

		switch(passType) {
		case kPassTypeAPF:
			a[0] = wc*wc;	a[1] = -wc/Q;	a[2] = 1.0;
			b[0] = wc*wc;	b[1] = wc/Q;	b[2] = 1.0;
			break;
		case kPassTypeHPF:
			a[0] = 0.0;	a[1] = 0.0;	a[2] = 1.0;
			b[0] = wc*wc;	b[1] = wc/Q;	b[2] = 1.0;
			break;
		case kPassTypeBPF:
			a[0] = 0.0;	a[1] = wc/Q;	a[2] = 0.0;
			b[0] = wc*wc;	b[1] = wc/Q;	b[2] = 1.0;
			break;
		case kPassTypeLPF:
		default:
			a[0] = wc*wc;	a[1] = 0.0;	a[2] = 0.0;
			b[0] = wc*wc;	b[1] = wc/Q;	b[2] = 1.0;
			break;
		}

		s2z(a, b, c, d, 2, Fs.getRate());

		coef[0] = c[0];
		coef[1] = c[1];
		coef[2] = c[2];
		coef[3] = -1.f*d[1];
		coef[4] = -1.f*d[2];
	}

public:
	BFilterIIR2D(PassType pt = kPassTypeLPF, float f = 1000.0, float q = 0.707) : BFilter(pt, f), Q(q) { calcCoef(); }

	TDATA process(TDATA in)
	{
		buf.decBP();

		TDATA 
		acc  = coef[3] * buf[1] + in;
		acc += coef[4] * buf[2];

		acc  = coef[0] * (buf[0] = acc);	
		acc += coef[1] * buf[1];
		acc += coef[2] * buf[2];

		return acc;
	}

	void setQ(float q) { Q = q; calcCoef(); }
	float getQ() const { return Q; }
};

/*------------------------------------------------------------------------------
	class BFilterSVF
------------------------------------------------------------------------------*/
template <class TDATA>
class BFilterSVF : public BFilter
{
	TDATA	buf0, buf1;
	TDATA	outLPF, outBPF, outHPF;
	
	float Q;

	float coefFc;
	float coefLPF, coefBPF, coefHPF;
	
	void calcCoef()
	{
		coefFc = float(2.0*M_PI)*sin(freq/Fs.getFreq());

		switch(passType) {
		case kPassTypeLPF:
			coefLPF = 1.0; coefBPF = 0.0; coefHPF = 0.0;
			break;
		case kPassTypeBPF:
			coefLPF = 0.0; coefBPF = 1.0; coefHPF = 0.0;
			break;
		case kPassTypeHPF:
			coefLPF = 0.0; coefBPF = 0.0; coefHPF = 1.0;
			break;
		}
	}
public:
	BFilterSVF(PassType pt = kPassTypeLPF, float f = 500.0, float q = 4.0) : BFilter(pt, f), Q(q) { calcCoef(); }

	void setQ(float q) { Q = q;  }
	float getQ() const { return Q; }

	void setCoefFc(float coef) { coefFc = coef; }

	TDATA process(TDATA in, TDATA* lpfOut, TDATA* bpfOut, TDATA* hpfOut)
	{
		TDATA hpBuf, acc;

		hpBuf = in - buf0/Q - buf1;
		buf0 += coefFc * hpBuf;
		buf1 += coefFc * buf0;

		acc  = coefHPF * (*hpfOut = hpBuf);
		acc += coefBPF * (*bpfOut = buf0);
		acc += coefLPF * (*lpfOut = buf1);

		return acc;
	}

	TDATA process(TDATA in)
	{
		TDATA	lpf, bpf, hpf;
		
		return process(in, &lpf, &bpf, &hpf);
	}

};


#endif	/* _BFILTER_H */
/*==============================================================================
	End
==============================================================================*/
