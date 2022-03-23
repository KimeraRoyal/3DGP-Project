#include "Quad.h"

Quad::Quad(const std::shared_ptr<Texture>& _texture)
{
	m_texture = _texture;

	// Create vertex array object
	m_vao = std::make_unique<VertexArray>();

	// Create vertex buffer objects for positions and texture coordinates
	std::shared_ptr<VertexBuffer> vboPosition = std::make_unique<VertexBuffer>();
	std::shared_ptr<VertexBuffer> vboTexcoords = std::make_unique<VertexBuffer>();
	
	for(int i = 0; i < c_vertexCount; i++)
	{
		vboPosition->Add(c_vertexPositions[i]);
		vboTexcoords->Add(c_vertexTexcoords[i]);
	}

	// Add VBOs to VAO
	m_vao->AddBuffer(vboPosition);
	m_vao->AddBuffer(vboTexcoords);
}