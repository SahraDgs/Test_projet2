#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "Image.h"

struct Image_t
{
    size_t nb_rows;
    size_t nb_columns;
    unsigned char **content;
};

Image *imgCreate(size_t nb_rows, size_t nb_cols, unsigned char *content)
{
    unsigned char **imgArray = malloc(nb_rows * sizeof(unsigned char *));
    for (size_t i = 0; i < nb_rows; i++)
        imgArray[i] = malloc(nb_cols * sizeof(unsigned char));
    Image *img = malloc(sizeof(Image));
    img->nb_rows = nb_rows;
    img->nb_columns = nb_cols;
    img->content = imgArray;

    if (content != NULL)
    {
        size_t i = 0;
        for (size_t r = 0; r < nb_rows; r++)
            for (size_t c = 0; c < nb_cols; c++)
                imgArray[r][c] = content[i++];
    }
    else
    {
        for (size_t r = 0; r < nb_rows; r++)
            for (size_t c = 0; c < nb_cols; c++)
                imgArray[r][c] = 0;
    }

    return img;
}

void imgFree(Image *img)
{
    for (size_t i = 0; i < img->nb_rows; i++)
        free(img->content[i]);
    free(img->content);
    free(img);
}

unsigned char imgGetPixel(Image *img, size_t i, size_t j)
{
    if (i >= img->nb_rows || j >= img->nb_columns)
        exit(-1);
    else
        return img->content[i][j];
}

void imgSetPixel(Image *img, size_t i, size_t j, unsigned char p)
{
    if (i >= img->nb_rows || j >= img->nb_columns)
        exit(-1);
    else
        img->content[i][j] = p;
}

size_t imgGetNbRows(Image *img)
{
    return img->nb_rows;
}

size_t imgGetNbColumns(Image *img)
{
    return img->nb_columns;
}

void imgWrite(const char *filename, Image *img)
{
    FILE *fOut = fopen(filename, "w+");
    if (img->nb_rows > 65535 || img->nb_columns > 65535)
    {
        fprintf(stderr, "imgWrite: image too large to be saved\n");
        return;
    }
    unsigned char basic[56] = {66, 77, 54, 0, 12, 0, 0, 0, 0, 0, 54, 0, 0, 0,
                               40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24,
                               0, 0, 0, 0, 0, 0, 0, 12, 0, 206, 14, 0, 0, 216,
                               14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    basic[19] = (unsigned char)(img->nb_columns / 256);
    basic[18] = (unsigned char)(img->nb_columns % 256);
    basic[23] = (unsigned char)(img->nb_rows / 256);
    basic[22] = (unsigned char)(img->nb_rows % 256);
    fwrite(basic, sizeof(unsigned char), 54, fOut);
    for (int i = (int)img->nb_rows - 1; i >= 0; i--)
    {
        for (size_t j = 0; j < img->nb_columns; j++)
        {
            putc(255 - img->content[i][j], fOut);
            putc(255 - img->content[i][j], fOut);
            putc(255 - img->content[i][j], fOut);
        }
    }
    fclose(fOut);
}

#define WIMAGES 20

void imgWriteMultiImages(const char *filename, size_t nbImages, Image **images)
{
    Image *imgDest;

    if (nbImages == 0)
        return;

    size_t nb_rows = images[0]->nb_rows;
    size_t nb_cols = images[0]->nb_columns;

    if (nbImages <= WIMAGES)
        imgDest = imgCreate(nb_rows, nb_cols * nbImages, NULL);
    else if (nbImages % WIMAGES > 0)
        imgDest = imgCreate(nb_rows * (nbImages / WIMAGES + 1), nb_cols * WIMAGES, NULL);
    else
        imgDest = imgCreate(nb_rows * (nbImages / WIMAGES), nb_cols * WIMAGES, NULL);

    for (size_t i = 0; i < nbImages; i++)
    {
        size_t posc = (i % WIMAGES) * nb_cols;
        size_t posr = (i / WIMAGES) * nb_rows;
        for (size_t c = 0; c < nb_cols; c++)
        {
            for (size_t r = 0; r < nb_rows; r++)
            {
                imgSetPixel(imgDest, posr + r, posc + c, imgGetPixel(images[i], r, c));
            }
        }
    }

    imgWrite(filename, imgDest);
}

Image *imgDeskew(Image *img)
{
    // A compléter
}
