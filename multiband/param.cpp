/*------------------------------------------------------------------------------
	parameter.cpp: VST Plug-in User parameter 
						Shoichi Ikeda
------------------------------------------------------------------------------*/
#include "public.sdk/source/vst2.x/audioeffectx.h"

#include "bfilter.h"
#include "myplug.h"

#include "param.h"


//==============================================================================
//	Parameter Definitions
//==============================================================================

VSTParam			paramDry("x", "DRY");
VSTParam			paramWet("x", "WET");

//------------------------------------------------------------------------------
class ParamChorusRate : public VSTParamHasMinMax<float> {
public:
	ParamChorusRate(const char* label, const char* name, float min, float max) : VSTParamHasMinMax<float>(label, name, min, max) {}
	void setVal(float value)
	{ 
		v = value;
		multiBand.oscChorus.setFreq(readout());
	}
} paramChorusRate("Hz", "RATE", 0.1f, 10.f);


class ParamChorusDepth : public VSTParamHasMinMax<float> {
public:
	ParamChorusDepth(const char* label, const char* name, float min, float max) : VSTParamHasMinMax<float>(label, name, min, max) {}
	void setVal(float value)
	{ 
		v = value;
		multiBand.chorusDepthSample = Fs.getFreq()*readout();
	}
} paramChorusDepth("ms", "DEPTH", 0.f, 0.008f);

//------------------------------------------------------------------------------
class ParamLoPitch : public VSTParamHasMinMax<int>
{
public:
	ParamLoPitch(const char* label, const char* name, int min, int max) : VSTParamHasMinMax<int>(label, name, min, max) {}
	void setVal (float value)
	{
		VSTParamHasMinMax<int>::setVal(value);
		multiBand.loPitch = readout();
		multiBand.setupProcessing();
	}
} paramLoPitch("semitone", "LO PITCH", -12, +12);


//------------------------------------------------------------------------------
class ParamLoFine : public VSTParamHasMinMax<float>	
{
public:
	ParamLoFine(const char* label, const char* name, float min, float max) : VSTParamHasMinMax<float>(label, name, min, max) {}
	void setVal (float value)
	{
		VSTParamHasMinMax<float>::setVal(value);
		multiBand.loFine = readout();
		multiBand.setupProcessing();
	}
} paramLoFine("cent", "LO FINE", -100.0, +100.0);

//------------------------------------------------------------------------------
class ParamPreDelay : public VSTParamHasMinMax<float>
{
public:
	ParamPreDelay(const char* label, const char* name, float min, float max) : VSTParamHasMinMax<float>(label, name, min, max) {}

	void setVal (float value)
	{
		VSTParamHasMinMax<float>::setVal(value);
		multiBand.preDelay = readout();
		multiBand.chorusPreDelaySample = Fs.getFreq()*readout();
		multiBand.setupProcessing();
	}
} paramPreDelay("sec", "PRE DLY", 0.0, 0.05f);


//------------------------------------------------------------------------------
class ParamLoLevel : public VSTParam
{
public:
	ParamLoLevel(const char* label, const char* name) : VSTParam(label, name) {}
	void setVal (float value)
	{
		VSTParam::setVal(multiBand.loLevel = value);
	}

} paramLoLevel("x", "LO LEVEL");

//------------------------------------------------------------------------------
class ParamLoHiBnad : public VSTParamHasMinMax<size_t>
{
public:
	ParamLoHiBnad(const char* label, const char* name, size_t min, size_t max) : VSTParamHasMinMax<size_t>(label, name, min, max) {}
	void setVal (float value)
	{
		VSTParamHasMinMax<size_t>::setVal(value);
		multiBand.loHiBand = readout();
		multiBand.setupProcessing();
	}
} paramLoHiBand("#", "LoHiBAND", 1, 100);


//------------------------------------------------------------------------------
class ParamHiPitch : public VSTParamHasMinMax<int>
{
public:
	ParamHiPitch(const char* label, const char* name, int min, int max) : VSTParamHasMinMax<int>(label, name, min, max) {}
	void setVal (float value)
	{
		VSTParamHasMinMax<int>::setVal(value);
		multiBand.hiPitch = readout();
		multiBand.setupProcessing();
	}
} paramHiPitch("semitone", "HI PITCH", -12, +12);


//------------------------------------------------------------------------------
class ParamHiFine : public VSTParamHasMinMax<float>	
{
public:
	ParamHiFine(const char* label, const char* name, float min, float max) : VSTParamHasMinMax<float>(label, name, min, max) {}
	void setVal (float value)
	{
		VSTParamHasMinMax<float>::setVal(value);
		multiBand.hiFine = readout();
		multiBand.setupProcessing();
	}
} paramHiFine("cent", "HI FINE", -100.0, +100.0);


//------------------------------------------------------------------------------
class ParamHiLevel : public VSTParam
{
public:
	ParamHiLevel(const char* label, const char* name) : VSTParam(label, name) {}

	void setVal (float value)
	{
		VSTParam::setVal(multiBand.hiLevel = value);
	}

} paramHiLevel("x", "HI LEVEL");


//------------------------------------------------------------------------------
class ParamRingLen : public VSTParamHasMinMax<size_t>
{
public:
	ParamRingLen(const char* label, const char* name, size_t min, size_t max) : VSTParamHasMinMax<size_t>(label, name, min, max) {}
	void setVal (float value)
	{
		VSTParamHasMinMax<size_t>::setVal(value);
		multiBand.ringLen = static_cast<float>(readout());
		multiBand.setupProcessing();
	}
} paramRingLen("waves", "RING LEN", 2, 30);




ParamGain			fGain("dB", "BPF GAIN"); 
ParamQ				fQ("Q","BPF RESO", 0.5f, 50.f, &multiBand);


//==============================================================================
//	Parameters Setup
//==============================================================================
VSTParam* params[] = {
	&paramDry,
	&paramWet,

	&paramLoLevel,

	&paramLoHiBand,

	&paramHiLevel,

	&paramChorusRate,
	&paramChorusDepth,
	&paramPreDelay,

	&fQ,
	&fGain,
};

const VstInt32 kNumParams = sizeof(params)/sizeof(params[0]);

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MyPlug::setupParam()
{
	paramDry.setVal(1.f);
	paramWet.setVal(1.f);
	
	paramLoLevel.setVal(1.0f);

	paramLoHiBand.setReadout(62);
	
	paramHiLevel.setVal(0.0f);

	paramChorusRate.setReadout(0.25f);
	paramChorusDepth.setReadout(0.004f);
	paramPreDelay.setReadout(0.010f);

	fQ.setReadout(20.0);
	fGain.setVal(1.0);
}
