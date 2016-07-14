/*==============================================================================
    s2z.c: S -> Z Twin-linear transfer
        $Header: s2z.cpv  1.1  95/06/23 16:08:52  S.Ikeda  Exp $
==============================================================================*/    
#include <stdlib.h>

#include <math.h>
#if !defined(M_PI)
#define M_PI       3.14159265358979323846
#endif	/* M_PI */


#include "s2z.h"

static S2Z_TYPE*  a2c(const S2Z_TYPE* a, S2Z_TYPE* c, const int N, const S2Z_TYPE T);
static void Normalize(S2Z_TYPE* a, S2Z_TYPE* b, int N);

/*------------------------------------------------------------------------------
    parameter   a: s平面伝達関数分子係数配列        a0+a1s+a2s...+aNs 
                b: s平面伝達関数分母係数配列        b0+b1s+b2s...+bNs 
                c: z平面伝達関数分子係数格納配列    c0+c1z^-1+c2z^-2....+cNz^-N
                d: z平面伝達関数分母係数格納配列    d0+d1z^-1+d2z^-2....+dNz^-N
                N: 次数     (0...N) 
                T: サンプリング周期  1/Fs   
------------------------------------------------------------------------------*/
void s2z(const S2Z_TYPE* a, const S2Z_TYPE* b, S2Z_TYPE* c, S2Z_TYPE* d, int N, S2Z_TYPE T)
{
	int n;

	for(n = N; (0.0 == a[n]) && (0.0 == b[n]) && (1 < n); n--) {
		c[n] = 0.0;
		d[n] = 0.0;
	}

        a2c(a, c, n, T); 
        a2c(b, d, n, T); 
        Normalize(c, d, n);
}

//------------------------------------------------------------------------------
static S2Z_TYPE*  a2c(const S2Z_TYPE* a, S2Z_TYPE* c, const int N, const S2Z_TYPE T) 
{
    	S2Z_TYPE* buf = malloc((N+1)*sizeof(S2Z_TYPE));
	int i, j, k, l, m;

	for(i = 0; i <= N; i++)     c[i] = 0.0;

	for(k = 0; k <= N; k++) {
		buf[0] = a[k];
		for(j = 1; j <= N; j++)     buf[j] = 0.0;
		
		for(l = 1; l <= k; l++) { 
			for(m = N; m >= 1; m--) {
				buf[m] += -2.f* buf[m-1];  
				buf[m-1] *= 2.f;  
			}
		}
		for(l = k+1; l <= N; l++) { 
			for(m = N; m >= 1; m--) {
				buf[m] += (T* buf[m-1]);
				buf[m-1] *= T;
			}
		}
		for(i = 0; i <= N; i++)     c[i] += buf[i];     
	}

	free(buf);
	return c;
}


static void Normalize(S2Z_TYPE* a, S2Z_TYPE* b, int N)
{
	int i;

	for(i = N; i >= 0; i--) {
		a[i] /= b[0];
		b[i] /= b[0];
	}

	b[0] = 1.0;
}


/*------------------------------------------------------------------------------
	prewarping	双線形変換時の歪補正プリワーピング
		
	parameter	wa: アナログ角周波数 (rad/sec) = 2*pi*freq(Hz)
				T: サンプリング周期  1/Fs	
	return		補正された角周波数 (rad/sec)
------------------------------------------------------------------------------*/
S2Z_TYPE s2zPrewarping(S2Z_TYPE wa, S2Z_TYPE T)
{
	return 	(S2Z_TYPE)(2.0*tan(wa*T/2.0)/T);
}

//------------------------------------------------------------------------------
//  Debug
//------------------------------------------------------------------------------
#ifdef  MODULE_DEBUG

#include <stdio.h>
#include <stdlib.h>



void NewError()
{
    fprintf(stderr, "Memory not enough\n");
    exit(-1);
}

main()
{

	double	Fs;
	double	t;
	int	N;
	double 	*a;
	double	*b;
	double	*c;
	double	*d;
	int	i;

    printf("Fs=");
    scanf("%lf", &Fs);

    t = 1.0/Fs;
    
    while(printf("demension ="), EOF != scanf("%d", &N)) {
    	a = malloc((N+1)*sizeof(double));
        for(i = 1; i <= N; i++)     a[i] = 0.0;

        for(i = 0; i <= N; i++) {
            printf("a[%d]=", i);
			scanf("%lf", &a[i]);
        }

    	b = malloc((N+1)*sizeof(double));
        for(i = 1; i <= N; i++)     b[i] = 0.0;

        for(i = 0; i <= N; i++) {
            printf("b[%d]=", i);
			scanf("%lf", &b[i]);
        }
        
    	c = malloc((N+1)*sizeof(double));
        for(i = 0; i <= N; i++)         c[i] = 0.0;
            
    	d = malloc((N+1)*sizeof(double));
        for(i = 0; i <= N; i++)         d[i] = 0.0;

        s2z(a, b, c, d, N, t);
        
        for(i = 0; i <= N; i++)     printf("%lf\n", c[i]);
        
        for(i = 0; i <= N; i++)     printf("%lf\n", d[i]);
    
		free(d);    
		free(c);    
		free(b);    
		free(a);    
    }
    
    return 0;
}
#endif  /* MODULE_DEBUG */
/*==============================================================================
    $Log: s2z.cpv $
 * Revision 1.1  95/06/23 16:08:52  S.Ikeda
 * Initial revision
 * 
==============================================================================*/    
