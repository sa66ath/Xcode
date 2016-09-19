/*==============================================================================
	freq.h:	Frequency and Rate
					Shoichi Ikeda
==============================================================================*/
#ifndef	_FREQ_H
#define	_FREQ_H

template <class TDATA>
class Frequency {
	TDATA freq;
public:
	Frequency(TDATA freq = 1.0) : freq(freq)	{}
	void setFreq(TDATA freq)	{ this->freq = freq; }
	void setRate(TDATA rate)	{ freq = 1.0/rate; }
	
	TDATA getFreq() const { return freq; }
	TDATA getRate() const { return (TDATA)1.0/freq; }
};


#endif	/* _FREQ_H */
/*==============================================================================
	End
==============================================================================*/
