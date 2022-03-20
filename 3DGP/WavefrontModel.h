#pragma once

#include <string>

#include <wavefront/wavefront.h> 

#include "IModel.h"

class WavefrontModel final : public IModel
{
private:
	WfModel m_model{};
	
public:
	explicit WavefrontModel(const std::string& _fileName);
	~WavefrontModel();
	
	[[nodiscard]] GLuint GetVaoId() override { return m_model.vaoId; }
	[[nodiscard]] GLuint GetTextureId() override { return m_model.textureId; }
	[[nodiscard]] int GetVertexCount() override { return m_model.vertexCount; }
};

