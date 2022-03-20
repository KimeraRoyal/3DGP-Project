#pragma once

#include <gl/glew.h>

class IModel
{
public:
	virtual ~IModel() = default;

	void Draw();
	
	void Bind();
	static void Unbind();
	
	[[nodiscard]] virtual GLuint GetVaoId() = 0;
	[[nodiscard]] virtual GLuint GetTextureId() = 0;
	[[nodiscard]] virtual int GetVertexCount() = 0;
};

