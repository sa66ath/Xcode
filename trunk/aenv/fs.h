/*==============================================================================
	fs.h:	Sampling Frequency
			Shoichi Ikeda
==============================================================================*/
#ifndef	_FS_H
#define	_FS_H

#include "public.sdk/source/vst2.x/audioeffectx.h"
extern AudioEffect* pEffectInstance;

class FreqSample {
	float freq;
public:
	FreqSample(float freq = 44100.0) : freq(freq) {}

	float getFreq() const
	{
		if(pEffectInstance)	return pEffectInstance->getSampleRate();
		else			return freq;
	}

	float getRate() const 
	{
		if(pEffectInstance)	return 1.f/pEffectInstance->getSampleRate();
		else			return 1.f/freq;
	}

	float rate2nsample(float rate) { return rate/getRate(); }
	float freq2nsample(float freq) { return getFreq()/freq; }
};



extern FreqSample Fs;

#endif	/* _FS_H */
/*==============================================================================
	End
==============================================================================*/
