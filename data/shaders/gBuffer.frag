#version 330 core
struct Material
{
	vec3 specular;
	float shininess;
};

uniform Material in_Material;

uniform sampler2D in_Texture;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

layout (location = 0) out vec4 g_Position;
layout (location = 1) out vec4 g_Normal;
layout (location = 2) out vec4 g_Specular;
layout (location = 3) out vec4 g_Albedo;

void main()
{
	g_Position = vec4(FragPos, 1);
	g_Normal = vec4(normalize(Normal), 1);
	g_Specular = vec4(in_Material.specular, in_Material.shininess / 256.0);
	g_Albedo = texture(in_Texture, TexCoord);
}