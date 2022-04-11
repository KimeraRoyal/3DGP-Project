#pragma once

#include "Material.h"
#include "ResourceHandler.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "WavefrontModel.h"

//TODO: Track references to resources to unload them when they're unneeded
class Resources
{
private:
	ResourceHandler<Texture> m_textures;
	ResourceHandler<WavefrontModel> m_models;
	
	ResourceHandler<Material> m_materials;
	
	ResourceHandler<ShaderProgram> m_programs;
public:
	std::shared_ptr<Texture> GetTexture(const std::string& _path) { return m_textures.GetResource(_path, this); }
	std::shared_ptr<WavefrontModel> GetModel(const std::string& _path) { return m_models.GetResource(_path, this); }

	std::shared_ptr<Material> GetMaterial(const std::string& _path) { return m_materials.GetResource(_path, this); }
	
	std::shared_ptr<ShaderProgram> GetProgram(const std::string& _path) { return m_programs.GetResource(_path, this); }
	std::shared_ptr<ShaderProgram> GetProgram(const std::string& _vertShader, const std::string& _fragShader);
};

