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
    Image * i0 = Image_import("img/city.bmp");
    Image * h0 = Image_histoBMP(i0, 1280, 900);
    Image_export(h0, "output_img/histo.bmp");
    Image_free(h0);
    Image * h1 = Image_histoCumulatifBMP(i0, 1280, 900);
    Image_export(h1, "output_img/histoCumulatif.bmp");
    Image_free(h1);

    //EGALISATION
    Image * i3 = Image_equalize(i0);
    Image_export(i3, "output_img/equalized.bmp");

    Image * h2 = Image_histoBMP(i3, 1280, 900);
    Image_export(h2, "output_img/equalized_histo.bmp");
    Image_free(h2);
    Image * h3 = Image_histoCumulatifBMP(i3, 1280, 900);
    Image_export(h3, "output_img/equalized_histoCumulatif.bmp");
    Image_free(h3);

    //ETIREMENT
    Image * i5 = Image_extend(i0);
    Image_export(i5, "output_img/strectched.bmp");

    Image * h4 = Image_histoBMP(i5, 1280, 900);
    Image_export(h4, "output_img/stretch_histo.bmp");
    Image_free(h4);
    Image * h5 = Image_histoCumulatifBMP(i5, 1280, 900);
    Image_export(h5, "output_img/stretch_histoCumulatif.bmp");
    Image_free(h5);

    //SPECIFICATION
    Image * ix = Image_import("img/skybox.bmp");
    unsigned int ** H = Image_histoCumulatif(ix);
    Image_free(ix);

    Image * i4 = Image_specHisto(i0, H[0], H[1], H[2]);
    Image_export(i4, "output_img/specified.bmp");

    Image * h6 = Image_histoBMP(i4, 1280, 900);
    Image_export(h6, "output_img/specified_histo.bmp");
    Image_free(h6);

    Image * h7 = Image_histoCumulatifBMP(i4, 1280, 900);
    Image_export(h7, "output_img/specified_histoCumulatif.bmp");
    Image_free(h7);

    //FREE MEMORY
    Image_free(i0);
    Image_free(i3);
    Image_free(i4);
    Image_free(i5);

    printf("END\n");
}