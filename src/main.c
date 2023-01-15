#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "Vec.h"
#include "Matrix.h"

void main()
{
    srand( time( NULL ) );

    Matrix * m1 = Matrix_generate( 12, 12 );

    for (unsigned short i = 0; i < m1->n_cols; i++)
        for (unsigned short j = 0; j < m1->n_rows; j++)
            Matrix_setAt(m1, i, j, -1 + rand() % 3);

    //clock_t start = clock();
    //printf("%3.2f\n", Matrix_determinant(m1) );
    //clock_t end = clock();

    //printf("TIME SPENT CALCULATINF DETERMINANT = %3.3fs\n", (double) (end - start)/CLOCKS_PER_SEC );

    Matrix_free(m1);
}