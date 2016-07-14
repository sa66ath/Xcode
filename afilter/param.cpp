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
ParamGain 		fGain("dB", "GAIN");

ParamFilterPassType	fPassType("", "Filter Type", &fil2D);
ParamFilterFreq		fFreq("Hz", "Frequency", 100.0, 2000.0, &fil2D);
ParamFilterQ		fQ("","Q", 0.5, 8.0, &fil2D);


VSTParam* param[] = {
 	&fPassType,
 	&fFreq,
 	&fQ,
	
	&fGain,
};

const VstInt32 kNumParams = sizeof(param)/sizeof(param[0]);

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Fx::setupParam()
{
	fPassType.setVal(0.0);
	fFreq.setReadout(1000.0);
	fQ.setReadout(4.0);
	
	fGain.setVal(1.0);
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

