#include "LoadSaveBinary.h"
#include <sys/stat.h>
#include <fstream>
#include <exception>


using namespace std;

vector<string> readLabels(string src)
{
	vector<string> labels;
	ifstream file;
	file.open(src);
	while (file) {
		string newLabel;
		file >> newLabel;
		if (!newLabel.empty()) {
			labels.push_back(newLabel);
		}
	}
	file.close();
	return labels;
}

unsigned long sizeOfBin(string src)
{
	struct stat results;
	if (stat(src.c_str(), &results) == 0) {
		return results.st_size;
	}
	else {
		throw exception();
	}
}

vector<Image*> loadBatch(string src)
/**
* The next 3072 bytes are the values of the pixels of the image. The first 1024 bytes are the red channel values, the next 1024 the green, and the final 1024 the blue. 
* The values are stored in row-major order, so the first 32 bytes are the red channel values of the first row of the image.
* Each file contains 10000 such 3073-byte "rows" of images, although there is nothing delimiting the rows. Therefore each file should be exactly 30730000 bytes long.
*/
{
	ifstream batch;
	batch.open(src, ios::in | ios::binary);
	if (!batch) {
		batch.gcount();
		batch.clear();
		throw exception();
	}
	vector<Image*> images;
	long blk = 3073;
	long blkNum = 0;
	while (batch) {
		batch.seekg(blk * blkNum);
		if (blk * blkNum >= sizeOfBin(src))
			break;
		Image* img = new Image;
		batch.read((char*)img, sizeof(Image));
		images.push_back(img);
		blkNum++;
	}
	batch.close();
	return images;
}
