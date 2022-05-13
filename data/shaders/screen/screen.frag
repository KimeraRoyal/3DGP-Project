#version 330 core
uniform sampler2D in_Texture;

struct FXAA
{
	bool enabled;

	float lumaThresholdFalloff;
	
	float multiplyReduction;
	float minimumReduction;
	
	float maxSpan;

	vec2 texelStep;
};

uniform FXAA in_Fxaa;

in vec2 TexCoord;

vec3 fxaa(FXAA _fxaa, sampler2D _texture, vec2 _texCoord);

void main()
{
	vec3 result;
	if(in_Fxaa.enabled)
	{
		result = fxaa(in_Fxaa, in_Texture, TexCoord);
	}
	else
	{
		result = texture(in_Texture, TexCoord).rgb;
	}
	gl_FragColor = vec4(result, 1.0);
}

vec3 fxaa(FXAA _fxaa, sampler2D _texture, vec2 _texCoord)
{
	const ivec2 offsets[5] = ivec2[5](ivec2(0, 0), ivec2(-1, 1), ivec2(1, 1), ivec2(-1, -1), ivec2(1, -1));
	const vec3 toLuma = vec3(0.299, 0.587, 0.114);
	
	vec3 texels[5];
	texels[0] = textureOffset(_texture, _texCoord, offsets[0]).rgb;
	texels[1] = textureOffset(_texture, _texCoord, offsets[1]).rgb;
	texels[2] = textureOffset(_texture, _texCoord, offsets[2]).rgb;
	texels[3] = textureOffset(_texture, _texCoord, offsets[3]).rgb;
	texels[4] = textureOffset(_texture, _texCoord, offsets[4]).rgb;
	
	float luma[5];
	
	float lumaSum = 0;
	float lumaMin = 1000;
	float lumaMax = -1000;
	
	for(int i = 0; i < 5; i++)
	{
		luma[i] = dot(texels[i], toLuma);
		
		lumaSum += luma[i] * int(i > 0);
		lumaMin = min(lumaMin, luma[i]);
		lumaMax = max(lumaMax, luma[i]);
	}
	
	float thresholdCutoff = int(lumaMax - lumaMin <= lumaMax * _fxaa.lumaThresholdFalloff);
	
	vec2 samplingDirection;
	samplingDirection.y = (luma[1] + luma[2]) - (luma[3] + luma[4]);
	samplingDirection.x = -samplingDirection.x;
	
	float samplingDirectionReduce = max(lumaSum * 0.25 * _fxaa.multiplyReduction, _fxaa.minimumReduction);
	float minimumSamplingDirectionFactor = 1.0 / (min(abs(samplingDirection.x), abs(samplingDirection.y)) + samplingDirectionReduce);
	
	samplingDirection = clamp(samplingDirection * minimumSamplingDirectionFactor, vec2(-_fxaa.maxSpan), vec2(_fxaa.maxSpan)) * _fxaa.texelStep;
	
	vec3 negativeSample = texture(_texture, _texCoord + samplingDirection * (1.0 / 3.0 - 0.5)).rgb;
	vec3 positiveSample = texture(_texture, _texCoord + samplingDirection * (2.0 / 3.0 - 0.5)).rgb;
	
	vec3 twoTab = (negativeSample + positiveSample) * 0.5;
	
	vec3 negativeSampleOuter = texture(_texture, _texCoord + samplingDirection * -0.5).rgb;
	vec3 positiveSampleOuter = texture(_texture, _texCoord + samplingDirection * 0.5).rgb;
	
	vec3 fourTab = (negativeSampleOuter + positiveSampleOuter) * 0.25 + twoTab * 0.5;
	float lumaFourTab = dot(fourTab, toLuma);
	
	int beyondEdge = int(lumaFourTab < lumaMin || lumaFourTab > lumaMax);
	return (twoTab * beyondEdge + fourTab * (1 - beyondEdge)) * (1 - thresholdCutoff) + texels[0] * thresholdCutoff;
}