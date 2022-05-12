#include "IJsonParser.h"

#include <stdexcept>
#include <sstream>

#include "File.h"

rapidjson::Document JsonParser::ReadDocument(const std::string& _path) const
{
	const std::string text = File::LoadTextFile(File::EvaluatePath(_path));

	rapidjson::Document document;
	document.Parse(text.c_str());
	if (document.HasParseError())
	{
#ifdef _DEBUG
		std::stringstream lineStream(text);
		std::string lineSegment, prevLineSegment;
		int lines = 0;
		unsigned int characters = 0;
		while (std::getline(lineStream, lineSegment, '\n'))
		{
			characters += lineSegment.size();
			if (characters >= document.GetErrorOffset()) { break; }
			prevLineSegment = lineSegment;
			lines++;
		}
		std::printf("JSON Parse Error: Code %d (%u): \"%s\"\n", document.GetParseError(), lines, prevLineSegment.c_str());
#endif
		throw std::runtime_error("Failed to parse JSON file! JSON Parse Error, Code: " + document.GetParseError());
	}

	return document;
}

glm::vec2 JsonParser::ParseVector2(rapidjson::Value& _value)
{
	glm::vec3 vector(0.0f);
	for (size_t i = 0; i < 2; i++)
	{
		vector[i] = _value[i].GetFloat();
	}
	return vector;
}

glm::vec3 JsonParser::ParseVector3(rapidjson::Value& _value)
{
	glm::vec3 vector(0.0f);
	for (size_t i = 0; i < 3; i++)
	{
		vector[i] = _value[i].GetFloat();
	}
	return vector;
}

glm::ivec2 JsonParser::ParseIVector2(rapidjson::Value& _value)
{
	glm::ivec3 vector(0.0f);
	for (size_t i = 0; i < 2; i++)
	{
		vector[i] = _value[i].GetInt();
	}
	return vector;
}

glm::ivec3 JsonParser::ParseIVector3(rapidjson::Value& _value)
{
	glm::ivec3 vector(0.0f);
	for (size_t i = 0; i < 3; i++)
	{
		vector[i] = _value[i].GetInt();
	}
	return vector;
}

glm::uvec2 JsonParser::ParseUVector2(rapidjson::Value& _value)
{
	glm::ivec3 vector(0.0f);
	for (size_t i = 0; i < 2; i++)
	{
		vector[i] = _value[i].GetUint();
	}
	return vector;
}

glm::uvec3 JsonParser::ParseUVector3(rapidjson::Value& _value)
{
	glm::ivec3 vector(0.0f);
	for(size_t i = 0; i < 3; i++)
	{
		vector[i] = _value[i].GetUint();
	}
	return vector;
}