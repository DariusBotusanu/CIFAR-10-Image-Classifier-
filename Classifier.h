#pragma once
#include "Image.h"
#include "Dataset.h"
#include <vector>

using std::vector;

class Classifier
{
public:
	virtual void train() = 0;
	virtual int predictOnSample(Image*) = 0;
	virtual std::pair<std::vector<std::vector<int>>, double> evaluateClassifier(const Dataset&) = 0;
};

