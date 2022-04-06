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

std::shared_ptr<IComponent> ModelComponent::Parser::Parse(rapidjson::Value& _value)
{
	std::shared_ptr<ModelComponent> component = std::make_unique<ModelComponent>();

	component->SetModel(m_resources->GetModel(_value["model"].GetString()));
	component->SetProgram(m_resources->GetProgram(_value["shader"].GetString()));
	
	return component;
}
