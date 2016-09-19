/*==============================================================================
	param.h: VST Plug-in User parameter 
					Shoichi Ikeda
==============================================================================*/
#ifndef _PARAM_H
#define _PARAM_H

#include "public.sdk/source/vst2.x/audioeffectx.h"
#include "fx.h"

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
//	Filter Pass Type
//------------------------------------------------------------------------------
class ParamFilterPassType : public VSTParam {
	BFilter* fp;

	BFilter::PassType val2PassType(float val) const;

public:
	ParamFilterPassType(const char* label, const char* name, BFilter* fp = 0) : VSTParam(label, name), fp(fp)	{}

	void setFilterPtr(BFilter* p) { fp = p; }
	void getDisplay (char *text) const;
	void setVal (float value);
};


//------------------------------------------------------------------------------
//	Filter Cutoff Frequency
//------------------------------------------------------------------------------
class ParamFilterFreq : public VSTParamHasMinMax<float> {
	BFilter* fp;

public:
	ParamFilterFreq(const char* label, const char* name, float min, float max, BFilter* fp = 0) : VSTParamHasMinMax<float>(label, name, min, max), fp(fp)	{ }

	void setFilterPtr(BFilter* p) { fp = p; }
	void getDisplay (char *text) const;
	void setVal (float value);
};

//------------------------------------------------------------------------------
//	Filter Q (quality factor)
//------------------------------------------------------------------------------
class ParamFilterQ : public VSTParamHasMinMax<float> {
	BFilterIIR2D<float>* fp;

public:
	ParamFilterQ(const char* label, const char* name, float min, float max, BFilterIIR2D<float>* fp = 0) : VSTParamHasMinMax<float>(label, name, min, max), fp(fp)	{}

	void setFilterPtr(BFilterIIR2D<float>* p) { fp = p; }
	void getDisplay (char *text) const;
	void setVal (float value);
};

//==============================================================================
//	Parameters
//==============================================================================
extern ParamGain 		fGain;

extern VSTParam* param[];

extern const VstInt32 kNumParams;

#endif /* _PARAM_H */
/*==============================================================================
	End
==============================================================================*/
