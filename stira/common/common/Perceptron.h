#ifndef PERCEPTRON_H
#define PERCEPTRON_H
#include "ClassSample.h"

class Perceptron
{
public:
    Perceptron(int nrInputWeights, double learningRate);
    ~Perceptron();

    void Train( std::vector<ClassSample> vTrainingSamples );

private:
    int m_nrInputWeights;
    std::vector<double> m_vWeights;
    double m_learningRate;
};

#endif // PERCEPTRON_H
