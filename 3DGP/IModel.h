#pragma once

#include <GL/glew.h>
#include "IResource.h"

class IModel : public IResource
{
public:
	virtual ~IModel() = default;

	void Draw();
	
	void Bind();
	static void Unbind();
	
	[[nodiscard]] virtual GLuint GetVaoId() = 0;
	[[nodiscard]] virtual GLuint GetTextureId() = 0;
	[[nodiscard]] virtual unsigned int GetVertexCount() = 0;
};

