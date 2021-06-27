#include "metrics.h"
#include <cmath>

double euclidean(Image* im1, Image* im2) {
	long long int sum = 0;
	for (int i = 0; i < 1024; i++) { //pow() increases the computation time!
		sum += ((long long int)im1->redChannel[i] - (long long int)im2->redChannel[i]) * ((long long int)im1->redChannel[i] - (long long int)im2->redChannel[i]);
		sum += ((long long int)im1->greenChannel[i] - (long long int)im2->greenChannel[i]) * ((long long int)im1->greenChannel[i] - (long long int)im2->greenChannel[i]);
		sum += ((long long int)im1->blueChannel[i] - (long long int)im2->blueChannel[i]) * ((long long int)im1->blueChannel[i] - (long long int)im2->blueChannel[i]);
	}
	//return sqrt(sum);
	return sum; //sqrt is monotonic, hence the actual sqrt only decreases the sum (we dropped it in favor of the speed)
}

double euclideanP3(Image* im1, Image* im2){
	long long int sum = 0;
	for (int i = 0; i < 1024; i++) { //pow() increases the computation time!
		sum += abs(((long long int)im1->redChannel[i] - (long long int)im2->redChannel[i]) * ((long long int)im1->redChannel[i] - (long long int)im2->redChannel[i]) * ((long long int)im1->redChannel[i] - (long long int)im2->redChannel[i]));
		sum += abs(((long long int)im1->greenChannel[i] - (long long int)im2->greenChannel[i]) * ((long long int)im1->greenChannel[i] - (long long int)im2->greenChannel[i]) * ((long long int)im1->greenChannel[i] - (long long int)im2->greenChannel[i]));
		sum += abs(((long long int)im1->blueChannel[i] - (long long int)im2->blueChannel[i]) * ((long long int)im1->blueChannel[i] - (long long int)im2->blueChannel[i]) * ((long long int)im1->blueChannel[i] - (long long int)im2->blueChannel[i]));
	}
	return sum; //sqrt is monotonic, hence the actual sqrt only decreases the sum (we dropped it in favor of the speed)
}

double euclideanP5(Image* im1, Image* im2) {
	long long int sum = 0;
	for (int i = 0; i < 1024; i++) { //pow() increases the computation time!
		sum += abs(((long long int)im1->redChannel[i] - (long long int)im2->redChannel[i]) * ((long long int)im1->redChannel[i] - (long long int)im2->redChannel[i]) * ((long long int)im1->redChannel[i] - (long long int)im2->redChannel[i]) * ((long long int)im1->redChannel[i] - (long long int)im2->redChannel[i]) * ((long long int)im1->redChannel[i] - (long long int)im2->redChannel[i]));
		sum += abs(((long long int)im1->greenChannel[i] - (long long int)im2->greenChannel[i]) * ((long long int)im1->greenChannel[i] - (long long int)im2->greenChannel[i]) * ((long long int)im1->greenChannel[i] - (long long int)im2->greenChannel[i]) * ((long long int)im1->greenChannel[i] - (long long int)im2->greenChannel[i]) * ((long long int)im1->greenChannel[i] - (long long int)im2->greenChannel[i]));
		sum += abs(((long long int)im1->blueChannel[i] - (long long int)im2->blueChannel[i]) * ((long long int)im1->blueChannel[i] - (long long int)im2->blueChannel[i]) * ((long long int)im1->blueChannel[i] - (long long int)im2->blueChannel[i]) * ((long long int)im1->blueChannel[i] - (long long int)im2->blueChannel[i]) * ((long long int)im1->blueChannel[i] - (long long int)im2->blueChannel[i]));
	}
	return sum; //sqrt is monotonic, hence the actual sqrt only decreases the sum (we dropped it in favor of the speed)
}

double minkowski(Image* im1, Image* im2) {
	long long int sum = 0;
	for (int i = 0; i < 1024; i++) {
		sum += abs((int)im1->redChannel[i] - (int)im2->redChannel[i]);
		sum += abs((int)im1->greenChannel[i] - (int)im2->greenChannel[i]);
		sum += abs((int)im1->blueChannel[i] - (int)im2->blueChannel[i]);
	}
	return (double)sum;
}