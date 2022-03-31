#include "ModelComponent.h"

#include <iostream>

ModelComponent::ModelComponent()
{

}

void ModelComponent::Start()
{
	std::cout << "Model Start\n";
	GetTransform()->SetPosition(glm::vec3(0.0f, -1.0f, -10.0f));
}

void ModelComponent::Draw()
{
	glm::vec3 val = GetTransform()->GetPosition();
	std::printf("pX: %f pY: %f pZ: %f ", val.x, val.y, val.z);
	val = GetTransform()->GetScale();
	std::printf("sX: %f sY: %f sZ: %f ", val.x, val.y, val.z);
	val = GetTransform()->GetRotation();
	std::printf("rX: %f rY: %f rZ: %f\n", val.x, val.y, val.z);
	m_model->Draw();
}

void ModelComponent::SetProgram(const std::shared_ptr<ShaderProgram>& _program)
{
	m_program = _program;
	m_modelMatrixLoc = m_program->GetUniformLocation("in_Model");
}
