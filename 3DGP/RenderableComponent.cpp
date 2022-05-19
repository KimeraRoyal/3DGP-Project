#include  "RenderableComponent.h"

#include "Scene.h"

void RenderableComponent::Start()
{
	GetScene()->GetRenderingSystem()->AddRenderable(std::static_pointer_cast<RenderableComponent>(shared_from_this()));
}