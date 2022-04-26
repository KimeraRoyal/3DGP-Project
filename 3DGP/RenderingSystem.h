#pragma once

#include <memory>

#include "RenderTexture.h"

class CameraComponent;
class IModel;
class ShaderProgram;
class Resources;
class Scene;

class RenderingSystem
{
private:
	static size_t s_projectionKey;
	static size_t s_modelKey;
	static size_t s_viewPosKey;
	
	std::shared_ptr<CameraComponent> m_camera;
	
	std::shared_ptr<RenderTexture> m_gBuffer;

	std::shared_ptr<IModel> m_quad;
	std::shared_ptr<ShaderProgram> m_program;
public:
	RenderingSystem(Resources* _resources);

	void Start(const std::shared_ptr<Scene>& _scene);
	void Draw() const;

	void Bind() const { m_gBuffer->BindFramebuffer(); }
	void Unbind() const { m_gBuffer->UnbindFramebuffer(); }
};

