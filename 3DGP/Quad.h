#pragma once

#include <memory>

#include "IModel.h"
#include "Texture.h"
#include "VertexArray.h"

class Quad final : public IModel
{
private:
	static constexpr int c_vertexCount = 6;
	
	static constexpr glm::vec3 c_vertexPositions[c_vertexCount] =
	{ glm::vec3(-0.5f, 0.5f, 0.0f),
		glm::vec3(-0.5f, -0.5f, 0.0f),
		glm::vec3(0.5f, 0.5f, 0.0f),
		glm::vec3(-0.5f, -0.5f, 0.0f),
		glm::vec3(0.5f, -0.5f, 0.0f),
		glm::vec3(0.5f, 0.5f, 0.0f) };
	
	static constexpr glm::vec2 c_vertexTexcoords[c_vertexCount] =
	{ glm::vec2(0.0f, 1.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(1.0f, 1.0f) };
	
	std::shared_ptr<Texture> m_texture;
	std::shared_ptr<VertexArray> m_vao;
	
public:
	explicit Quad(const std::shared_ptr<Texture>& _texture);
	
	[[nodiscard]] GLuint GetVaoId() override { return m_vao->GetId(); }
	[[nodiscard]] GLuint GetTextureId() override { return m_texture->GetId(); }
	[[nodiscard]] unsigned int GetVertexCount() override { return m_vao->GetVertexCount(); }
};

