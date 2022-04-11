#pragma once

#include <memory>

#include <GL/glew.h>

#include "IResource.h"
#include "ITexture.h"

class IModel : public IResource
{
private:
	std::shared_ptr<ITexture> m_texture;
	
public:
	IModel();
	explicit IModel(const std::shared_ptr<ITexture>& _texture);
	virtual ~IModel() = default;

	void Draw(bool _bindTexture = true);
	
	void Bind(bool _bindTexture = true);
	static void Unbind(bool _unbindTexture = true);
	
	[[nodiscard]] virtual GLuint GetVaoId() = 0;
	[[nodiscard]] virtual GLuint GetTextureId();
	[[nodiscard]] virtual unsigned int GetVertexCount() = 0;
};

