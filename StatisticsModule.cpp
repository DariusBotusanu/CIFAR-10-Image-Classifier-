#include "StatisticsModule.h"
#include <fstream>
#include "LoadSaveBinary.h"

using namespace std;

StatisticsModule::StatisticsModule(Classifier* classifier, const Dataset& testDataset)
{

	auto beginTrain = std::chrono::high_resolution_clock::now();
	classifier->train();
	auto endTrain = std::chrono::high_resolution_clock::now();
	m_trainingTime = std::chrono::duration_cast<std::chrono::seconds>(endTrain - beginTrain);

	auto beginTest = std::chrono::high_resolution_clock::now();
	pair<vector<vector<int>>, double> stats = classifier->evaluateClassifier(testDataset);
	auto endTest = std::chrono::high_resolution_clock::now();
	m_testingTime = std::chrono::duration_cast<std::chrono::seconds>(endTest - beginTest);

	m_elapsedTime = m_trainingTime + m_testingTime;
	m_confusionMatrix = stats.first;
	m_accuracy = stats.second;
	m_labels = readLabels("./cifar-10-batches-bin/batches.meta.txt");
}

void StatisticsModule::saveToCsv(string src)
{
	ofstream csv;
	csv.open(src);
	csv << ",";
	for (size_t i = 0; i < m_labels.size(); i++) {
		if (i != m_labels.size() - 1) {
			csv << m_labels[i] << ",";
		}
		else {
			csv << m_labels[i] << "\n";
		}
		
	}
	for (size_t i = 0; i < m_confusionMatrix.size(); i++) {
		csv << m_labels[i] << ",";
		for (size_t j = 0; j < m_confusionMatrix.size(); j++) {
			if (j != m_confusionMatrix.size() - 1) {
				csv << m_confusionMatrix[i][j] << ", ";
			}
			else {
				csv << m_confusionMatrix[i][j] << "\n";
			}
		}
	}
	csv << "Acc: " << m_accuracy << "%" << "\n";
	csv << "Time(sec): " << m_elapsedTime.count() * 1e-9;
	csv.close();
}
