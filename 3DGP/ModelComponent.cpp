#include "ModelComponent.h"

size_t ModelComponent::s_modelMatrixKey = ShaderProgram::GetUniformKey("in_Model");

ModelComponent::ModelComponent()
{

}

void ModelComponent::Start()
{
	
}

void ModelComponent::Draw()
{
	m_program->SetUniformValueByKey(s_modelMatrixKey, GetTransform()->GetModelMatrix());
	
	m_model->Draw();
}

void ModelComponent::SetProgram(const std::shared_ptr<ShaderProgram>& _program)
{
	m_program = _program;
}
