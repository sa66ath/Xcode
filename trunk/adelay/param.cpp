/*------------------------------------------------------------------------------
	parameter.cpp: VST Plug-in User parameter 
						Shoichi Ikeda
------------------------------------------------------------------------------*/
#include "public.sdk/source/vst2.x/audioeffectx.h"

#include "bfilter.h"
#include "fx.h"

#include "param.h"


//==============================================================================
//	Parameters
//==============================================================================
VSTParam	delayTime("sec", "TIME");
VSTParam	delayFeedback("", "FEEDBACK");
VSTParam 	delayWet("dB", "WET");


VSTParam* param[] = {
 	&delayTime,
 	&delayFeedback,
 	&delayWet,
};

const VstInt32 kNumParams = sizeof(param)/sizeof(param[0]);

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Fx::setupParam()
{
	delayTime.setVal(0.34f);
	delayFeedback.setVal(0.3f);
	delayWet.setVal(0.5);
}


