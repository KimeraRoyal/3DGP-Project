#include "IModel.h"

void IModel::Draw()
{
	Bind();
	glDrawArrays(GL_TRIANGLES, 0, GetVertexCount());
	Unbind();
}

void IModel::Bind()
{
	glBindVertexArray(GetVaoId());
	glBindTexture(GL_TEXTURE_2D, GetTextureId());
}

void IModel::Unbind()
{
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
