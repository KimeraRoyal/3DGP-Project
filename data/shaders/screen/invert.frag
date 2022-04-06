#version 330 core
uniform sampler2D in_Texture;

varying vec2 out_TexCoord;

void main()
{
	vec4 tex = texture2D(in_Texture, out_TexCoord);
	gl_FragColor = vec4(1 - tex.rgb, 1);
}