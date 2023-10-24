#ifndef MPERCEPTRON_H
#define MPERCEPTRON_H

// Opaque structure representing a multi-class perceptron
typedef struct MPerceptron_t MPerceptron;

/**
 * @brief Create a MPerceptron object
 *
 * @param nbInputs the number of inputs
 * @param nbClasses the number of classes
 * @return MPerceptron* the created multi-class perceptron
 */
MPerceptron *mpercInit(int nbInputs, int nbClasses);

/**
 * @brief Free the memory allocated for the multi-class perceptron
 *
 * @param mp the multi-class perceptron to free
 */
void mpercFree(MPerceptron *mp);

/**
 * @brief Get the number of inputs of the multi-class perceptron
 *
 * @param mp the multi-class perceptron
 * @return int the number of inputs
 */
int mpercNbInputs(MPerceptron *mp);

/**
 * @brief Get the number of classes of the multi-class perceptron
 *
 * @param mp the multi-class perceptron
 * @return int the number of classes
 */
int mpercNbClasses(MPerceptron *mp);

/**
 * @brief Fit the multi-class perceptron on the given example
 *
 * @param mp the multi-class perceptron
 * @param x the features vector
 * @param label the label of the example
 */
void mpercFit(MPerceptron *mp, double *x, int label);

/**
 * @brief Predict the class of the given example
 *
 * @param mp the multi-class perceptron
 * @param x the features vector
 * @return int the predicted class
 */
int mpercPredict(MPerceptron *mp, double *x);

/**
 * @brief Return an array containing for each class the number of perceptrons
 * that predict this class
 *
 * @param mp the multi-class perceptron
 * @param x the features vector
 * @return int* the array of votes
 */
int *mpercPredictVote(MPerceptron *mp, double *x);

#endif // MPERCEPTRON_H
