/*------------------------------------------------------------------------------
	parameter.cpp: VST Plug-in User parameter 
						Shoichi Ikeda
------------------------------------------------------------------------------*/
#include "public.sdk/source/vst2.x/audioeffectx.h"

#include "bfilter.h"
#include "myplug.h"

#include "param.h"


//==============================================================================
//	Parameters
//==============================================================================
VSTParamHasMinMax<float>	fDepth("", "DEPTH", 0.0, 100.0);

ParamFilterQ			fReso("Q","REQO", 0.5, 16.0, &filSVF);

VSTParam			fLevel("", "LEVEL");

VSTParamHasMinMax<float>	fMin("Hz", "MIN", 50.0, 500.0);
VSTParamHasMinMax<float>	fMax("Hz", "MAX", 400.0, 4000.0);

ParamEnvAttack	envAttack("sec", "ATTACK", &envFlw);
ParamEnvRelease	envRelease("sec", "RELEASE", &envFlw);


VSTParam* param[] = {
	&fDepth,
 	&fReso,
	&fLevel,

	&envAttack,
	&envRelease,

	&fMin,
	&fMax,
};

const VstInt32 kNumParams = sizeof(param)/sizeof(param[0]);

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MyPlug::setupParam()
{
	fDepth.setReadout(20.0);
	fReso.setReadout(5.0);
	fLevel.setVal(1.0);
	fMin.setReadout(150.0);
	fMax.setReadout(2000.0);

	envAttack.setVal(0.06f);
	envRelease.setVal(0.35f);
}


//==============================================================================
//	ParamFilterPassType	methods
//==============================================================================
BFilter::PassType ParamFilterPassType::val2PassType(float val) const 
{
	int type = (int)(val*(float)(BFilter::kNumOfPassType));

	if((BFilter::kNumOfPassType - 1) < type)	
		type = BFilter::kNumOfPassType - 1; 	

	return (BFilter::PassType)type;
}

//------------------------------------------------------------------------------
void ParamFilterPassType::getDisplay (char *text) const
{
	const char *str;
	switch(val2PassType(v)) {
		case BFilter::kPassTypeAPF:
			str = "APF";
			break;
		case BFilter::kPassTypeHPF:
			str = "HPF";
			break;
		case BFilter::kPassTypeBPF:
			str = "BPF";
			break;
		case BFilter::kPassTypeLPF:
		default:
			str = "LPF";
			break;
	}
	vst_strncpy (text, str, kVstMaxParamStrLen);
}


//------------------------------------------------------------------------------
void ParamFilterPassType::setVal (float value)
{ 
	v = value;
	if(fp)	fp->setPassType(val2PassType(value));
}

//==============================================================================
//	ParamFilterFreq	methods
//==============================================================================
void ParamFilterFreq::getDisplay (char *text) const
{
	pEffectInstance->float2string(readout(), text, kVstMaxParamStrLen);
}

//------------------------------------------------------------------------------
void ParamFilterFreq::setVal(float value)
{ 
	v = value;
	if(fp) fp->setFreq(readout());
}

//==============================================================================
//	ParamFilterQ	methods
//==============================================================================
void ParamFilterQ::getDisplay (char *text) const
{
	pEffectInstance->float2string(readout(), text, kVstMaxParamStrLen);
}

//------------------------------------------------------------------------------
void ParamFilterQ::setVal(float value)
{ 
	v = value;
	if(fp) fp->setQ(readout());
}

