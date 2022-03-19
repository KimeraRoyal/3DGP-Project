#pragma once

#include <GL/glew.h>

class Program
{
private:
	GLuint m_programId;
public:
	Program();
	~Program();

	Program(const Program& _copy) = delete;
	Program& operator=(const Program& _other) = delete;

	void Link() const;

	[[nodiscard]] GLuint GetId() const { return m_programId; }
};

