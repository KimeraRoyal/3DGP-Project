#pragma once

#include <GL/glew.h>

class ColorBuffer
{
private:
	GLenum m_internalFormat;
	GLenum m_format;
	GLenum m_type;

	GLenum m_filter;
	GLenum m_wrap;

	GLuint m_textureId;

public:
	ColorBuffer(const GLenum _internalFormat, const GLenum _format, const GLenum _type, const GLenum _filter, const GLenum _wrap)
		: m_internalFormat(_internalFormat), m_format(_format), m_type(_type), m_filter(_filter), m_wrap(_wrap), m_textureId(0) {}

	[[nodiscard]] GLenum GetInternalFormat() const { return m_internalFormat; }
	[[nodiscard]] GLenum GetFormat() const { return m_format; }
	[[nodiscard]] GLenum GetType() const { return m_type; }

	[[nodiscard]] GLenum GetFilter() const { return m_filter; }
	[[nodiscard]] GLenum GetWrap() const { return m_wrap; }

	[[nodiscard]] GLuint GetTextureId() const { return m_textureId; }

	void SetTextureId(const GLuint _textureId) { m_textureId = _textureId; }
};
