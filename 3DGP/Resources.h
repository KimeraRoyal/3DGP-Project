#pragma once

#include "ResourceHandler.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "WavefrontModel.h"

class Resources
{
private:
	ResourceHandler<Texture> m_textures;
	ResourceHandler<WavefrontModel> m_models;
	
	ResourceHandler<ShaderProgram> m_programs;
public:
	std::shared_ptr<Texture> GetTexture(const std::string& _path) { return m_textures.GetResource(_path); }
	std::shared_ptr<WavefrontModel> GetModel(const std::string& _path) { return m_models.GetResource(_path); }
	
	std::shared_ptr<ShaderProgram> GetProgram(const std::string& _path) { return m_programs.GetResource(_path); }
	std::shared_ptr<ShaderProgram> GetProgram(const std::string& _vertShader, const std::string& _fragShader);
};

