#include "mathFunctions.h"
#include <math.h>

double geometricSumEqualsOne(double a) {
	return log((pow(a, (-a - 1)) * (pow(a, (a + 2) - 1))) / a - 1) / log(a);
}