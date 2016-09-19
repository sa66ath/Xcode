/*------------------------------------------------------------------------------
	parameter.cpp: VST Plug-in User parameter 
						ikeda@roland.co.jp
------------------------------------------------------------------------------*/
#include "public.sdk/source/vst2.x/audioeffectx.h"
#include "fx.h"

#include "param.h"


//==============================================================================
//	Parameters
//==============================================================================
VSTParam		chWet("", "WET");
ParamOscFreq		chRate("Hz", "RATE", 0.1f, 3.f);

ParamChorusDepth	chDepth("ms", "DEPTH", 0.f, 0.008f);
ParamChorusPreDelay	chPreDelay("ms", "PREDELAY", 0.f, 0.03f);


VSTParam* param[] = {
	&chRate,
	&chDepth,
	&chPreDelay,

	&chWet,
};

const VstInt32 kNumParams = sizeof(param)/sizeof(param[0]);
//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Fx::setupParam()
{
	chRate.setOscPtr(&oscTri); chRate.setReadout(0.7f);
	chDepth.setReadout(0.005f);
	chPreDelay.setReadout(0.003f);
	chWet.setVal(1.0);
}


/*==============================================================================
	Chorus
==============================================================================*/
//---- DEPTH -----------------------------------------------------------------
ParamChorusDepth::ParamChorusDepth(const char* label, const char* name, float min, float max)
	: VSTParamHasMinMax<float>(label, name, min, max)
{ }

//---- PREDELAY ---------------------------------------------------------------
ParamChorusPreDelay::ParamChorusPreDelay(const char* label, const char* name, float min, float max) : VSTParamHasMinMax<float>(label, name, min, max)
{ }



/*==============================================================================
	OSC	
==============================================================================*/
ParamOscFreq::ParamOscFreq(const char* label, const char* name, float min, float max) : VSTParamHasMinMax<float>(label, name, min, max)
{
	op = 0;
}

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

