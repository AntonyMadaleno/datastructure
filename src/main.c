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
    Image * h0 = Image_histoBMP(i0, 1280, 900);
    Image_export(h0, "output_img/histo.bmp");
    Image_free(h0);
    Image * h1 = Image_histoCumulatifBMP(i0, 1280, 900);
    Image_export(h1, "output_img/histoCumulatif.bmp");
    Image_free(h1);

    Image ** F = Image_applyFFT(i0);
    Image_free(i0);

    Image * i1 = Image_applyIFFT(F);
    Image_export(i1, "output_img/ifftout.bmp");
    Image_free(i1);

    Image * i2 = Image_extend(F[0]);
    Image * i3 = Image_extend(F[1]);

    Image_export(i2, "output_img/fftreal.bmp");
    Image_export(i3, "output_img/fftimag.bmp");

    Image_free(i2);
    Image_free(i3);
}