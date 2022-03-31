#include "ModelComponent.h"

#include <iostream>

ModelComponent::ModelComponent()
{

}

void ModelComponent::Start()
{
	GetTransform()->SetPosition(glm::vec3(0.0f, -1.0f, -10.0f));
}

void ModelComponent::Draw()
{
	m_model->Draw();
}

void ModelComponent::SetProgram(const std::shared_ptr<ShaderProgram>& _program)
{
	m_program = _program;
	m_modelMatrixLoc = m_program->GetUniformLocation("in_Model");
}
