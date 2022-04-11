#include "SceneParser.h"

#include <rapidjson/document.h>

#include "CameraComponent.h"
#include "ModelComponent.h"
#include "PlayerInputComponent.h"

SceneParser::SceneParser(Resources* _resources)
{
	m_resources = _resources;

	m_parsers.insert(std::make_pair("camera", std::make_unique<CameraComponent::Parser>(m_resources)));
	m_parsers.insert(std::make_pair("light", std::make_unique<LightComponent::Parser>(m_resources)));
	m_parsers.insert(std::make_pair("model", std::make_unique<ModelComponent::Parser>(m_resources)));
	m_parsers.insert(std::make_pair("playerInput", std::make_unique<PlayerInputComponent::Parser>(m_resources)));
}

std::shared_ptr<Scene> SceneParser::Parse(const std::string& _path)
{
	rapidjson::Document document = ReadDocument(_path);
	std::shared_ptr<Scene> scene = std::make_unique<Scene>(m_resources);

	if(document.HasMember("textures"))
	{
		rapidjson::Value& textures = document["textures"];
		assert(textures.IsArray());
		for (rapidjson::SizeType i = 0; i < textures.Size(); i++)
		{
			ParseTexture(textures[i]);
		}
	}

#ifdef _DEBUG
	printf("\n");
#endif
	
	if(document.HasMember("objects"))
	{
		rapidjson::Value& objects = document["objects"];
		assert(objects.IsArray());
		for (rapidjson::SizeType i = 0; i < objects.Size(); i++)
		{
			ParseObject(scene, objects[i]);
		}
	}

	return scene;
}

void SceneParser::ParseTexture(rapidjson::Value& _textureValue)
{
	std::shared_ptr<Texture> texture = m_resources->GetTexture(_textureValue["texture"].GetString());

#ifdef _DEBUG
	printf("Loading texture %s (%d)", _textureValue["texture"].GetString(), texture->GetId());
#endif

	texture->Bind();
	
	const bool generateMipmaps = _textureValue.HasMember("mipmap") && _textureValue["mipmap"].GetBool();
	if(generateMipmaps)
	{
#ifdef _DEBUG
		printf(" (Mipmaps)");
#endif
		
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	const bool filtering = _textureValue.HasMember("filtering") && !_textureValue["filtering"].GetBool();
	if(filtering)
	{
#ifdef _DEBUG
		printf(" (No Filtering)");
#endif

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
	
	GLint wrapX = GL_REPEAT, wrapY = GL_REPEAT;
	
	if(_textureValue.HasMember("wrapX"))
	{
		wrapX = GetWrapMode(_textureValue["wrapX"].GetString());
		
#ifdef _DEBUG
		printf(" (X Wrap: \"%s\" %d)", _textureValue["wrapX"].GetString(), wrapX);
#endif
	}
	if(_textureValue.HasMember("wrapY"))
	{
		wrapY = GetWrapMode(_textureValue["wrapY"].GetString());
		
#ifdef _DEBUG
		printf(" (Y Wrap: \"%s\" %d)", _textureValue["wrapY"].GetString(), wrapY);
#endif
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapX);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapY);
	
	texture->Unbind();
	
#ifdef _DEBUG
	printf("\n");
#endif
}

std::shared_ptr<GameObject> SceneParser::ParseObject(const std::shared_ptr<Scene>& _scene, rapidjson::Value& _objectValue)
{
	std::shared_ptr<GameObject> gameObject = _scene->CreateGameObject();

	if(_objectValue.HasMember("transform"))
	{
		rapidjson::Value& transform = _objectValue["transform"];
		gameObject->GetTransform()->SetPosition(ParseVector(transform["position"]));
		gameObject->GetTransform()->SetRotation(ParseVector(transform["rotation"]));
		gameObject->GetTransform()->SetScale(ParseVector(transform["scale"]));
	}

	if(_objectValue.HasMember("components"))
	{
		rapidjson::Value& components = _objectValue["components"];
		assert(components.IsArray());
		for (rapidjson::SizeType i = 0; i < components.Size(); i++)
		{
			ParseComponent(gameObject, components[i]);
		}
	}

	if(_objectValue.HasMember("children"))
	{
		rapidjson::Value& children = _objectValue["children"];
		assert(children.IsArray());
		for(rapidjson::SizeType i = 0; i < children.Size(); i++)
		{
			std::shared_ptr<GameObject> child = ParseObject(_scene, children[i]);
			child->GetTransform()->SetParent(gameObject->GetTransform());
		}
	}

	return gameObject;
}

void SceneParser::ParseComponent(const std::shared_ptr<GameObject>& _gameObject, rapidjson::Value& _componentValue)
{
	std::shared_ptr<IJsonParser<IComponent>> parser = m_parsers.at(_componentValue["componentType"].GetString());
	_gameObject->AddComponent(parser->Parse(_componentValue));
}

GLint SceneParser::GetWrapMode(const std::string& _in)
{
	if (_in == "edge") { return(GL_CLAMP_TO_EDGE); }
	if (_in == "border") { return(GL_CLAMP_TO_BORDER); }
	if (_in == "mirror") { return(GL_MIRRORED_REPEAT); }
	if (_in == "repeat") { return(GL_REPEAT); }
	if (_in == "mirrorClamp") { return(GL_MIRROR_CLAMP_TO_EDGE); }
	return(GL_REPEAT);
}
