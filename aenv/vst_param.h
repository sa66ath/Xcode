/*==============================================================================
	vst_param.h: VST Plug-in parameter class for class AudioEffect
					Shoichi Ikeda
==============================================================================*/
#ifndef _VST_PARAM_H
#define _VST_PARAM_H

#include <string>

#include "public.sdk/source/vst2.x/audioeffectx.h"
#include "pluginterfaces/vst2.x/aeffect.h"

#include "myplug.h"	///< for pEffectInstance

	
//------------------------------------------------------------------------------
//	VST Parameter Bass class
//------------------------------------------------------------------------------
class VSTParam {
protected:
	float v;
	std::string label;
	std::string name;
public:
	VSTParam() {}
	VSTParam(const char* label, const char* name) : label(label), name(name) { }

	virtual void 	setVal (float value) { v = value; }
	virtual float 	getVal (void) const { return v; }


	virtual void 	getLabel (char *label) const { vst_strncpy(label, this->label.c_str(), kVstMaxParamStrLen); }
	virtual void 	getName (char *text) const { vst_strncpy(text, this->name.c_str(), kVstMaxParamStrLen); }

	virtual void 	getDisplay (char *text) const { pEffectInstance->float2string(v, text, kVstMaxParamStrLen); }
};


//------------------------------------------------------------------------------
//	VST Parameter has Min, Max
//------------------------------------------------------------------------------
template <class TDATA>
class VSTParamHasMinMax : public VSTParam
{
protected:
	TDATA min;
	TDATA max;

public:
	VSTParamHasMinMax(TDATA min = 0.0, TDATA max = 1.0) : VSTParam("", ""), min(min), max(max) { }
	VSTParamHasMinMax(const char* label, const char* name, TDATA min = 0.0, TDATA max = 1.0) : VSTParam(label, name), min(min), max(max) {}

	void 	getDisplay (char *text) const { pEffectInstance->float2string((float)readout(), text, kVstMaxParamStrLen); }

	virtual TDATA readout() const { return (TDATA)((1.f - v)*min + v*max); }
public:
	virtual void setReadout(TDATA read) { setVal(((float)read - min)/(max - min)); }
};


#endif	/* _VST_PARAM_H */
/*==============================================================================
	End
==============================================================================*/
