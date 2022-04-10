#include "KeybindParser.h"

void KeybindParser::Parse(const std::string& _path, Input& _input) const
{
	rapidjson::Document document = ReadDocument(_path);

	rapidjson::Value& bindings = document["bindings"];
	assert(bindings.IsArray());

#ifdef _DEBUG
	std::printf("Registering bindings:");
#endif
	
	for (rapidjson::SizeType i = 0; i < bindings.Size(); i++)
	{
#ifdef _DEBUG
		if (i > 0) { std::printf(","); }
#endif
		rapidjson::Value& binding = bindings[i];

		std::string name = binding["name"].GetString();
		const SDL_Scancode value = static_cast<SDL_Scancode>(binding["value"].GetUint());
		SDL_Scancode alt = SDL_SCANCODE_UNKNOWN;
		
#ifdef _DEBUG
		std::printf(" \"%s\": %d", name.c_str(), value);
#endif

		if(binding.HasMember("alt"))
		{
			alt = static_cast<SDL_Scancode>(binding["alt"].GetUint());
			
#ifdef _DEBUG
			std::printf(" (alt: %d)", alt);
#endif
		}
		
		_input.SetBinding(name, value, alt);
	}
	
	printf("\n");
}
