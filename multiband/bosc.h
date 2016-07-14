/*==============================================================================
	bosc.h:	Oscillator
				ikeda@roland.co.jp
==============================================================================*/
#ifndef	_BOSC_H
#define	_BOSC_H

#include <cmath>
#if !defined(M_PI)
#define M_PI       3.14159265358979323846
#endif  /* M_PI */

#include "fs.h"

//==============================================================================
//	Saw Wave
//==============================================================================
template <class TDATA>
class BOscSaw {
	bool on;
	TDATA phase;
	TDATA val;	
	TDATA delta;
protected:
	TDATA rate;
	void calcDelta() { delta = TDATA(2.0)*Fs.getRate()/rate; }
public:
	BOscSaw(TDATA rate = 1.0/200.0) : rate(rate) { val = 0.0; calcDelta(); }
	virtual void setRate(TDATA rate) {  this->rate = rate; calcDelta(); }
	virtual void setFreq(TDATA freq) {  this->rate = TDATA(1.0)/freq; calcDelta(); }
	virtual void setPhase(TDATA freq) {  this->phase = phase; }
	
	virtual void setSampleFreq(TDATA freq) { calcDelta(); } 


	TDATA getRate() const { return rate; }
	TDATA getFreq() const { return 1.0/rate; }

	virtual TDATA process();
	virtual void restart() { val = phase; }
	
};

//------------------------------------------------------------------------------
template <class Tdata>
Tdata BOscSaw<Tdata>::process(void)
{
	val += delta;
	if(1.0 <= val)	val -= 2.0;

	return val;
}

//==============================================================================
//	Traingle Wave
//==============================================================================
template <class TDATA>
class BOscTri : public BOscSaw<TDATA> 
{
	TDATA saw2tri(TDATA data)
	{
		data *= 2.0;
		if(1.0 <= data) {
			data = TDATA(2.0) - data;
		} else {
			if(data < -1.0) {
				data = TDATA(-2.0) - data;	
			}	
		}
		return data;
	}
public:
	TDATA process(void) { return saw2tri(BOscSaw<TDATA>::process()); }
};

//==============================================================================
//	Square Wave
//==============================================================================
template <class TDATA>
class BOscSqr : public BOscSaw<TDATA> 
{
public:
	TDATA process(void) { return (0.0 <= BOscSaw<TDATA>::process())? TDATA(1.0):TDATA(-1.0); }
};


//==============================================================================
//	Sine Wave
//==============================================================================
template <class TDATA>
class BOscSin : public BOscSaw<TDATA> 
{
public:
	TDATA process(void) { return sin(TDATA(M_PI)*BOscSaw<TDATA>::process()); }
};


#endif	/* _BOSC_H */
/*==============================================================================
	End
==============================================================================*/
