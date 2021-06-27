#pragma once
#include "Classifier.h"
#include "Dataset.h"
#include <string>
#include <unordered_map>

typedef std::tuple<double, double, double> feature;

class NaiveBayes :
    public Classifier
{
public:
    NaiveBayes(const Dataset& ds);
    virtual void train() override;
    virtual int predictOnSample(Image*) override;
    virtual std::pair<std::vector<std::vector<int>>, double> evaluateClassifier(const Dataset&) override;

private:
    Dataset m_trainingSet;
    std::vector<double> m_prior; //each position represents a label and the value at each position represents the prior probability of the label 
    std::vector<std::vector<feature>> m_likelihoods; 
    //each position of the vector represents a label
    //each i'th vector gives the likelihood of features to belong to the i'th label
};

