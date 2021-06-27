#pragma once
#include "Classifier.h"
#include "Dataset.h"
#include "metrics.h"
#include <string>
#include <vector>

typedef double (*dist)(Image*, Image*);

class KNearestNeighbours :
    public Classifier
{
public:
    KNearestNeighbours(const Dataset&);
    KNearestNeighbours(unsigned int k, dist distance, const Dataset&);

    virtual void train() override;
    virtual int predictOnSample(Image*) override;
    virtual std::pair<std::vector<std::vector<int>>, double> evaluateClassifier(const Dataset&) override;

private:
    Dataset m_trainingSet;
    unsigned int m_k;
    dist m_dist;
};

