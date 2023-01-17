#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "Vec.h"
#include "Matrix.h"
#include "Image.h"

void main()
{

    //OPEN IMAGE INTO AN IMAGE STRUCT
    Image * i0 = Image_import("img/city.bmp");

    Matrix * gx = Matrix_generate(3,3);

    Matrix_setAt(gx, 0, 0, -1);
    Matrix_setAt(gx, 0, 1, -2);
    Matrix_setAt(gx, 0, 2, -1);

    Matrix_setAt(gx, 1, 0, -2);
    Matrix_setAt(gx, 1, 1, 12);
    Matrix_setAt(gx, 1, 2, -2);

    Matrix_setAt(gx, 2, 0, -1);
    Matrix_setAt(gx, 2, 1, -2);
    Matrix_setAt(gx, 2, 2, -1);

    Image * i1 = Image_applyMatrix(i0, gx);
    Vec3 * v = (Vec3 *) calloc( 1, sizeof(Vec3) );
    Vec3_set(v, 0.1, 0.2, 0.4);
    Image_applyTreshold(i1, v);
    free(v);

    Image_export(i1, "output_img/test.bmp");

    Image_free(i0);
    Image_free(i1);
}