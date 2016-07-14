//-------------------------------------------------------------------------------------------------------
// Category     : VST 2.x SDK Samples
// Filename     : myplug.h
// Created by   : Shoichi Ikeda
// Description  : FX Experimental.
// Modified from : myplug.h, Steinberg VST SDK Sample
//-------------------------------------------------------------------------------------------------------

#ifndef _MYPLUGIN_H
#define _MYPLUGIN_H

#include <vector>

#include "public.sdk/source/vst2.x/audioeffectx.h"

#include "ringbuff.h"
#include "bfilter.h"
#include "bpitch_shift.h"



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
const size_t	kNumOfBand = 72;

class MultiBand {
public:
//	std::vector<BFilterIIR2D<float>>	filter;
	BPitchShift<float, 44100>		ps[kNumOfBand]; 
	BFilterIIR2D<float>			filter[kNumOfBand];
	BFilterIIR2D<float>			filter2[kNumOfBand];
	BOscSin<float>				oscChorus;

	bool	bypass;

	int 	loPitch;
	float	loFine;
	float	loLevel;	
	
	size_t	loHiBand;
	
	int 	hiPitch;
	float	hiFine;
	float	hiLevel;	
	
	float	preDelay;

	float	ringLen;

	float	chorusPreDelaySample;
	float	chorusDepthSample;
private:
	float ringSample[kNumOfBand];
	void calcCent();
	void calcRing();
public:
	MultiBand();
	void setupProcessing();
	void setSampleFreq(float freq);
	float process(float in);
}; 

extern MultiBand	multiBand;

#endif	/* _MYPLUGIN_H */
//-------------------------------------------------------------------------------------------------------
//	End 
//-------------------------------------------------------------------------------------------------------
