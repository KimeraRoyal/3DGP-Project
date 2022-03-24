#pragma once

#include <memory>

#include "IComponent.h"
#include "IModel.h"

class ModelComponent : public IComponent
{
private:
	std::shared_ptr<IModel> m_model;
public:
	ModelComponent();

	void Start() override;
	void Draw() override;

	[[nodiscard]] std::shared_ptr<IModel> GetModel() { return m_model; }

	void SetModel(const std::shared_ptr<IModel>& _model) { m_model = _model; }
};

