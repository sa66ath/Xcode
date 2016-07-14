/*==============================================================================
	RingBuff Class
==============================================================================*/
#ifndef	_RINGBUFF_H
#define	_RINGBUFF_H

#include <cstddef>
#include <cmath>

template <class TDATA, size_t sz>		///< TDATA is double or float
class RingBuff {
	TDATA buf[sz];
	size_t bp;
public:

	void decBP(void) { bp--; }
	void IncBP(void) { bp++; }
	
	size_t size(void) const { return sz; }

	//------------------------------------------------------------------------------
	///	 Reading with Linear interpolation
	///
	///	@param adrs	read pointer address as floating point 
	///	@return	read data
	//------------------------------------------------------------------------------
	TDATA lerpRead(TDATA adrs) const	// Reading with Linear interpolation
	{
		TDATA intPart;
		TDATA fracPart = std::modf(adrs, &intPart);
		size_t iAdrs = static_cast<size_t>(intPart);

		return (TDATA(1.0)-fracPart)*buf[(bp+iAdrs)%sz] + fracPart*buf[(bp+iAdrs+1)%sz];
	}

//	TDATA operator[](float adrs) const { return lerpRead(adrs); }
	TDATA& operator[](size_t i) { return buf[(bp+i)%sz]; }
};

#endif	/* _RINGBUFF_H */
/*==============================================================================
	End
==============================================================================*/
