#pragma once

#include <string>

#include <gl/glew.h>
#include <glm/vec2.hpp>

class Texture
{
private:
	GLuint m_textureId;
	glm::ivec2 m_textureSize;

	Texture(const Texture& _copy) = delete;
	Texture& operator=(const Texture& _other) = delete;
public:
	Texture(std::string _path);
	~Texture();

	inline GLuint GetId() { return m_textureId; }
	inline glm::ivec2 GetSize() { return m_textureSize; }
};

