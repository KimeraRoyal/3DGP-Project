#version 330 core
uniform sampler2D in_Texture;

in vec2 TexCoord;

in vec3 Normal;
in vec3 FragPos;

void main()
{
	vec4 tex = texture2D(in_Texture, TexCoord);
	gl_FragColor = tex;
}