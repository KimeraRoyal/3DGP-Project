#version 330 core
struct Material
{
	sampler2D diffuse;
	vec3 specular;
	float shininess;
};

struct Light
{
	vec3 position;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform vec3 in_ViewPos;

uniform Material in_Material;
uniform Light in_Light;

varying vec2 out_TexCoord;

varying vec3 out_Normal;
varying vec3 out_FragPos;

void main()
{
	vec4 tex = texture2D(in_Material.diffuse, out_TexCoord);
	vec3 ambient = in_Light.ambient * vec3(tex);

	vec3 normal = normalize(out_Normal);
	
	vec3 lightDir = normalize(in_Light.position - out_FragPos);
	vec3 viewDir = normalize(in_ViewPos - out_FragPos);
	
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = in_Light.diffuse * vec3(tex) * diff;

	vec3 halfwayDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(normal, halfwayDir), 0.0), in_Material.shininess);
	vec3 specular = in_Light.specular * (in_Material.specular * spec);

	vec3 lighting = min(ambient + diffuse + specular, 1.0);
	gl_FragColor = vec4(lighting, 1);
}