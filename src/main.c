#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <complex.h>
#include <string.h>

#include "Vec.h"
#include "Matrix.h"
#include "Image.h"
#include "fft.h"

void main()
{

    //load image
    Image * i0 = Image_import("img/earth.bmp");

    //do treatment on it and save some results
    Matrix ** fR = Matrix_fft(i0->R);
    Matrix ** fG = Matrix_fft(i0->G);
    Matrix ** fB = Matrix_fft(i0->B);

    Matrix * xR = Matrix_ifft(fR);
    Matrix * xG = Matrix_ifft(fG);
    Matrix * xB = Matrix_ifft(fB);

    i0->R = xR;
    i0->G = xG;
    i0->B = xB;

    Image_export(i0, "output_img/testifft.bmp");

    //free memory
    Image_free(i0);
}