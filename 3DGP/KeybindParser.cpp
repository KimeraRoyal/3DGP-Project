#include "KeybindParser.h"

void KeybindParser::Parse(const std::string& _path, Input& _input) const
{
	rapidjson::Document document = ReadDocument(_path);

	rapidjson::Value& bindings = document["bindings"];
	assert(bindings.IsArray());
	for (rapidjson::SizeType i = 0; i < bindings.Size(); i++)
	{
		rapidjson::Value& binding = bindings[i];
		
#ifdef _DEBUG
		std::printf("Registering binding \"%s\" with scancode %d\n", binding["name"].GetString(), binding["value"].GetUint());
#endif
		
		_input.SetBinding(binding["name"].GetString(), static_cast<SDL_Scancode>(binding["value"].GetUint()));
	}
	
	printf("\n");
}
