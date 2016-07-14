/*==============================================================================
	freq.h:	Frequency and Rate
					Shoichi Ikeda
==============================================================================*/
#ifndef	_FREQ_H
#define	_FREQ_H

template <class T>
class Frequency {
	T freq;
public:
	Frequency(T freq = 1.0) : freq(freq)	{}
	void setFreq(T freq)	{ this->freq = freq; }
	void setRate(T rate)	{ freq = 1.0/rate; }
	
	T getFreq() const { return freq; }
	T getRate() const { return (T)1.0/freq; }
};


#endif	/* _FREQ_H */
/*==============================================================================
	End
==============================================================================*/
