//-------------------------------------------------------------------------------------------------------
// VST Plug-Ins SDK
// Version 2.4		$Date: 2006/11/13 09:08:27 $
//
// Category     : VST 2.x SDK Samples
// Filename     : fx.cpp
// Created by   : ikeda@roland.co.jp BOSS Corporation
// Description  : FX Experimental.
// Modified from : again.cpp, Steinberg VST SDK Sample
//
//-------------------------------------------------------------------------------------------------------
#include "bosc.h"

#include "param.h"

#include "fx.h"


//-------------------------------------------------------------------------------------------------------
const char kVendorString[] = "ikeda@roland.co.jp BOSS Corporation";
const char kProductString[] = "Ikeda's OSC";
const char kEffectName[] = "OSC";

#define	UNIQ_ID	'TEST'


//==============================================================================
//	Processing Instances
//==============================================================================
BOscSaw<float> oscL;
BOscSin<float> oscR;

// BOscSawOVS<float, 8>	oscOV;


//==============================================================================
//	AudioEffect
//==============================================================================
void Fx::setSampleRate(float freq)
{
	oscL.setSampleFreq(freq);
	oscR.setSampleFreq(freq);
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
	// L channel
	*in1++;
	(*out1++) = oscLevelL.getVal()*oscL.process();
	

	// R channel
	*in2++;
	(*out2++) = oscLevelR.getVal()*oscR.process();
//	(*out2++) = oscLevelR.getVal()*oscOV.process();

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

