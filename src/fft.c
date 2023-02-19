/**
 * @file fft.c
 * @brief fft implementation (Cooley-Tuckey)
 * @author Antony Madaleno
 * @version 1.0
 * @date 20-01-2023
 *
 *
 */

#include "fft.h"

unsigned int reverseBit(unsigned int n, unsigned char bitsize)
{
    unsigned int reversed = 0;

    for (unsigned char i = 0; i < bitsize-1; i++)
        if ( n & (1 << i) )
            reversed |= 1 << bitsize - i - 1;

    return reversed;
}

float complex * fft(float complex * data, unsigned int n)
{

    if (n == 1)
        return data;

    unsigned int m = n / 2;

    float complex * XE = (float complex *) calloc( m, sizeof(float complex) );
    float complex * XO = (float complex *) calloc( m, sizeof(float complex) );

    for (unsigned int i = 0; i < m; i++)
    {
        XE[i] = data[2*i];
        XO[i] = data[2*i + 1];
    }

    float complex * FE = fft(XE, m);
    float complex * FO = fft(XO, m);

    float complex * F = (float complex *) calloc( n, sizeof(float complex) );

    for (int k = 0; k < m; k++)
    {
        double complex w = ( cosf(-2*M_PI*k/n) + I * sinf(-2*M_PI*k/n) ) * FO[k];

        F[k] = FE[k] + w;
        F[k+m] = FE[k] - w;
    }

    return F;
    
}

float complex * ifft(float complex * data, unsigned int n)
{
    for (unsigned int k = 0; k < n; k++)
        data[k] = cimagf(data[k]) + I*crealf(data[k]);

    float complex * X = (float complex *) calloc( n, sizeof(float complex) );

    X = fft(data, n);

    for (unsigned int k = 0; k < n; k++)
    {
        X[k] = (cimagf(X[k]) + I*crealf(X[k]))/n;
    }
        

    return X;
}