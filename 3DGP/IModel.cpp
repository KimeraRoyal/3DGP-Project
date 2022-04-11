#include "IModel.h"

IModel::IModel()
{
	m_texture = nullptr;
}

IModel::IModel(const std::shared_ptr<ITexture>& _texture)
{
	m_texture = _texture;
}

void IModel::Draw(const bool _bindTexture)
{
	Bind(_bindTexture);
	glDrawArrays(GL_TRIANGLES, 0, GetVertexCount());
	Unbind(_bindTexture);
}

void IModel::Bind(const bool _bindTexture)
{
	if (_bindTexture) { glBindTexture(GL_TEXTURE_2D, GetTextureId()); }
	glBindVertexArray(GetVaoId());
}

void IModel::Unbind(const bool _unbindTexture)
{
	if (_unbindTexture) { glBindTexture(GL_TEXTURE_2D, 0); }
	glBindVertexArray(0);
}

GLuint IModel::GetTextureId()
{
	if (m_texture) { return m_texture->GetId(); }
	return 0;
}
