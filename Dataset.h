#ifndef DATASET_H
#define DATASET_H

#include <stdio.h>
#include <stdlib.h>

#include "Image.h"

/* Opaque structure representing a dataset */
typedef struct dataset_t Dataset;

/**
 * @brief Load a dataset from several csv file.
 *
 * @param imageFile The name of the csv file containing the data.
 * @param labelFile The name of the csv file containing the labels.
 * @param labelnameFile The name of the file containing the label names.
 *
 * @return A pointer to the created dataset or NULL.
 */
Dataset *dsLoad(const char *imageFile, const char *labelFile,
                const char *labelnameFile);

/**
 * @brief Free a dataset, including all images (with imgFree).
 *
 * @param dataset The dataset to be freed.
 */
void dsFree(Dataset *dataset);

/**
 * @brief Return the number of images in a dataset.
 *
 * @param dataset The dataset.
 *
 * @return The number of images in the dataset.
 */
int dsGetNbImages(Dataset *dataset);

/**
 * @brief Return the i-th image in the dataset.
 *
 * @param dataset The dataset.
 * @param i The index of the images to be retrieved (an integer between 0 and
 * N-1, with N the number of images in the dataset).
 *
 * @return The i-th image in the dataset.
 */
Image *dsGetImage(Dataset *dataset, int i);

/**
 * @brief Return the label of the i-th image in the dataset.
 *
 * @param dataset The dataset.
 * @param i The index of the images to be retrieved (an integer between 0 and
 * N-1, with N the number of images in the dataset).
 *
 * @return The label of the i-th image in the dataset.
 */
int dsGetLabel(Dataset *dataset, int i);

/**
 * @brief Return the number of different labels in the dataset.
 *
 * @param dataset The dataset.
 *
 * @return The number of labels in the dataset.
 */
int dsGetNbLabelNames(Dataset *dataset);

/**
 * @brief Return the name (a string) of the i-th label in the dataset.
 *
 * @param dataset The dataset
 * @param label_index The integer code of the label
 * @return char* A string containing the label name
 */
char *dsGetLabelName(Dataset *dataset, int label_index);

#endif /* DATASET_H */
