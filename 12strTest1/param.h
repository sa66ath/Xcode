/*==============================================================================
	param.h: VST Plug-in User parameter 
					Shoichi Ikeda
==============================================================================*/
#ifndef _PARAM_H
#define _PARAM_H

#include "public.sdk/source/vst2.x/audioeffectx.h"
#include "myplug.h"

#include "vst_param.h"


//==============================================================================
//	User Defined classes
//==============================================================================
//------------------------------------------------------------------------------
//	Gain
//------------------------------------------------------------------------------
class ParamGain : public VSTParam {
public:
	ParamGain(const char* label, const char* name) : VSTParam(label, name) { }
	void  getDisplay (char *text) const {
		pEffectInstance->dB2string(getVal(), text, kVstMaxParamStrLen);
	}
};


//------------------------------------------------------------------------------
//	Filter Q (quality factor)
//------------------------------------------------------------------------------
class ParamQ : public VSTParamHasMinMax<float> {
	MultiBand*	fp;

public:
	ParamQ(const char* label, const char* name, float min, float max, MultiBand* fp = 0) : VSTParamHasMinMax<float>(label, name, min, max), fp(fp)	{}

	void setFilterPtr(MultiBand* p) { fp = p; }
	void getDisplay (char *text) const
	{
		pEffectInstance->float2string(readout(), text, kVstMaxParamStrLen);
	}

	void setVal (float value)
	{ 
		v = value;
		if(fp) {
			for(std::size_t i = 0; i < sizeof(fp->filter)/sizeof(fp->filter[0]); i++) {
				fp->filter[i].setQ(readout());
				fp->filter2[i].setQ(readout());
			}
		}
	}
};


//==============================================================================
//	Parameters
//==============================================================================
extern VSTParam			paramDry;
extern VSTParam			paramWet;

extern ParamGain	fGain;
extern ParamQ		fQ;

extern VSTParam* params[];

extern const VstInt32 kNumParams;

#endif /* _PARAM_H */
/*==============================================================================
	End
==============================================================================*/
