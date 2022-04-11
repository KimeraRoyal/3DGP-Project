#include "Resources.h"

std::shared_ptr<ShaderProgram> Resources::GetProgram(const std::string& _vertShader, const std::string& _fragShader)
{
	const std::string path = _vertShader + _fragShader;
	std::shared_ptr<ShaderProgram> program = m_programs.GetResource(path, this, false);

	program->Load(_vertShader, _fragShader);

	return program;
}
