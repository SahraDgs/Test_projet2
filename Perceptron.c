
#include "Perceptron.h"

struct Perceptron_t
{
    int nbInputs_s;
    double *w_vect;
    double w0_s;


};

Perceptron *percInit(int nbInputs){

	Perception *nouvPerceptron = malloc(sizeof(Perceptron*));

    if(!nouvPerceptron){
            free(nouvPerceptron);
            return NULL;
        }

    nouvPerceptron->nbInputs_s = nbInputs;

    nouvPerceptron->w_vecteur = malloc(nbInputs_s = sizeof(Perceptron*));
    ouvPerceptron->w0_s = 0;

    if(!nouvPerception->w_vect){
            free(nouvPerceptron->vect);
            free(nouvPerceptron);
            return NULL;
        }

    for(int i =0; i< nbInputs ;i++)
        nouvPerceptron[i] = 0;

}

void percFree(Perceptron *p){

	free(p->w_vect);
    free(p);
    return NULL;
        
}

int percNbInputs(Perceptron *p){

	return p->nbInputs_s;
}

void percFit(Perceptron *p, double *x, int label){

    	p->w_vect += label * x;
    	p->w0 += label;

}

int percPredict(Perceptron *p, double *x){

   return sign(percPredictWeight(Perceptron *p, double *x));
}

double percPredictWeight(Perceptron *p, double *x){

    double w0 = p->w0_s;
    double WT_x = 0;

    for(int i = 0; i< nbInputs ;i++)  
        WT_x += p[i] * x[i];

    return WT_x + w0;

}