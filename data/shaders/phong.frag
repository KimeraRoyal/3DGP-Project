#version 330 core
struct Material
{
	sampler2D diffuse;
	vec3 specular;
	float shininess;
};

struct AmbientLight
{
	vec3 ambient;
};

struct DirectionalLight
{
	vec3 direction;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight
{
	vec3 position;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	float radius;
};

struct SpotLight
{
	vec3 position;
	vec3 direction;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	float innerCutoff;
	float outerCutoff;
};

uniform vec3 in_ViewPos;

uniform Material in_Material;

uniform AmbientLight in_AmbientLight;
uniform DirectionalLight in_DirLight;
uniform PointLight in_PointLight;
uniform SpotLight in_SpotLight;

in vec2 TexCoord;

in vec3 Normal;
in vec3 FragPos;

vec3 ambient(vec4 _tex, AmbientLight _light);
vec3 directional(vec4 _tex, DirectionalLight _light, vec3 _normal, vec3 _viewDir);
vec3 point(vec4 _tex, PointLight _light, vec3 _normal, vec3 _fragPos, vec3 _viewDir);
vec3 spot(vec4 _tex, SpotLight _light, vec3 _normal, vec3 _fragPos, vec3 _viewDir);

void main()
{
	vec4 tex = texture2D(in_Material.diffuse, TexCoord);
	
	vec3 normal = normalize(Normal);
	vec3 viewDir = normalize(in_ViewPos - FragPos);

	vec3 result = vec3(0.0);
	result += ambient(tex, in_AmbientLight);
	
	// Loop through all directional lights
	result += directional(tex, in_DirLight, normal, viewDir);
	
	// Loop through all point lights
	result += point(tex, in_PointLight, normal, FragPos, viewDir);
	
	// Loop through all spot lights
	result += spot(tex, in_SpotLight, normal, FragPos, viewDir);
	
	gl_FragColor = vec4(result, 1.0);
}

vec3 ambient(vec4 _tex, AmbientLight _light)
{
	vec3 ambient = _light.ambient * vec3(_tex);
	return ambient;
}

vec3 directional(vec4 _tex, DirectionalLight _light, vec3 _normal, vec3 _viewDir)
{
	vec3 lightDir = normalize(-_light.direction);
	
	float diff = max(dot(_normal, lightDir), 0.0);

	vec3 halfwayDir = normalize(lightDir + _viewDir);
	float spec = pow(max(dot(_normal, halfwayDir), 0.0), in_Material.shininess);
	
	vec3 ambient = _light.ambient * vec3(_tex);
	vec3 diffuse = _light.diffuse * diff * vec3(_tex);
	vec3 specular = _light.specular * spec * in_Material.specular;

	return ambient + diffuse + specular;
}

vec3 point(vec4 _tex, PointLight _light, vec3 _normal, vec3 _fragPos, vec3 _viewDir)
{
	vec3 lightDir = _light.position - _fragPos;
	float distance = length(lightDir);
	float d = max(distance - _light.radius, 0);
	lightDir = normalize(lightDir);
	
	float diff = max(dot(_normal, lightDir), 0.0);

	vec3 halfwayDir = normalize(lightDir + _viewDir);
	float spec = pow(max(dot(_normal, halfwayDir), 0.0), in_Material.shininess);
	
	vec3 ambient = _light.ambient * vec3(_tex);
	vec3 diffuse = _light.diffuse * diff * vec3(_tex);
	vec3 specular = _light.specular * spec * in_Material.specular;
	
	float denom = d / _light.radius + 1;
	float attenuation = 1 / (denom * denom);
	
	float cutoff = 0.001;
	attenuation = (attenuation - cutoff) / (1 - cutoff);
	attenuation = max(attenuation, 0.0);
	
	return attenuation * (ambient + diffuse + specular);
}

vec3 spot(vec4 _tex, SpotLight _light, vec3 _normal, vec3 _fragPos, vec3 _viewDir)
{
	vec3 lightDir = normalize(_light.position - _fragPos);
	
	float diff = max(dot(_normal, lightDir), 0.0);

	vec3 halfwayDir = normalize(lightDir + _viewDir);
	float spec = pow(max(dot(_normal, halfwayDir), 0.0), in_Material.shininess);
	
	vec3 ambient = _light.ambient * vec3(_tex);
	vec3 diffuse = _light.diffuse * diff * vec3(_tex);
	vec3 specular = _light.specular * spec * in_Material.specular;
	
	float theta = dot(lightDir, normalize(-_light.direction));
	float epsilon = _light.innerCutoff - _light.outerCutoff;
	float intensity = clamp((theta - _light.outerCutoff) / epsilon, 0.0, 1.0);
	
	return intensity * (ambient + diffuse + specular);
}