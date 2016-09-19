/*==============================================================================
	param.h: VST Plug-in User parameter 
					Shoichi Ikeda
==============================================================================*/
#ifndef _PARAM_H
#define _PARAM_H

#include "public.sdk/source/vst2.x/audioeffectx.h"

#include "vst_param.h"

//==============================================================================
//	User Defined classes
//==============================================================================
class ParamShift:public VSTParamHasMinMax<float>
{
public:
	ParamShift(const char* label, const char* name, float min, float max) : VSTParamHasMinMax<float>(label, name, min, max) {}
	void 	setVal (float value)
	{
		VSTParamHasMinMax<float>::setVal(value);
		psLFO.setCent(readout());		
	}
};

//==============================================================================
//	Parameters
//==============================================================================

extern VSTParam* param[];

extern const VstInt32 kNumParams;

#endif /* _PARAM_H */
/*==============================================================================
	End
==============================================================================*/
