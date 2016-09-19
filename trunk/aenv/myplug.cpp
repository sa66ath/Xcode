//-------------------------------------------------------------------------------------------------------
// VST Plug-Ins SDK
// Version 2.4		$Date: 2006/11/13 09:08:27 $
//
// Category     : VST 2.x SDK Samples
// Filename     : myplugin.cpp
// Created by   : Shoichi Ikeda
// Description  : FX Experimental.
// Modified from : again.cpp, Steinberg VST SDK Sample
//
//-------------------------------------------------------------------------------------------------------
#include <algorithm>

#include "public.sdk/source/vst2.x/audioeffectx.h"

#include "benv.h"
#include "param.h"

#include "myplug.h"


//-------------------------------------------------------------------------------------------------------
const char kVendorString[] = "ikeda@roland.co.jp BOSS Corporation";
const char kProductString[] = "Ikeda's Envelope";
const char kEffectName[] = "Envelope";

#define	UNIQ_ID	'TEST'


//==============================================================================
//	Processing Instances
//==============================================================================
BEnvFollow<float>	envFlw(0.01f, 0.5f);

BFilterSVF<float>	filSVF;



//==============================================================================
//	AudioEffect
//==============================================================================
void MyPlug::setSampleRate(float freq)
{
	envFlw.setSampleFreq(freq);
}


//-----------------------------------------------------------------------------------------
void MyPlug::processReplacing (float** inputs, float** outputs, VstInt32 sampleFrames)
{
    float* in1  =  inputs[0];
    float* in2  =  inputs[1];
    float* out1 = outputs[0];
    float* out2 = outputs[1];

    while (--sampleFrames >= 0)
    {
	// L channel
	float in = (*out1++) = (*in1++);
	
	// R channel
	(*in2++);
	
	float cv = fDepth.readout()*in;
	cv = envFlw.process(cv);
	cv = std::min(cv, 1.0f);		
	cv = std::max(cv, 0.0f);		

	cv = (1.f - cv)*fMin.readout() + cv*fMax.readout();	
	
	filSVF.setFreq(cv);

	(*out2++) = filSVF.process(fLevel.getVal()*in);

    }
}

//-----------------------------------------------------------------------------------------
AudioEffect* pEffectInstance;

AudioEffect* createEffectInstance (audioMasterCallback audioMaster)
{
	return	pEffectInstance = new MyPlug (audioMaster);
}

//-------------------------------------------------------------------------------------------------------
MyPlug::MyPlug (audioMasterCallback audioMaster)
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
MyPlug::~MyPlug ()
{
	// nothing to do here
}


//-------------------------------------------------------------------------------------------------------
void MyPlug::setProgramName (char* name)
{
	vst_strncpy (programName, name, kVstMaxProgNameLen);
}

//-----------------------------------------------------------------------------------------
void MyPlug::getProgramName (char* name)
{
	vst_strncpy (name, programName, kVstMaxProgNameLen);
}

//-----------------------------------------------------------------------------------------
void MyPlug::setParameter (VstInt32 index, float value)
{
	param[index]->setVal(value);
}

//-----------------------------------------------------------------------------------------
float MyPlug::getParameter (VstInt32 index)
{
	return param[index]->getVal();
}

//-----------------------------------------------------------------------------------------
void MyPlug::getParameterName (VstInt32 index, char* label)
{
	param[index]->getName(label);
}

//-----------------------------------------------------------------------------------------
void MyPlug::getParameterDisplay (VstInt32 index, char* text)
{
	param[index]->getDisplay (text);
}

//-----------------------------------------------------------------------------------------
void MyPlug::getParameterLabel (VstInt32 index, char* label)
{
	param[index]->getLabel(label);
}

//------------------------------------------------------------------------
bool MyPlug::getEffectName (char* name)
{
	vst_strncpy (name, kEffectName, kVstMaxEffectNameLen);
	return true;
}

//------------------------------------------------------------------------
bool MyPlug::getProductString (char* text)
{
	vst_strncpy (text, kProductString, kVstMaxProductStrLen);
	return true;
}

//------------------------------------------------------------------------
bool MyPlug::getVendorString (char* text)
{
	vst_strncpy (text, kVendorString, kVstMaxVendorStrLen);
	return true;
}

//-----------------------------------------------------------------------------------------
VstInt32 MyPlug::getVendorVersion ()
{ 
	return 1000; 
}

