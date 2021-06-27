#include "KNearestNeighbours.h"
#include "LoadSaveBinary.h"
#include <algorithm>
#include <string>
#include <iostream>
#include <queue>

using namespace std;

KNearestNeighbours::KNearestNeighbours(const Dataset& ds) : m_k{ 1 }, m_dist{ euclidean }, m_trainingSet{ds}
{
}

KNearestNeighbours::KNearestNeighbours(unsigned int k, dist distance, const Dataset& ds) : m_k{ k }, m_dist{distance}, m_trainingSet{ ds }
{
}

void KNearestNeighbours::train()
{
	//All the training samples are already loaded into the Dataset
}

int KNearestNeighbours::predictOnSample(Image* sample)
{
	auto compare = [this, sample](pair<unsigned char, double> a, pair<unsigned char, double> b) { return a.second < b.second; };
	priority_queue<pair<unsigned char, double>, vector<pair<unsigned char, double>>, decltype(compare)> knn(compare); //NOTE TO SELF
	for (auto img : m_trainingSet.getData()) {
		double delta = m_dist(img, sample);
		if ((knn.size() == m_k) && (delta < knn.top().second)) {
			knn.pop();
			knn.push(make_pair(img->label, delta));
		}
		else if (knn.size() < m_k){
			knn.push(make_pair(img->label, delta));
		}
	}
	
	vector<int> votes;
	for (int i = 0; i < m_trainingSet.getLabels().size(); i++) {
		votes.push_back(0);
	}
	while(knn.size()) {
		int label = knn.top().first;
		++votes[label];
		knn.pop();
	}
	int voteWinner = -1;
	int prediction = 0;
	for (int i = 0; i < votes.size(); i++) {
		if (votes[i] > voteWinner) {
			voteWinner = votes[i];
			prediction = i;
		}
	}
	return prediction;
}

pair<vector<vector<int>>, double> KNearestNeighbours::evaluateClassifier(const Dataset& ds)
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
