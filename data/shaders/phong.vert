#version 330 core
attribute vec3 in_Position;
attribute vec3 in_Normal;
attribute vec2 in_TexCoord;

uniform mat4 in_View;
uniform mat4 in_Projection;
uniform mat4 in_Model;

varying vec2 out_TexCoord;

varying vec3 out_Normal;
varying vec3 out_FragPos;

void main()
{
	gl_Position = in_Projection * in_View * in_Model * vec4(in_Position, 1.0);
	out_TexCoord = in_TexCoord;

	out_Normal = mat3(in_Model) * in_Normal;
	out_FragPos = vec3(in_Model * vec4(in_Position, 1.0));
}