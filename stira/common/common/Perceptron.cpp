#include "Perceptron.h"

Perceptron::Perceptron(int nrInputWeights, double learningRate)
{
   m_nrInputWeights = nrInputWeights;
   m_vWeights = std::vector<double>(m_nrInputWeights, 0.0);
   m_learningRate = learningRate;
}


Perceptron::~Perceptron()
{
}


void Perceptron::Train( std::vector<ClassSample> vTrainingSamples )
{
    bool hasConverged = false;
    int nrSamples = vTrainingSamples.size();

    while (!hasConverged)
    {
        for (int i = 0; i < nrSamples; i++)
        {
            int currentLabel = vTrainingSamples[i].GetLabel();
            std::vector<double> currentFeatureVector = vTrainingSamples[i].GetFeatureVector();

            double currentInProduct = 0.0;
            for (int j = 0; j < m_nrInputWeights; j++)
            {
                currentInProduct += currentFeatureVector[i] * m_vWeights[i];
            }

            if ( ( (double)(currentLabel) * currentInProduct ) <= 0.0)
            {
                for (int j = 0; j < m_nrInputWeights; j++)
                {
                     m_vWeights[i] += m_learningRate * currentFeatureVector[i] * currentLabel;
                     hasConverged = false;
                }
            }
        }
    }
}

