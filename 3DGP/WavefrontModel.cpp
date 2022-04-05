#include "WavefrontModel.h"

#include <stdexcept>

WavefrontModel::~WavefrontModel()
{
	WfModelDestroy(&m_model);
}

void WavefrontModel::Load(const std::string& _path)
{
	const std::string path = _path;

	m_model = { 0 };
	if (WfModelLoad(path.c_str(), &m_model) != 0) { throw std::runtime_error("Failed to load model " + path); }
}
