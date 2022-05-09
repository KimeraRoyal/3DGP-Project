#pragma once

#include <memory>
#include <rapidjson/document.h>

#include "IJsonParser.h"
#include "IModel.h"
#include "RenderableComponent.h"
#include "ShaderProgram.h"

class Material;

class ModelComponent : public RenderableComponent
{
private:
	std::shared_ptr<Material> m_material;
	
	static size_t s_modelMatrixKey;
	
	std::shared_ptr<IModel> m_model;

	std::shared_ptr<ShaderProgram> m_program;
public:
	class Parser final : public IJsonParser<IComponent>
	{
	public:
		explicit Parser(Resources* _resources) : IJsonParser(_resources) {}
		std::shared_ptr<IComponent> Parse(rapidjson::Value& _value) override;
	};
	
	ModelComponent();

	void Draw() override;

	[[nodiscard]] std::shared_ptr<IModel> GetModel() const { return m_model; }
	[[nodiscard]] std::shared_ptr<ShaderProgram> GetProgram() override { return m_program; }

	void SetModel(const std::shared_ptr<IModel>& _model) { m_model = _model; }
	void SetProgram(const std::shared_ptr<ShaderProgram>& _program);
	
	void SetMaterial(const std::shared_ptr<Material>& _material) { m_material = _material; }
};

