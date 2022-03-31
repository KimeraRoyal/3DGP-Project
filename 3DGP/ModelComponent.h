#pragma once

#include <memory>

#include "IComponent.h"
#include "IModel.h"
#include "ShaderProgram.h"

class ModelComponent : public IComponent
{
private:
	std::shared_ptr<IModel> m_model;

	std::shared_ptr<ShaderProgram> m_program;

	GLint m_modelMatrixLoc;
public:
	ModelComponent();

	void Start() override;
	void Draw() override;

	[[nodiscard]] std::shared_ptr<IModel> GetModel() const { return m_model; }
	[[nodiscard]] std::shared_ptr<ShaderProgram> GetProgram() const { return m_program; }

	void SetModel(const std::shared_ptr<IModel>& _model) { m_model = _model; }
	void SetProgram(const std::shared_ptr<ShaderProgram>& _program);
};

