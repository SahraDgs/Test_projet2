#ifndef IMAGECLASSIFIER_H
#define IMAGECLASSIFIER_H

#include <stdbool.h>
#include "Image.h"
#include "Dataset.h"

// Opaque structure representing an image classifier
typedef struct ImgClas_t ImgClas;

/**
 * @brief Create a ImgClas object
 *
 * @param trainingSet the training set
 * @param featureExtractor a function that extracts features from an image
 * @return ImgClas* the created image classifier
 */
ImgClas *icCreate(Dataset *trainingSet, int (*featureExtractor)(Image *img, double *vector));

/**
 * @brief Free the memory allocated for the image classifier
 *
 * @param ic the image classifier to free
 */
void icFree(ImgClas *ic);

/**
 * @brief Train the image classifier
 *
 * @param ic the image classifier
 * @param nbEpochs the number of iterations over the training set
 * @param randomOrder if true, the images are presented in random order
 * @param reset if true, the model is reset before training
 */
void icTrain(ImgClas *ic, int nbEpochs, bool randomOrder, bool reset);

/**
 * @brief Return an array containing for each class the number of perceptrons
 * that predict this class
 *
 * @param ic the image classifier
 * @param img the image to classify
 * @return int* the array of votes
 */
int *icPredictVote(ImgClas *ic, Image *img);

/**
 * @brief Return the class predicted by the image classifier
 *
 * @param ic the image classifier
 * @param img the image to classify
 * @return int the predicted class
 */
int icPredict(ImgClas *ic, Image *img);

/**
 * @brief Return the error rate of the image classifier on the given dataset
 *
 * @param ic the image classifier
 * @param ts the test set
 * @return float the error rate
 */
float icGetTestError(ImgClas *ic, Dataset *ts);

/**
 * @brief Generate for each pair of classes (c1, c2) an image resulting from
 * the concatenation of all images of label c1 misclassified as c2. The files
 * should be named errors_c1_c2_N.bmp with N the number of misclassified images.
 * When N is equal to 0 for a pair of classes, no file is generated.
 *
 * @param ic the image classifier
 * @param ts the dataset
 * @param path the path where the images are saved
 */
void icShowErrors(ImgClas *ic, Dataset *ts, char *path);

/**
 * @brief Create features from the image, store them in the vector and return
 * the number of features. The features are defined as the pixels obtained after
 * aligning vertically the image. vector should have been allocated by the calling
 * function. if vector is NULL, the function only returns the number of features,
 * without computing them.
 *
 * @param img the image
 * @param vector the vector to fill
 * @return int the number of features
 */
int icGetFlatFeatures(Image *img, double *vector);

/**
 * @brief Fill the vector with the features extracted from the image and return
 * the number of features. These features can be obtained using a custom method.
 * vector should have been allocated by the calling function. if vector is NULL, 
 * the function only returns the number of features, without computing them.
 *
 * @param img the image
 * @param vector the vector to fill
 * @return int the number of features
 */
int icGetCustomFeatures(Image *img, double *vector);

#endif // IMAGECLASSIFIER_H
