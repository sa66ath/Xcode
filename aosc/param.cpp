/*------------------------------------------------------------------------------
	parameter.cpp: VST Plug-in User parameter 
					Mar. 13th 2012
					Shoichi Ikeda
------------------------------------------------------------------------------*/
#include "public.sdk/source/vst2.x/audioeffectx.h"

#include "fx.h"

#include "param.h"


//==============================================================================
//	Parameters
//==============================================================================
ParamOscFreq		oscFreqL("Hz", "SAW Freq", 20.f, 2000.f, &oscL);
VSTParam 		oscLevelL("", "SAW Lev");

ParamOscFreq		oscFreqR("Hz", "SIN Freq", 20.f, 2000.f, &oscR);
// ParamOscFreq		oscFreqR("Hz", "SIN Freq", 20.f, 2000.f, &oscOV);

VSTParam 		oscLevelR("", "SIN Lev");

VSTParam* param[] = {
	&oscFreqL,
	&oscLevelL,
	
	&oscFreqR,
	&oscLevelR,
};

const VstInt32 kNumParams = sizeof(param)/sizeof(param[0]);
//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Fx::setupParam()
{
	oscFreqL.setReadout(200.0);
	oscLevelL.setVal(0.5);
	
	oscFreqR.setReadout(200.0);
	oscLevelR.setVal(0.5);
}


/*==============================================================================
	OSC	
==============================================================================*/
//------------------------------------------------------------------------------
void ParamOscFreq::getDisplay (char *text) const
{
	pEffectInstance->float2string(readout(), text, kVstMaxParamStrLen);
}

//------------------------------------------------------------------------------
void ParamOscFreq::setVal(float value)
{ 
	v = value;
	if(op) 	op->setFreq(readout());
}

