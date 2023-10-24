#ifndef PERCEPTRON_H
#define PERCEPTRON_H

// Opaque structure representing a perceptron
typedef struct Perceptron_t Perceptron;

/**
 * @brief Create a Perceptron object
 *
 * @param nbInputs the number of inputs
 * @return Perceptron* the created perceptron
 */
Perceptron *percInit(int nbInputs);

/**
 * @brief Free the memory allocated for the perceptron
 *
 * @param p the perceptron to free
 */
void percFree(Perceptron *p);

/**
 * @brief Get the number of inputs of the perceptron
 *
 * @param p the perceptron
 * @return int the number of inputs
 */
int percNbInputs(Perceptron *p);

/**
 * @brief Fit the perceptron on the given example
 *
 * @param p the perceptron
 * @param x the features vector
 * @param label the label of the example
 */
void percFit(Perceptron *p, double *x, int label);

/**
 * @brief Predict the class of the given example
 *
 * @param p the perceptron
 * @param x the features vector
 * @return int the predicted class
 */
int percPredict(Perceptron *p, double *x);

/**
 * @brief Return the weighted sum of the perceptron
 *
 * @param p the perceptron
 * @param x the features vector
 * @return double the weighted sum
 */
double percPredictWeight(Perceptron *p, double *x);

#endif // PERCEPTRON_H
