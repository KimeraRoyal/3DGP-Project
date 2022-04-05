#pragma once

#include <memory>

#include "IComponent.h"
#include "IModel.h"
#include "IRenderable.h"
#include "ShaderProgram.h"

class ModelComponent : public IComponent, public IRenderable
{
private:
	static size_t s_modelMatrixKey;
	
	std::shared_ptr<IModel> m_model;

	std::shared_ptr<ShaderProgram> m_program;
public:
	ModelComponent();

	void Start() override;
	void Draw() override;

	[[nodiscard]] std::shared_ptr<IModel> GetModel() const { return m_model; }
	[[nodiscard]] std::shared_ptr<ShaderProgram> GetProgram() override { return m_program; }

	void SetModel(const std::shared_ptr<IModel>& _model) { m_model = _model; }
	void SetProgram(const std::shared_ptr<ShaderProgram>& _program);
};

