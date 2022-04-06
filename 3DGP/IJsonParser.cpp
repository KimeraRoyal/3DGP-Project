#include "IJsonParser.h"

glm::vec3 JsonParser::ParseVector(rapidjson::Value& _value)
{
	glm::vec3 vector(0.0f);
	vector.x = _value[0].GetFloat();
	vector.y = _value[1].GetFloat();
	vector.z = _value[2].GetFloat();
	return vector;
}