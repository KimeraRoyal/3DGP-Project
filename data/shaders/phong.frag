#version 120
uniform sampler2D in_Texture;

varying vec2 out_TexCoord;

varying vec3 out_Normal;
varying vec3 out_FragPos;

void main()
{
	vec3 lightPos = vec3(5, 10, 10);
	vec3 ambientColor = vec3(0.1, 0, 0.3);
	vec3 diffuseColor = vec3(1, 1, 1);
	vec3 specularColor = vec3(1, 0, 0);

	vec3 normal = normalize(out_Normal);
	vec3 lightDir = normalize(lightPos - out_FragPos);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diffuseColor * diff;

	vec3 viewPos = vec3(0, 0, 0);
	vec3 viewDir = normalize(viewPos - out_FragPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = spec * specularColor;

	vec3 lighting = min(ambientColor + diffuse + specular, 1.0);
	vec4 tex = texture2D(in_Texture, out_TexCoord);
	gl_FragColor = vec4(lighting, 1) * tex;
}