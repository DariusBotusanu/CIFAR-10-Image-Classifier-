#include "NaiveBayes.h"
#include "LoadSaveBinary.h"
#include <iostream>

using namespace std;

NaiveBayes::NaiveBayes(const Dataset& ds) :m_trainingSet{ds}
{
	for (auto label : ds.getLabels()) {
		m_prior.push_back(0);
	}
}

void NaiveBayes::train()
{
	double normalizer = m_trainingSet.getData().size();
	for (size_t i = 0; i < m_trainingSet.getLabels().size(); i++) {
		vector<feature> ftLikelihood;
		for (int j = 0; j < 1024; j++) {
			ftLikelihood.push_back(make_tuple(0, 0, 0));
		}
		m_likelihoods.push_back(ftLikelihood);
	}
	for (auto img : m_trainingSet.getData()) {
		m_prior[img->label]++;
		for (size_t i = 0; i < 1024; i++) {
			get<0>(m_likelihoods[img->label][i]) += (double)img->redChannel[i] / normalizer;
			get<1>(m_likelihoods[img->label][i]) += (double)img->greenChannel[i] / normalizer;
			get<2>(m_likelihoods[img->label][i]) += (double)img->blueChannel[i] / normalizer;
		}
	}

	for (size_t i = 0; i < m_prior.size(); i++) {
		m_prior[i] /= normalizer;
	}
}

int NaiveBayes::predictOnSample(Image* img)
{
	vector<double> probabilities;
	for (size_t i = 0; i < m_trainingSet.getLabels().size(); i++) {
		double prob = 1;
		prob *= m_prior[i];
		for (int j = 0; j < 1024; j++) {
			tuple<double, double, double> pixelProb = m_likelihoods[i][j]; // the tuple represents the j'th pixel averages for the i'th label
			//We will calculate how close is our current pixel to the average one
			double p1, p2, p3;
			if (get<0>(pixelProb) > (double)img->redChannel[i]) {
				p1 = (double)img->redChannel[i] / get<0>(pixelProb);
			}
			else {
				p1 = 1 - get<0>(pixelProb) / (double)img->redChannel[i];
			}
			if (get<1>(pixelProb) > (double)img->greenChannel[i]) {
				p2 = (double)img->greenChannel[i] / get<1>(pixelProb);
			}
			else {
				p2 = 1 - get<1>(pixelProb) / (double)img->greenChannel[i]; 
			}
			if (get<2>(pixelProb) > (double)img->blueChannel[i]) {
				p3 =  (double)img->blueChannel[i] / get<2>(pixelProb);
			}
			else {
				p3 = 1 - get<2>(pixelProb) / (double)img->blueChannel[i];
			}
			prob *= (p1 + p2 + p3) / 3;
		}
		probabilities.push_back(prob);
	}
	int closest = 0;
	double max = -1;
	for (size_t i = 0; i < probabilities.size(); i++) {
		if (probabilities[i] > max) {
			closest = i;
			max = probabilities[i];
		}
	}
	return closest;
}

std::pair<std::vector<std::vector<int>>, double> NaiveBayes::evaluateClassifier(const Dataset& ds)
{
	vector<vector<int>> confusionMatrix;
	for (size_t i = 0; i < m_trainingSet.getLabels().size(); i++) {
		vector<int> row;
		for (size_t j = 0; j < m_trainingSet.getLabels().size(); j++) {
			row.push_back(0);
		}
		confusionMatrix.push_back(row);
	}
	for (auto img : ds.getData()) {
		int index = predictOnSample(img);
		confusionMatrix[img->label][index]++;
	}

	double accuracy = 0;
	for (size_t i = 0; i < confusionMatrix.size(); i++) {
		accuracy += confusionMatrix[i][i];
	}
	accuracy = (accuracy / ds.getData().size()) * 100;

	return make_pair(confusionMatrix, accuracy);
}
