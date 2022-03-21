#include "WavefrontModel.h"

#include <stdexcept>

#include "File.h"

WavefrontModel::WavefrontModel(const std::string& _fileName)
{
	const std::string path = File::GetBasePath() + _fileName;
	
	m_model = { 0 };
	if (WfModelLoad(path.c_str(), &m_model) != 0) { throw std::runtime_error("Failed to load model " + path); }
}

WavefrontModel::~WavefrontModel()
{
	WfModelDestroy(&m_model);
}
