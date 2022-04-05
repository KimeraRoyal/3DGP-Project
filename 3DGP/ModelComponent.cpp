#include "ModelComponent.h"

ModelComponent::ModelComponent()
{

}

void ModelComponent::Start()
{
	
}

void ModelComponent::Draw()
{
	glUniformMatrix4fv(m_modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(GetTransform()->GetModelMatrix()));
	
	m_model->Draw();
}

void ModelComponent::SetProgram(const std::shared_ptr<ShaderProgram>& _program)
{
	m_program = _program;
	
	m_modelMatrixLoc = _program->GetUniformLocation("in_Model");
}
