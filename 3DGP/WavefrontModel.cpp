#include "WavefrontModel.h"

#include <stdexcept>

WavefrontModel::~WavefrontModel()
{
	WfModelDestroy(&m_model);
}

void WavefrontModel::Load(const std::string& _path)
{
	if (WfModelLoad(_path.c_str(), &m_model) != 0) { throw std::runtime_error("Failed to load model " + _path); }
}
