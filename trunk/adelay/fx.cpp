//-------------------------------------------------------------------------------------------------------
// VST Plug-Ins SDK
// Version 2.4		$Date: 2006/11/13 09:08:27 $
//
// Category     : VST 2.x SDK Samples
// Filename     : fx.cpp
// Created by   : Shoichi Ikeda
// Description  : FX Experimental.
// Modified from : again.cpp, Steinberg VST SDK Sample
//
//-------------------------------------------------------------------------------------------------------

#include <cstddef>

#include "public.sdk/source/vst2.x/audioeffectx.h"
#include "fs.h"
#include "bfilter.h"
#include "param.h"

#include "fx.h"


//-------------------------------------------------------------------------------------------------------
const char kVendorString[] = "ikeda@roland.co.jp BOSS Corporation";
const char kProductString[] = "Ikeda's Delay";
const char kEffectName[] = "Delay";

#define	UNIQ_ID	'TEST'


//==============================================================================
//	Processing Instances
//==============================================================================
BFilterIIR1D<float>	dcCut(BFilter::kPassTypeHPF, 5.0);

// RingBuff<float, size_t(1.0*44100.0)>	delayBuf;
RingBuff<float, 44100 >	delayBuf;


//==============================================================================
//	AudioEffect
//==============================================================================
void Fx::setSampleRate(float freq)
{
	dcCut.setSampleFreq(freq);
}


//-----------------------------------------------------------------------------------------
void Fx::processReplacing (float** inputs, float** outputs, VstInt32 sampleFrames)
{
    float* in1  =  inputs[0];
    float* in2  =  inputs[1];
    float* out1 = outputs[0];
    float* out2 = outputs[1];

    while (--sampleFrames >= 0)
    {
 	float dryLch = (*in1++);
 	float dryRch = (*in2++);

	delayBuf.decBP();

	// Calc Read Pointer Address
	size_t rAdrs = static_cast<size_t>(Fs.getFreq()*delayTime.getVal());
	if(rAdrs <= 0)	rAdrs = 1;

	float wet = delayBuf[rAdrs];
	delayBuf[0] = (dryLch + dryRch)/2.f + dcCut.process(delayFeedback.getVal() * wet);
			
	wet *= delayWet.getVal();

	(*out1++) = dryLch + +wet;
	(*out2++) = dryLch + +wet;
    }
}

//-----------------------------------------------------------------------------------------
AudioEffect* pEffectInstance;

AudioEffect* createEffectInstance (audioMasterCallback audioMaster)
{
	return	pEffectInstance = new Fx (audioMaster);
}

//-------------------------------------------------------------------------------------------------------
Fx::Fx (audioMasterCallback audioMaster)
: AudioEffectX (audioMaster, 1, kNumParams)
{
	setNumInputs (2);		// stereo in
	setNumOutputs (2);		// stereo out
	setUniqueID (UNIQ_ID);	// identify
	canProcessReplacing ();	// supports replacing output
//	canDoubleReplacing ();	// supports double precision processing

	vst_strncpy (programName, "Default", kVstMaxProgNameLen);	// default program name

	setupParam();
}

//-------------------------------------------------------------------------------------------------------
Fx::~Fx ()
{
	// nothing to do here
}


//-------------------------------------------------------------------------------------------------------
void Fx::setProgramName (char* name)
{
	vst_strncpy (programName, name, kVstMaxProgNameLen);
}

//-----------------------------------------------------------------------------------------
void Fx::getProgramName (char* name)
{
	vst_strncpy (name, programName, kVstMaxProgNameLen);
}

//-----------------------------------------------------------------------------------------
void Fx::setParameter (VstInt32 index, float value)
{
	param[index]->setVal(value);
}

//-----------------------------------------------------------------------------------------
float Fx::getParameter (VstInt32 index)
{
	return param[index]->getVal();
}

//-----------------------------------------------------------------------------------------
void Fx::getParameterName (VstInt32 index, char* label)
{
	param[index]->getName(label);
}

//-----------------------------------------------------------------------------------------
void Fx::getParameterDisplay (VstInt32 index, char* text)
{
	param[index]->getDisplay (text);
}

//-----------------------------------------------------------------------------------------
void Fx::getParameterLabel (VstInt32 index, char* label)
{
	param[index]->getLabel(label);
}

//------------------------------------------------------------------------
bool Fx::getEffectName (char* name)
{
	vst_strncpy (name, kEffectName, kVstMaxEffectNameLen);
	return true;
}

//------------------------------------------------------------------------
bool Fx::getProductString (char* text)
{
	vst_strncpy (text, kProductString, kVstMaxProductStrLen);
	return true;
}

//------------------------------------------------------------------------
bool Fx::getVendorString (char* text)
{
	vst_strncpy (text, kVendorString, kVstMaxVendorStrLen);
	return true;
}

//-----------------------------------------------------------------------------------------
VstInt32 Fx::getVendorVersion ()
{ 
	return 1000; 
}

