#pragma once

#include <string>

#include <wavefront/wavefront.h> 

#include "IModel.h"
#include "IResource.h"

class WavefrontModel final : public IModel, public IResource
{
private:
	WfModel m_model{};
	
public:
	~WavefrontModel() override;

	void Load(const std::string& _path) override;
	
	[[nodiscard]] GLuint GetVaoId() override { return m_model.vaoId; }
	[[nodiscard]] GLuint GetTextureId() override { return m_model.textureId; }
	[[nodiscard]] unsigned int GetVertexCount() override { return m_model.vertexCount; }
};

