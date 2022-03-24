#include "ModelComponent.h"

ModelComponent::ModelComponent()
{

}

void ModelComponent::Start()
{
	GetGameObject()->GetTransform()->SetPosition(glm::vec3(0.0f, -1.0f, -10.0f));
}

void ModelComponent::Draw()
{

}