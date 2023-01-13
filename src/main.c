#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "Vec.h"
#include "Matrix.h"

void main()
{
    Matrix * m1 = Matrix_generate( 2000, 2000 );

    for (unsigned short i = 0; i < m1->n_cols; i++)
        for (unsigned short j = 0; j < m1->n_rows; j++)
            Matrix_setAt(m1, i, j, 4*i + j + 1);

    Matrix * m2 = Matrix_generate( 2000, 2000 );

    for (unsigned short i = 0; i < m2->n_cols; i++)
        for (unsigned short j = 0; j < m2->n_rows; j++)
            Matrix_setAt(m2, i, j, i + 2*j + 1);

    clock_t start = clock();

    Matrix * r = Matrix_multiply(m1, m2);

    clock_t end = clock();

    printf("time spent on multiply = %3.2f s\n", (double) (end - start)/CLOCKS_PER_SEC );

    free(m1);
    free(m2);
    free(r);
}