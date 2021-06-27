#pragma once
#include <vector>
#include <string>
#include "Image.h"

class Dataset
{
public:
	Dataset();
	Dataset(std::string src);
	Dataset(const std::vector<Image*>& v);
	void addData(std::string src);
	void addVectorToData(std::vector<Image*>& vec);

	void readDatasetLabels(std::string src);

	inline const std::vector<Image*>& getData() const { return m_data; }
	inline const std::vector<std::string>& getLabels() const { return m_labels; }

	~Dataset();

private:
	std::vector<Image*> m_data;
	std::vector<std::string> m_labels;
};

