#pragma once

#include <string>

#include <GL/glew.h>
#include <glm/vec2.hpp>

class Texture
{
private:
	GLuint m_textureId;
	glm::ivec2 m_textureSize;
public:
	Texture(const std::string& _fileName);
	~Texture();

	Texture(const Texture& _copy) = delete;
	Texture& operator=(const Texture& _other) = delete;

	[[nodiscard]] GLuint GetId() const { return m_textureId; }
	[[nodiscard]] glm::ivec2 GetSize() const { return m_textureSize; }
};

