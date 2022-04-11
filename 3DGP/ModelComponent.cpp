#include "ModelComponent.h"

size_t ModelComponent::s_modelMatrixKey = std::hash<std::string>()("in_Model");

ModelComponent::ModelComponent()
{
	m_material = nullptr;
}

void ModelComponent::Start()
{
	
}

void ModelComponent::Draw()
{
	m_program->SetUniformValueByKey(s_modelMatrixKey, GetTransform()->GetModelMatrix());

	if (m_material)
	{
		m_material->AssignUniforms(m_program);
		m_material->Bind();
	}
	
	m_model->Draw(!m_material || !m_material->HasTexture());
	
	if (m_material)
	{
		m_material->Unbind();
	}
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
	if(_value.HasMember("material")) { component->SetMaterial(m_resources->GetMaterial(_value["material"].GetString())); }
	
	return std::static_pointer_cast<IComponent>(component);
}
