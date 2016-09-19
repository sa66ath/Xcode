//------------------------------------------------------------------------------
//	benv.h:	Envelope
//				Shoichi Ikeda
//------------------------------------------------------------------------------
#ifndef	_BENV_H
#define	_BENV_H

#include <cmath>
#if !defined(M_E)
#define M_E         2.7182818284590452354
#endif  /* M_E */

#include "fs.h"

template <class TDATA>		///< TDATA=float or double
class BEnvFollow {
	TDATA	env;

	float	attack;
	float	release;

	float	coefAttack[2];
	float	coefRelease;

	float	calcFeedback(float time) { return pow(float(1.0/M_E), Fs.getRate()/time); }
public:
	BEnvFollow(float attack = 0.07f, float release = 0.4f) : attack(attack), release(release)
	{
		setAttack(attack); setRelease(release);
	} 

	void setAttack(float time)
	{
		attack = time;
		coefAttack[1] = calcFeedback(time);
		coefAttack[0] = 1.f - coefAttack[1];
	}	

	void setRelease(float time)
	{
		release = time;
		coefRelease = calcFeedback(release);
	}

	void setSampleFreq(float freq)
	{
		setAttack(attack);	
		setRelease(release);	
	}

	TDATA process(TDATA in)
	{
		TDATA tmp = fabs(in);
		if(env <= tmp) {
			env = coefAttack[0]*tmp + coefAttack[1]*env;
		} else {
			env *= coefRelease;
		}	

		return env;
	}
};




#endif	/* _BENV_H */
//------------------------------------------------------------------------------
//	End	
//------------------------------------------------------------------------------
