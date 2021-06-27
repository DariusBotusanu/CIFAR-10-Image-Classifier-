#pragma once
#include "Classifier.h"
#include "Dataset.h"
#include <vector>
#include <string>
#include <chrono>

using std::vector;

class StatisticsModule
{
public:
	StatisticsModule(Classifier*, const Dataset& testDataset);
	void saveToCsv(std::string);
private:
	Classifier* m_classifier;
	vector<vector<int>> m_confusionMatrix;
	vector<std::string> m_labels;
	double m_accuracy;
	std::chrono::nanoseconds m_trainingTime;
	std::chrono::nanoseconds m_testingTime;
	std::chrono::nanoseconds m_elapsedTime;
};

