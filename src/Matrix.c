/**
 * @file Matrix.c
 * @brief Implement Matrix.h
 * @author Antony Madaleno
 * @version 1.0
 * @date 12-01-2023
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "math.h"
#include "Matrix.h"

Matrix * Matrix_generate(unsigned short n_cols, unsigned short n_rows )
{
    if (n_cols == 0 || n_rows == 0)
        return NULL;
    
    Matrix * mat = (Matrix *) calloc( 1, sizeof(Matrix) );
    mat->n_cols = n_cols;
    mat->n_rows = n_rows;

    //ALLOCATION OF MEMORY
    mat->data = (float *) calloc( (size_t) n_cols * n_rows, sizeof(float) );
    return mat;
}

float * Matrix_at(Matrix * mat, unsigned short i, unsigned short j )
{
    return &(mat->data[i + j * mat->n_cols]);
}

unsigned char Matrix_setAt(Matrix * mat, unsigned short i, unsigned short j, float x)
{
    if (mat == NULL || i >= mat->n_cols || j >= mat->n_rows )
        return 0;

    * Matrix_at(mat, i, j) = x;
    return 1;
}

void Matrix_scalarMultiply(Matrix * mat, float x)
{
    if (mat == NULL)
        return;

    for (unsigned short i = 0; i < mat->n_cols; i++)
        for (unsigned short j = 0; j < mat->n_rows; j++)
            * Matrix_at(mat, i, j) *= x;
}

Matrix * Matrix_multiply(Matrix * m1, Matrix * m2)
{
    if (m1 == NULL || m2 == NULL || m1->n_cols != m2->n_rows)
        return NULL;

    Matrix * res = Matrix_generate(m2->n_cols, m1->n_rows);

    //for each row of m1
    for (unsigned short i = 0; i < m1->n_rows; i++)
    {   
        //for each column of m2
        for (unsigned short j = 0; j < m2->n_cols; j++)
        {
            Matrix_setAt(res, j, i, 0);
            //for each element of m1 row and m2 column
            for (unsigned short k = 0; k < m1->n_cols; k++)
                * Matrix_at(res, j, i) += ( * Matrix_at(m1, k, i) ) *  ( * Matrix_at(m2, j, k) );
        }
    }

    return res;
}

Matrix * Matrix_addition(Matrix * m1, Matrix * m2)
{
    if (m1 == NULL || m2 == NULL || m1->n_cols != m2->n_cols || m1->n_rows != m2->n_rows)
        return NULL;

    Matrix * result = Matrix_generate(m1->n_cols, m1->n_rows);

    for (unsigned short i = 0; i < m1->n_cols; i++)
        for (unsigned short j = 0; j < m1->n_rows; j++)
            * Matrix_at(result, i, j) = ( * Matrix_at(m1, i, j) ) + ( * Matrix_at(m2, i, j) );

    return result;
}

Matrix * Matrix_substract(Matrix * m1, Matrix * m2)
{
    if (m1 == NULL || m2 == NULL || m1->n_cols != m2->n_cols || m1->n_rows != m2->n_rows)
        return NULL;

    Matrix * result = Matrix_generate(m1->n_cols, m1->n_rows);

    for (unsigned short i = 0; i < m1->n_cols; i++)
        for (unsigned short j = 0; j < m1->n_rows; j++)
            * Matrix_at(result, i, j) = ( * Matrix_at(m1, i, j) ) - ( * Matrix_at(m2, i, j) );

    return result;
}

bool Matrix_equals(Matrix * m1, Matrix * m2)
{
    if (m1 == m2)
        return true;
    else if (m1 == NULL || m2 == NULL || m1->n_rows != m2->n_rows || m1->n_cols != m2->n_cols)
        return false;

    for (unsigned short i = 0; i < m1->n_cols; i++)
        for (unsigned short j = 0; j < m1->n_rows; j++)
            if ( * Matrix_at(m1, i, j) != * Matrix_at(m2, i, j) )
                return false;
    
    return true;
}

Matrix * Matrix_copy(Matrix * mat)
{
    if (mat == NULL)
        return NULL;

    Matrix * cpy = (Matrix *) calloc( 1, sizeof( Matrix ));
    memcpy(cpy, mat, 1)
    
    cpy->data = (float *) calloc( 1, (size_t) sizeof( float ) * cpy->n_cols * cpy->n_rows);
    memcpy(cpy->data, mat->data, cpy->n_cols * cpy->n_rows);

    return cpy;
}