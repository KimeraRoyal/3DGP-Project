#pragma once

#include <GL/glew.h>

class ITexture
{
public:
	virtual ~ITexture() = default;
	
	void Bind() { glBindTexture(GL_TEXTURE_2D, GetId()); }
	void Unbind() { glBindTexture(GL_TEXTURE_2D, 0); }

	virtual GLuint GetId() = 0;
};