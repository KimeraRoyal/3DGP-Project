#pragma once

#include <string>

#include <GL/glew.h>
#include <glm/vec2.hpp>

#include "IResource.h"
#include "ITexture.h"

class Texture : public ITexture, public IResource
{
private:
	GLuint m_textureId;
	glm::ivec2 m_textureSize;
public:
	Texture();
	~Texture() override;

	void Load(const std::string& _path) override;
	
	Texture(const Texture& _copy) = delete;
	Texture& operator=(const Texture& _other) = delete;

	[[nodiscard]] GLuint GetId() override { return m_textureId; }
	[[nodiscard]] glm::ivec2 GetSize() const { return m_textureSize; }
};

