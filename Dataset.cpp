#include "Dataset.h"
#include "LoadSaveBinary.h"

Dataset::Dataset()
{
}

Dataset::Dataset(std::string src)
{
	m_data = loadBatch(src);
}

Dataset::Dataset(const std::vector<Image*>& v)
{
	m_data = v;
}

void Dataset::addData(std::string src)
{
	std::vector<Image*> toAppend = loadBatch(src);
	m_data.insert(std::end(m_data), std::begin(toAppend), std::end(toAppend));
}

void Dataset::addVectorToData(std::vector<Image*>& vec)
{
	m_data.insert(std::end(m_data), std::begin(vec), std::end(vec));
}

void Dataset::readDatasetLabels(std::string src) {
	m_labels = readLabels(src);
}

Dataset::~Dataset()
{
	/*for (auto image: m_data) {
		delete image;
	}
	m_data.clear();*/
}
