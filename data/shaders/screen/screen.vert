#version 330 core
attribute vec3 in_Position;
attribute vec2 in_TexCoord;

uniform mat4 in_Projection;
uniform mat4 in_Model;

out vec2 TexCoord;

void main()
{
	gl_Position = in_Projection * in_Model * vec4(in_Position, 1.0);
	TexCoord = in_TexCoord;
}