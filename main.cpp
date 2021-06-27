#include <iostream>
#include "LoadSaveBinary.h"
#include "KNearestNeighbours.h"
#include "NaiveBayes.h"
#include "Image.h"
#include "StatisticsModule.h"
#include <fstream>

int main() {

	//TRAINING DATASET
	Dataset trainImages("./cifar-10-batches-bin/data_batch_1.bin");
	trainImages.addData("./cifar-10-batches-bin/data_batch_2.bin");
	trainImages.addData("./cifar-10-batches-bin/data_batch_3.bin");
	trainImages.addData("./cifar-10-batches-bin/data_batch_4.bin");
	trainImages.addData("./cifar-10-batches-bin/data_batch_5.bin");
	trainImages.readDatasetLabels("./cifar-10-batches-bin/batches.meta.txt");
	
	//TESTING DATASET
	vector<Image*> testingBatch = loadBatch("./cifar-10-batches-bin/test_batch.bin");
	Dataset testWholeBatch(testingBatch);
	testWholeBatch.readDatasetLabels("./cifar-10-batches-bin/batches.meta.txt");

	//CLASSIFIERS
	/*
	//NAIVE BAYES
	NaiveBayes nb(trainImages);
	StatisticsModule naiveBayes(&nb, testWholeBatch);
	naiveBayes.saveToCsv("./statistics/naiveBayes.csv");

	//KNN Minkowski metric
	KNearestNeighbours knnMinkowski13(13, minkowski, trainImages);
	StatisticsModule minkoskiStats13(&knnMinkowski13, testWholeBatch);
	minkoskiStats13.saveToCsv("./statistics/knn13Minkowski.csv");
	*/

	//KNN Euclidean metric
	KNearestNeighbours knnEuclidean(13, euclidean, trainImages);
	StatisticsModule euclideanStats(&knnEuclidean, testWholeBatch);
	euclideanStats.saveToCsv("./statistics/knn13Euclidean.csv");

	/*
	//KNN EuclideanP3 metric
	KNearestNeighbours knnEuclideanP3(13, euclideanP3, trainImages);
	StatisticsModule euclideanP3Stats(&knnEuclideanP3, testWholeBatch);
	euclideanP3Stats.saveToCsv("./statistics/knn13EuclideanP3.csv");

	//KNN EuclideanP5 metric
	KNearestNeighbours knnEuclideanP5(13, euclideanP5, trainImages);//
	StatisticsModule euclideanP5Stats(&knnEuclideanP5, testWholeBatch);
	euclideanP5Stats.saveToCsv("./statistics/knn13EuclideanP5.csv");
	*/

	return 0;
}