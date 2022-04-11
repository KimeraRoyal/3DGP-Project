#pragma once

#include <string>
#include <unordered_map>
#include <GL/glew.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "IResource.h"

class ShaderProgram : public IResource
{
private:
	GLuint m_programId;

	int m_attributeCount;

	std::unordered_map<size_t, GLuint> m_uniformLocations;

	void SetUniformKeys();
public:
	ShaderProgram();
	~ShaderProgram() override;

	ShaderProgram(const ShaderProgram& _copy) = delete;
	ShaderProgram& operator=(const ShaderProgram& _other) = delete;

	void Load(const std::string& _path, Resources* _resources) override;
	void Load(const std::string& _vertShader, const std::string& _fragShader);

	void Link() const;

	void BindAttribute(const std::string& _attribute);

	[[nodiscard]] GLuint GetId() const { return m_programId; }
	[[nodiscard]] GLuint GetUniformLocation(const std::string& _uniformName) const;

	void SetUniformValue(GLuint _uniformLocation, const float& _value) const;
	void SetUniformValue(GLuint _uniformLocation, const glm::vec2& _value) const;
	void SetUniformValue(GLuint _uniformLocation, const glm::vec3& _value) const;
	void SetUniformValue(GLuint _uniformLocation, const glm::vec4& _value) const;
	void SetUniformValue(GLuint _uniformLocation, const glm::mat4& _value) const;

	void SetUniformValueByKey(size_t _uniformKey, const float& _value) const;
	void SetUniformValueByKey(size_t _uniformKey, const glm::vec2& _value) const;
	void SetUniformValueByKey(size_t _uniformKey, const glm::vec3& _value) const;
	void SetUniformValueByKey(size_t _uniformKey, const glm::vec4& _value) const;
	void SetUniformValueByKey(size_t _uniformKey, const glm::mat4& _value) const;

	void SetUniformValueByName(const std::string& _uniformName, const float& _value) const;
	void SetUniformValueByName(const std::string& _uniformName, const glm::vec2& _value) const;
	void SetUniformValueByName(const std::string& _uniformName, const glm::vec3& _value) const;
	void SetUniformValueByName(const std::string& _uniformName, const glm::vec4& _value) const;
	void SetUniformValueByName(const std::string& _uniformName, const glm::mat4& _value) const;
};

