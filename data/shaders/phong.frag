#version 330 core
struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

uniform sampler2D in_Texture;

uniform vec3 in_ViewPos;
uniform vec3 in_LightPos;

uniform Material in_Material;

varying vec2 out_TexCoord;

varying vec3 out_Normal;
varying vec3 out_FragPos;

void main()
{
	vec3 ambient = in_Material.ambient;

	vec3 normal = normalize(out_Normal);
	
	vec3 lightDir = normalize(in_LightPos - out_FragPos);
	vec3 viewDir = normalize(in_ViewPos - out_FragPos);
	
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = in_Material.diffuse * diff;

	vec3 halfwayDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(normal, halfwayDir), 0.0), in_Material.shininess);
	vec3 specular = in_Material.specular * spec;

	vec3 lighting = min(ambient + diffuse + specular, 1.0);
	vec4 tex = texture2D(in_Texture, out_TexCoord);
	gl_FragColor = vec4(lighting, 1) * tex;
}