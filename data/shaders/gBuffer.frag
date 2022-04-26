#version 330 core
uniform sampler2D in_Texture;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

layout (location = 0) out vec3 g_Position;
layout (location = 1) out vec3 g_Normal;
layout (location = 2) out vec4 g_Albedo;

void main()
{
	g_Position = FragPos;
	g_Normal = normalize(Normal);
	g_Albedo = texture(in_Texture, TexCoord);
	
}