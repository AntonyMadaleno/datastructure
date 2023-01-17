#include "Image.h"
#include "stdio.h"
#include "stdlib.h"

Image * Image_set(unsigned short height, unsigned short width)
{
    Image * img = (Image *) calloc(1, sizeof(Image));

    img->height = height;
    img->width = width;

    img->R = Matrix_generate(width, height);
    img->G = Matrix_generate(width, height);
    img->B = Matrix_generate(width, height);

    return img;
}

void Image_free(Image * img)
{
    Matrix_free(img->R);
    Matrix_free(img->G);
    Matrix_free(img->B);
}

Vec3 * Image_getPixel(Image * img, unsigned short x, unsigned short y)
{
    if(img == NULL)
        return NULL;

    Vec3 * output = (Vec3 *) calloc(1, sizeof(Vec3) );

    output->x = * Matrix_at(img->R, x, y);
    output->y = * Matrix_at(img->G, x, y);
    output->z = * Matrix_at(img->B, x, y);

    return output;
}

void Image_setPixel(Image * img, unsigned short x, unsigned short y, Vec3 * pixel)
{
    Matrix_setAt(img->R, x, y, pixel->x);
    Matrix_setAt(img->G, x, y, pixel->y);
    Matrix_setAt(img->B, x, y, pixel->z);
}

Image * Image_import(char * filepath)
{
    //get data from a bmp file
    FILE * file;
    file = fopen(filepath, "rb");

    if (file == NULL)
    {
        printf("CAN'T OPEN : '%s'", filepath);
        return NULL;
    }

    if( file != NULL)
    {

        unsigned char * header = (unsigned char *) malloc( sizeof(unsigned char) * 14);
        unsigned char * info_header = (unsigned char *) malloc( sizeof(unsigned char) * 40);

        fread(header, sizeof(char), 14, file);
        fread(info_header, sizeof(char), 40, file);

        unsigned int width = 0;
        unsigned int height = 0;

        width += info_header[4]     << 0;
        width += info_header[5]     << 8;
        width += info_header[6]     << 16;
        width += info_header[7]     << 24;

        height += info_header[8]    << 0;
        height += info_header[9]    << 8;
        height += info_header[10]   << 16;
        height += info_header[11]   << 24;

        unsigned char * data = (unsigned char *) malloc( sizeof(unsigned char) * 3);

        Image * img = Image_set(height, width);

        free(header);
        free(info_header);

        const unsigned char padding_amount = ( 4 - ( img->width * 3 ) % 4) % 4;

        for (unsigned short y = 0; y < height; y++)
        {
            for (unsigned short x = 0; x < width; x++)
            {
                fread(data, sizeof(unsigned char), 3, file);
                Vec3 * pixel = (Vec3 *) calloc(1, sizeof(Vec3) );
                Vec3_set(
                    pixel,
                    (float) data[2] / 255.0f ,
                    (float) data[1] / 255.0f ,
                    (float) data[0] / 255.0f 
                );
                Image_setPixel(img, x, y, pixel);
                free(pixel);
                if (x == width - 1)
                    fread(data, sizeof(unsigned char), padding_amount, file);
            }
        }

        free(data);
        return img;
    }

}

void Image_export(Image * img, char * filepath)
{
    FILE * file;
    file = fopen(filepath, "wb");

    if( file != NULL)
    {
        unsigned char bmppad[1] = { 0 };

        const unsigned char padding_amount = ( 4 - ( img->width * 3 ) % 4) % 4;
        const unsigned char header_size = 14;
        const unsigned char info_header_size = 40;
        const unsigned int file_size = header_size + info_header_size + img->width * img->height * 3 + padding_amount * img->height;

        unsigned char file_header[ header_size ];

        //FILE TYPE
        file_header[0] = 'B';
        file_header[1] = 'M';

        //FILE SIZE
        file_header[2] = file_size;
        file_header[3] = file_size >> 8;
        file_header[4] = file_size >> 16;
        file_header[5] = file_size >> 24;

        //RESERVED 0 Not Used
        file_header[6] = 0;
        file_header[7] = 0;

        //RESERVED 1 Not Used
        file_header[8] = 0;
        file_header[9] = 0;

        //PIXEL DATA OFFSET
        file_header[10] = header_size + info_header_size;
        file_header[11] = 0;
        file_header[12] = 0;
        file_header[13] = 0;

        unsigned char information_header[ info_header_size ];

        //HEADER SIZE
        information_header[0] = info_header_size;
        information_header[1] = 0;
        information_header[2] = 0;
        information_header[3] = 0;

        //IMAGE WIDTH
        information_header[4] = img->width;
        information_header[5] = img->width >> 8;
        information_header[6] = img->width >> 16;
        information_header[7] = img->width >> 24;

        //IMAGE HEIGHT
        information_header[8]  = img->height;
        information_header[9]  = img->height >> 8;
        information_header[10] = img->height >> 16;
        information_header[11] = img->height >> 24;

        //PLANES
        information_header[12] = 1;
        information_header[13] = 0;

        //BITS PER PIXELS
        information_header[14] = 24;
        information_header[15] = 0;

        //COMPRESSION (NO COMPRESSION)
        information_header[16] = 0;
        information_header[17] = 0;
        information_header[18] = 0;
        information_header[19] = 0;

        //IMAGE SIZE (NO COMPRESSION)
        information_header[20] = 0;
        information_header[21] = 0;
        information_header[22] = 0;
        information_header[23] = 0;

        //X PIXEL PER METER
        information_header[24] = 0;
        information_header[25] = 0;
        information_header[26] = 0;
        information_header[27] = 0;

        //Y PIXEL PER METER
        information_header[28] = 0;
        information_header[29] = 0;
        information_header[30] = 0;
        information_header[31] = 0;

        //TOTAL COLORS
        information_header[32] = 0;
        information_header[33] = 0;
        information_header[34] = 0;
        information_header[35] = 0;

        //IMPORTANT COLORS [IGNORED]
        information_header[36] = 0;
        information_header[37] = 0;
        information_header[38] = 0;
        information_header[39] = 0;

        fwrite((char *) file_header, header_size, 1, file);
        fwrite((char *) information_header, info_header_size, 1, file);

        for (unsigned short y = 0; y < img->height; y++)
        {
            for (unsigned short x = 0; x < img->width; x++)
            {
                Vec3 * pixel;
                pixel = Image_getPixel(img, x, y);
                unsigned char r = (unsigned char) ( pixel->x * 255.0f );
                unsigned char g = (unsigned char) ( pixel->y * 255.0f );
                unsigned char b = (unsigned char) ( pixel->z * 255.0f );

                unsigned char color[3] = { b, g, r };
                fwrite((char *) color, sizeof(char) * 3, 1, file);
            }

            for (unsigned char p = 0; p < padding_amount; p++)
                fwrite( (char *) bmppad, sizeof(char), 1, file);
        }

    }
    else
        printf("can't open file %s", filepath);

    fclose(file);
}

//apply mat to all channels
Image * Image_applyMatrix(Image * img, Matrix * mat)
{
    if (img == NULL || mat == 0 || mat->n_cols % 2 != 1 || mat->n_cols != mat->n_rows)
        return NULL;

    Image * out = Image_set(img->height, img->width);
    short offset = (mat->n_rows -1)/2;

    for (unsigned short y = 0; y < img->height; y++)
    {
        for (unsigned short x = 0; x < img->width; x++)
        {
            if ( x < offset || y < offset || x > img->width -offset -1 || y > img->height -offset -1 )
            {
                Vec3 * pix = Image_getPixel(img, x, y);
                Image_setPixel( out, x, y, pix );
                free(pix);
            }
            else
            {
                Vec3 * pix = (Vec3 *) calloc( 1, sizeof(Vec3) );

                for (unsigned short r = 0; r < mat->n_rows; r++)
                {
                    for (unsigned short c = 0; c < mat->n_cols; c++)
                    {
                        Vec3 * tmp = Image_getPixel( img, x + c - offset, y + r - offset);
                        pix->x += ( * Matrix_at(mat, c, r) ) * tmp->x;
                        pix->y += ( * Matrix_at(mat, c, r) ) * tmp->y;
                        pix->z += ( * Matrix_at(mat, c, r) ) * tmp->z;
                        free(tmp);
                    }
                }

                Image_setPixel(out, x, y, pix);
                free(pix);
            }
        }
    }

    return out;

}

void Image_applyTreshold(Image * img, Vec3 * v)
{
    for (unsigned short y = 0; y < img->height; y++)
    {
        for (unsigned short x = 0; x < img->width; x++)
        {
            Vec3 * pix = Image_getPixel(img, x, y);

            if (pix->x < v->x) pix->x = 0; else pix->x = 1; 
            if (pix->y < v->y) pix->y = 0; else pix->y = 1; 
            if (pix->z < v->z) pix->z = 0; else pix->z = 1;

            Image_setPixel(img, x, y, pix);

            free(pix);
        }
    }
}