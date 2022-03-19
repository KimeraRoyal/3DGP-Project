#pragma once

#include <string>
#include <GL/glew.h>

class Program
{
private:
	GLuint m_programId;

	int m_attributeCount;
public:
	Program();
	~Program();

	Program(const Program& _copy) = delete;
	Program& operator=(const Program& _other) = delete;

	void Link() const;

	void BindAttribute(const std::string& _attribute);

	[[nodiscard]] GLuint GetId() const { return m_programId; }
	[[nodiscard]] GLuint GetUniformLocation(const std::string& _uniformName) const;
};

