#ifndef IMAGEIO_H
#define IMAGEIO_H

// Opaque structure representing an image (grey level)

typedef struct Image_t Image;

/**
 * @brief Create a Image object
 *
 * @param nb_rows the number of rows of the image
 * @param nb_cols the number of columns of the image
 * @param content a vector with pixel values (ordered row by row).
 *                If NULL, the image is initialised with 0 values.
 *
 * @return Image* the created image
 */
Image *imgCreate(size_t nb_rows, size_t nb_cols, unsigned char *content);

/**
 * @brief Free the memory allocated for the image
 *
 * @param img the image to free
 */
void imgFree(Image *img);

/**
 * @brief Get the image pixel at the given position
 *
 * @param img the image
 * @param i the row index
 * @param j the column index
 * @return Pixel the pixel at the given position
 */
unsigned char imgGetPixel(Image *img, size_t i, size_t j);

/**
 * @brief Set the image pixel at the given position
 *
 * @param img the image
 * @param i the row index
 * @param j the column index
 * @param p the new value of the pixel
 */
void imgSetPixel(Image *img, size_t i, size_t j, unsigned char p);

/**
 * @brief Get the number of rows of the image
 *
 * @param img the image
 * @return size_t the number of rows of the image
 */
size_t imgGetNbRows(Image *img);

/**
 * @brief Get the number of columns of the image
 *
 * @param img the image
 * @return size_t the number of columns of the image
 */
size_t imgGetNbColumns(Image *img);

/**
 * @brief Write an image to a bmp file (image size should not exceed 65536x65536)
 *
 * @param filename the name of the bmp file
 * @param img the image to write
 */

void imgWrite(const char *filename, Image *img);

/**
 * @brief Write several images of the same size in a bmp file. Images are ordered from
 *        left to right, top to down, with no more than 20 images per row. Total image size
 *        should not exceed 65536x65536 pixels.
 *
 * @param filename the name of the bmp file
 * @param nbImages the number of images
 * @param images an array with at least nbImages
 */

void imgWriteMultiImages(const char *filename, size_t nbImages, Image **images);

/**
 * @brief Align the image so that its principal orientation is vertical
 *
 * @param img the image to be aligned (that should not be modified)
 * @return Image* a vertically aligned copy of img
 */

Image *imgDeskew(Image *img);

#endif
