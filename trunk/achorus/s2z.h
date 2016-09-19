/*==============================================================================
	s2z.h: S -> Z Bi-linear transfer
    		Please refer http://web.boss.rosenet/~ikeda/techdoc/bilinear.pdf
		$Header: /home/boss/ikeda/source/RCS/s2z.h,v 1.1 2004/12/22 00:51:25 ikeda Exp ikeda $
==============================================================================*/	
#ifndef	__S2Z_H
#define	__S2Z_H


//	#define	S2Z_TYPE	double		// or float
#define	S2Z_TYPE	float

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */
/*------------------------------------------------------------------------------
	s2z	S •½–Ê“`’BŠÖ”‚ğ‘oüŒ`•ÏŠ·‚É‚æ‚è Z •½–Ê“`’BŠÖ”‚É•ÏŠ·‚·‚é
	
	parameter	a: s•½–Ê“`’BŠÖ”•ªqŒW””z—ñ		a0+a1s+a2s...+aNs 
				b: s•½–Ê“`’BŠÖ”•ª•êŒW””z—ñ		b0+b1s+b2s...+bNs 
				c: z•½–Ê“`’BŠÖ”•ªqŒW”Ši”[”z—ñ	c0+c1z^-1+c2z^-2....+cNz^-N
				d: z•½–Ê“`’BŠÖ”•ª•êŒW”Ši”[”z—ñ	d0+d1z^-1+d2z^-2....+dNz^-N
				N: Ÿ”		(0...N) 
				T: ƒTƒ“ƒvƒŠƒ“ƒOüŠú  1/Fs	
------------------------------------------------------------------------------*/
extern void s2z (const S2Z_TYPE *a, const S2Z_TYPE *b, S2Z_TYPE *c, S2Z_TYPE *d, int N, S2Z_TYPE T);


/*------------------------------------------------------------------------------
	prewarping	‘oüŒ`•ÏŠ·‚Ì˜c•â³ƒvƒŠƒ[ƒsƒ“ƒO
		
	parameter	wa: ƒAƒiƒƒOŠpü”g” (rad/sec) = 2*pi*freq(Hz)
				T: ƒTƒ“ƒvƒŠƒ“ƒOüŠú  1/Fs	
	return		•â³‚³‚ê‚½Špü”g” (rad/sec)
------------------------------------------------------------------------------*/
extern S2Z_TYPE s2zPrewarping(S2Z_TYPE wa, S2Z_TYPE T);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* __S2Z_H */
/*==============================================================================
	$Log: s2z.h,v $
	Revision 1.1  2004/12/22 00:51:25  ikeda
	Initial revision

	Revision 1.1  2004/12/22 00:29:20  ikeda
	Initial revision

 * Revision 1.1  98/03/20 16:41:26  ikeda
 * Initial revision
 * 
==============================================================================*/	
