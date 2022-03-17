#include "Texture.h"

#include <stdexcept>

#include <stb/stb_image.h>

Texture::Texture(std::string _path)
{
	// Load texture from file.
	m_textureSize = glm::ivec2(0, 0);

	unsigned char* data = stbi_load("image.png", &m_textureSize.x, &m_textureSize.y, nullptr, 4);
	if (!data)
	{
		throw std::runtime_error("Failed to load texture \"image.png\"");
	}
	
	// Generate and bind texture.
	glGenTextures(1, &m_textureId);
	if (!m_textureId) { throw std::runtime_error("Failed to create texture."); }
	glBindTexture(GL_TEXTURE_2D, m_textureId);

	// Defines texture and frees loaded data.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_textureSize.x, m_textureSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	free(data);

	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_textureId);
}