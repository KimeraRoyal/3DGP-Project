#version 330 core
uniform sampler2D g_Position;
uniform sampler2D g_Normal;
uniform sampler2D g_Albedo;

uniform vec3 in_ViewPos;

in vec2 TexCoord;

out vec4 FragColor;

void main()
{
	vec3 FragPos = texture(g_Position, TexCoord).rgb;
	vec3 Normal = texture(g_Normal, TexCoord).rgb;
	vec3 Albedo = texture(g_Albedo, TexCoord).rgb;
	
	FragColor = vec4(FragPos * Normal * Albedo, 1.0);
}