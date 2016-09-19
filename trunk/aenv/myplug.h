//-------------------------------------------------------------------------------------------------------
// Category     : VST 2.x SDK Samples
// Filename     : myplug.h
// Created by   : Shoichi Ikeda
// Description  : FX Experimental.
// Modified from : again.h, Steinberg VST SDK Sample
//-------------------------------------------------------------------------------------------------------

#ifndef _MYPLUG_H
#define _MYPLUG_H

#include "public.sdk/source/vst2.x/audioeffectx.h"

#include "bfilter.h"
#include "benv.h"



//-------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------
class MyPlug : public AudioEffectX
{
	void setSampleRate(float freq);
public:
	MyPlug (audioMasterCallback audioMaster);
	~MyPlug ();

	void setupParam();

	// Processing
	virtual void processReplacing (float** inputs, float** outputs, VstInt32 sampleFrames);
//	virtual void processDoubleReplacing (double** inputs, double** outputs, VstInt32 sampleFrames);

	// Program
	virtual void setProgramName (char* name);
	virtual void getProgramName (char* name);

	// Parameters
	virtual void setParameter (VstInt32 index, float value);
	virtual float getParameter (VstInt32 index);
	virtual void getParameterLabel (VstInt32 index, char* label);
	virtual void getParameterDisplay (VstInt32 index, char* text);
	virtual void getParameterName (VstInt32 index, char* text);

	virtual bool getEffectName (char* name);
	virtual bool getVendorString (char* text);
	virtual bool getProductString (char* text);
	virtual VstInt32 getVendorVersion ();

protected:
	char programName[kVstMaxProgNameLen + 1];
};

extern AudioEffect* pEffectInstance;

//==============================================================================
//	Processing Instances
//==============================================================================
extern BEnvFollow<float>	envFlw;

extern BFilterSVF<float>	filSVF;


#endif	/* _MYPLUG_H */
//-------------------------------------------------------------------------------------------------------
//	End 
//-------------------------------------------------------------------------------------------------------
