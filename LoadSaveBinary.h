#pragma once
#include <string>
#include <vector>
#include "Image.h"

std::vector<std::string> readLabels(std::string);
unsigned long sizeOfBin(std::string src);
std::vector<Image*> loadBatch(std::string src);