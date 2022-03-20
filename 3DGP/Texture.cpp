#include "Texture.h"

#include <stdexcept>

#include <stb/stb_image.h>

#include "File.h"

Texture::Texture(const std::string& _fileName)
{
	// Load texture from file.
	m_textureSize = glm::ivec2(0, 0);
	unsigned char* data = stbi_load((File::GetBasePath() + _fileName).c_str(), &m_textureSize.x, &m_textureSize.y, nullptr, 4);
	if (!data) { throw std::runtime_error("Failed to load texture \"" + _fileName + "\""); }
	
	// Generate and bind texture.
	m_textureId = 0;
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