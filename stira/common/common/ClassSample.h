#ifndef FEATURE_H
#define FEATURE_H

#include <vector>

// class to structure feature values for classification
class ClassSample
{
public:
    ClassSample()
    {
        m_vFeatureVector.clear();
        m_label = -1;
        m_isClassified = false;
    }


    std::vector<double> GetFeatureVector() {return m_vFeatureVector;}
    void SetFeatureVector( std::vector<double> vFeatureVector )
    {
        m_vFeatureVector = vFeatureVector;
    }

    void SetLabel(int label)
    {
        m_label = label;
        m_isClassified = true;
    }

    int GetLabel() { return m_label;}

    bool GetIsClassified() {return m_isClassified;}


private:
    std::vector<double> m_vFeatureVector;
    int m_label;
    bool m_isClassified;
};

#endif // FEATURE_H
