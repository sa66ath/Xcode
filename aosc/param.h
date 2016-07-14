/*==============================================================================
	param.h: VST Plug-in User parameter 
					Shoichi Ikeda
==============================================================================*/
#ifndef _PARAM_H
#define _PARAM_H

#include "public.sdk/source/vst2.x/audioeffectx.h"
#include "fx.h"
#include "bosc.h"

#include "vst_param.h"

//==============================================================================
//	User Defined classes
//==============================================================================
//------------------------------------------------------------------------------
//	Oscillator Frequency
//------------------------------------------------------------------------------
class ParamOscFreq : public VSTParamHasMinMax<float> {
	BOscSaw<float>*	op; 
public:
	ParamOscFreq(const char* label, const char* name, float min, float max, BOscSaw<float>* op = 0): VSTParamHasMinMax<float>(label, name, min, max), op(op)	{}
	void setOscPtr(BOscSaw<float>* p) { op = p; }
	void getDisplay (char *text) const;
	void setVal(float value);
};



//==============================================================================
//	Parameters
//==============================================================================
extern VSTParam 		oscLevelL;
extern VSTParam 		oscLevelR;

extern VSTParam* param[];

extern const VstInt32 kNumParams;

#endif /* _PARAM_H */
/*==============================================================================
	End
==============================================================================*/
