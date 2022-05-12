#pragma once

#include <memory>

#include "RenderTexture.h"

class CameraComponent;
class LightComponent;
class RenderableComponent;

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
	
	std::vector<std::shared_ptr<CameraComponent>> m_cameras;
	std::vector<std::shared_ptr<LightComponent>> m_lights;
	std::vector<std::shared_ptr<RenderableComponent>> m_renderables;
	
	std::shared_ptr<RenderTexture> m_gBuffer;

	std::shared_ptr<IModel> m_quad;
	std::shared_ptr<ShaderProgram> m_program;
public:
	explicit RenderingSystem(Resources* _resources);

	void PreDraw();
	void Draw() const;

	void Bind() const { m_gBuffer->BindFramebuffer(); }
	void Unbind() const { m_gBuffer->UnbindFramebuffer(); }

	void AddCamera(const std::shared_ptr<CameraComponent>& _camera) { m_cameras.push_back(_camera); }
	void AddLight(const std::shared_ptr<LightComponent>& _light) { m_lights.push_back(_light); }
	void AddRenderable(const std::shared_ptr<RenderableComponent>& _light) { m_renderables.push_back(_light); }
};

