/**
 * @file fft.h
 * @brief fft header (Cooley-Tuckey)
 * @author Antony Madaleno
 * @version 1.0
 * @date 12-01-2023
 *
 *
 */


#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

unsigned int reverseBit(unsigned int n, unsigned char bitsize);

float complex * fft( float complex * buf, unsigned int n);

float complex * ifft( float complex * buf, unsigned int n);