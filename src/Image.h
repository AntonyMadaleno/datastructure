/**
 * @file Image.h
 * @brief Header for struct Image
 * @author Antony Madaleno
 * @version 1.0
 * @date 12-01-2023
 *
 * Header pour les struct de Image, semblable à des matrices
 *
 */

#pragma once

#include "Vec.h"
#include "Matrix.h"

#define IMAGE_BMP

/// @brief contain image data
typedef struct Image
{
    unsigned short height, width;
    Matrix * R;
    Matrix * G;
    Matrix * B;
} Image;

/// @brief initiate image data
/// @param height position on y-axis
/// @param width position on x-axis
/// @param img image
Image * Image_set(unsigned short height, unsigned short width);

/// @brief Free memory used by image
/// @param img 
void Image_free(Image * img);

/// @brief get R,G,B value of a pixel at given position
/// @param img image struct
/// @param x position on row
/// @param y position on column
/// @return pointer to a Vec3 containing values of said pixel R,G,B
Vec3 * Image_getPixel(Image * img, unsigned short x, unsigned short y);

/// @brief set R,G,B channels of a given pixel
/// @param img pointer to image
/// @param x position in column
/// @param y position in row
/// @param pixel pointer to Pixel with R,G,B value inside
void Image_setPixel(Image * img, unsigned short x, unsigned short y, Vec3 * pixel);

/// @brief Import an image from BMP format directly allocate right amount of memory
/// @param img 
/// @param filepath 
Image * Image_import(char * filepath);

/// @brief Export an image to BMP format
/// @param img 
/// @param filepath 
void Image_export(Image * img, char * filepath);

/// @brief apply a average filter of size N
/// @param mat pointer to matrix of size n² with n odd
/// @param img 
/// @param output 
Image * Image_applyMatrix(Image * img, Matrix * mat);

/// @brief 
/// @param x 
void Image_applyTreshold(Image * img, Vec3 * v);


/// @brief 
/// @param img pointer to original image
/// @param s size of filtering
/// @return pointer to resulting image
Image * Image_medianFilter(Image * img, unsigned short s);

Image * Image_histoBMP(Image * img, unsigned short w, unsigned short h);

Image * Image_histoCumulatifBMP(Image * img, unsigned short w, unsigned short h);

unsigned int ** Image_histo(Image * img);

unsigned int ** Image_histoCumulatif(Image * img);

Image * Image_extend(Image * img);

Image ** Image_applyFFT(Image * img);

Image * Image_applyIFFT(Image ** frq);

