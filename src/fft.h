#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

unsigned int reverseBit(unsigned int n, unsigned char bitsize);

float complex * fft( float complex * buf, unsigned int n);

float complex * ifft( float complex * buf, unsigned int n);