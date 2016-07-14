/*==============================================================================
	param.h: VST Plug-in User parameter 
					Shoichi Ikeda
==============================================================================*/
#ifndef _PARAM_H
#define _PARAM_H

#include "public.sdk/source/vst2.x/audioeffectx.h"
#include "fx.h"

#include "vst_param.h"


extern float	coefDepth;
extern float	coefPreDelay;

//==============================================================================
//	User Defined classes
//==============================================================================
#include "bosc.h"
//------------------------------------------------------------------------------
//	Chorus DEPTH
//------------------------------------------------------------------------------
class ParamChorusDepth : public VSTParamHasMinMax<float> {
public:
	ParamChorusDepth(const char* label, const char* name, float min, float max);
	void getDisplay (char *text) const 
	{
		pEffectInstance->float2string(1000.f*readout(), text, kVstMaxParamStrLen);
	}
	void calcCoef() { coefDepth = Fs.rate2nsample(readout()); }
	void setVal(float value) { v = value; calcCoef(); }
};

//------------------------------------------------------------------------------
//	Chorus PREDELAY
//------------------------------------------------------------------------------
class ParamChorusPreDelay : public VSTParamHasMinMax<float> {
public:
	ParamChorusPreDelay(const char* label, const char* name, float min, float max);
	void getDisplay (char *text) const 
	{
		pEffectInstance->float2string(1000.f*readout(), text, kVstMaxParamStrLen);
	}
	void calcCoef() { coefPreDelay = Fs.rate2nsample(readout()); }
	void setVal(float value) { v = value; calcCoef(); }
};

//------------------------------------------------------------------------------
//	Chorus RATE
//------------------------------------------------------------------------------
class ParamOscFreq : public VSTParamHasMinMax<float> {
	BOscSaw<float>*	op; 
public:
	ParamOscFreq(const char* label, const char* name, float min, float max);
	void setOscPtr(BOscSaw<float>* p) { op = p; }
	void getDisplay (char *text) const;
	void setVal(float value);
};




//==============================================================================
//	Parameters
//==============================================================================
extern ParamOscFreq		chRate;
extern ParamChorusDepth		chDepth;
extern ParamChorusPreDelay	chPreDelay;
extern VSTParam			chWet;

extern VSTParam* param[];

extern const VstInt32 kNumParams;

#endif /* _PARAM_H */
/*==============================================================================
	End
==============================================================================*/
