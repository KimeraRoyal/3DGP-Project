#version 330 core
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

struct Material
{
	vec3 specular;
	float shininess;
};

uniform AmbientLight in_AmbientLight;
uniform DirectionalLight in_DirLight;
uniform PointLight in_PointLight;
uniform SpotLight in_SpotLight;

uniform sampler2D g_Position;
uniform sampler2D g_Normal;
uniform sampler2D g_Specular;
uniform sampler2D g_Albedo;

uniform vec3 in_ViewPos;

in vec2 TexCoord;

out vec4 FragColor;

vec3 ambient(vec4 _tex, AmbientLight _light);
vec3 directional(vec4 _tex, DirectionalLight _light, vec3 _normal, vec3 _viewDir, Material _material);
vec3 point(vec4 _tex, PointLight _light, vec3 _normal, vec3 _fragPos, vec3 _viewDir, Material _material);
vec3 spot(vec4 _tex, SpotLight _light, vec3 _normal, vec3 _fragPos, vec3 _viewDir, Material _material);

void main()
{
	vec3 FragPos = texture(g_Position, TexCoord).rgb;
	vec3 Normal = texture(g_Normal, TexCoord).rgb;
	vec4 Specular = texture(g_Specular, TexCoord);
	vec4 Albedo = texture(g_Albedo, TexCoord);
	
	vec3 viewDir = normalize(in_ViewPos - FragPos);
	
	Material material;
	material.specular = Specular.rgb;
	material.shininess = Specular.a * 256.0;
	
	vec3 result = vec3(0.0);
	result += ambient(Albedo, in_AmbientLight);
	
	// Loop through all directional lights
	result += directional(Albedo, in_DirLight, Normal, viewDir, material);
	
	// Loop through all point lights
	result += point(Albedo, in_PointLight, Normal, FragPos, viewDir, material);
	
	// Loop through all spot lights
	result += spot(Albedo, in_SpotLight, Normal, FragPos, viewDir, material);
	
	FragColor = vec4(result, 1.0);
}

vec3 ambient(vec4 _tex, AmbientLight _light)
{
	vec3 ambient = _light.ambient * vec3(_tex);
	return ambient;
}

vec3 directional(vec4 _tex, DirectionalLight _light, vec3 _normal, vec3 _viewDir, Material _material)
{
	vec3 lightDir = normalize(-_light.direction);
	
	float diff = max(dot(_normal, lightDir), 0.0);

	vec3 halfwayDir = normalize(lightDir + _viewDir);
	float spec = pow(max(dot(_normal, halfwayDir), 0.0), _material.shininess);
	
	vec3 ambient = _light.ambient * vec3(_tex);
	vec3 diffuse = _light.diffuse * diff * vec3(_tex);
	vec3 specular = _light.specular * spec * _material.specular;

	return ambient + diffuse + specular;
}

vec3 point(vec4 _tex, PointLight _light, vec3 _normal, vec3 _fragPos, vec3 _viewDir, Material _material)
{
	vec3 lightDir = _light.position - _fragPos;
	float distance = length(lightDir);
	float d = max(distance - _light.radius, 0);
	lightDir = normalize(lightDir);
	
	float diff = max(dot(_normal, lightDir), 0.0);

	vec3 halfwayDir = normalize(lightDir + _viewDir);
	float spec = pow(max(dot(_normal, halfwayDir), 0.0), _material.shininess);
	
	vec3 ambient = _light.ambient * vec3(_tex);
	vec3 diffuse = _light.diffuse * diff * vec3(_tex);
	vec3 specular = _light.specular * spec * _material.specular;
	
	float denom = d / _light.radius + 1;
	float attenuation = 1 / (denom * denom);
	
	float cutoff = 0.001;
	attenuation = (attenuation - cutoff) / (1 - cutoff);
	attenuation = max(attenuation, 0.0);
	
	return attenuation * (ambient + diffuse + specular);
}

vec3 spot(vec4 _tex, SpotLight _light, vec3 _normal, vec3 _fragPos, vec3 _viewDir, Material _material)
{
	vec3 lightDir = normalize(_light.position - _fragPos);
	
	float diff = max(dot(_normal, lightDir), 0.0);

	vec3 halfwayDir = normalize(lightDir + _viewDir);
	float spec = pow(max(dot(_normal, halfwayDir), 0.0), _material.shininess);
	
	vec3 ambient = _light.ambient * vec3(_tex);
	vec3 diffuse = _light.diffuse * diff * vec3(_tex);
	vec3 specular = _light.specular * spec * _material.specular;
	
	float theta = dot(lightDir, normalize(-_light.direction));
	float epsilon = _light.innerCutoff - _light.outerCutoff;
	float intensity = clamp((theta - _light.outerCutoff) / epsilon, 0.0, 1.0);
	
	return intensity * (ambient + diffuse + specular);
}