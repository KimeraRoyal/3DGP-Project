#include "KeybindParser.h"

void KeybindParser::Parse(const std::string& _path, Input& _input) const
{
	rapidjson::Document document = ReadDocument(_path);

	if (document.HasMember("bindings"))
	{
		rapidjson::Value& bindings = document["bindings"];
		ParseBindings(bindings, _input);
	}
	
	if (document.HasMember("axis"))
	{
		rapidjson::Value& axis = document["axis"];
		ParseAxis(axis, _input);
	}

#ifdef _DEBUG
	printf("\n");
#endif
}

void KeybindParser::ParseBindings(rapidjson::Value& _bindings, Input& _input) const
{
	assert(_bindings.IsArray());
	
#ifdef _DEBUG
	std::printf("Registering bindings:");
#endif

	for (rapidjson::SizeType i = 0; i < _bindings.Size(); i++)
	{
#ifdef _DEBUG
		if (i > 0) { std::printf(","); }
#endif
		rapidjson::Value& binding = _bindings[i];

		std::string name = binding["name"].GetString();
		const SDL_Scancode value = static_cast<SDL_Scancode>(binding["value"].GetUint());
		SDL_Scancode alt = SDL_SCANCODE_UNKNOWN;

#ifdef _DEBUG
		std::printf(" \"%s\": %d", name.c_str(), value);
#endif

		if (binding.HasMember("alt"))
		{
			alt = static_cast<SDL_Scancode>(binding["alt"].GetUint());

#ifdef _DEBUG
			std::printf(" (alt: %d)", alt);
#endif
		}

		_input.SetBinding(name, value, alt);
	}
	
#ifdef _DEBUG
	printf("\n");
#endif
}

void KeybindParser::ParseAxis(rapidjson::Value& _axis, Input& _input) const
{
	assert(_axis.IsArray());

#ifdef _DEBUG
	std::printf("Registering axis:");
#endif

	for(rapidjson::SizeType i = 0; i < _axis.Size(); i++)
	{
#ifdef _DEBUG
		if (i > 0) { std::printf(","); }
#endif
		rapidjson::Value& axis = _axis[i];

		std::string name = axis["name"].GetString();
		std::string negative = axis["negative"].GetString();
		std::string positive = axis["positive"].GetString();

#ifdef _DEBUG
		std::printf(" \"%s\": \"%s\" <-> \"%s\"", name.c_str(), negative.c_str(), positive.c_str());
#endif

		_input.SetInputAxis(name, negative, positive);
	}

#ifdef _DEBUG
	printf("\n");
#endif
}
