#version 330 core
uniform sampler2D in_Texture;

uniform vec2 in_TexelStep;

in vec2 TexCoord;

vec3 fxaa(sampler2D _texture, vec2 _texCoord);

void main()
{
	gl_FragColor = vec4(fxaa(in_Texture, TexCoord), 1.0);
}

vec3 fxaa(sampler2D _texture, vec2 _texCoord)
{
	vec3 texels[5];
	float luma[5];
	
	float lumaSum = 0;
	float lumaMin = 1000;
	float lumaMax = -1000;
	
	for(int y = 0; y < 2; y++)
	{
		for(int x = 0; x < 2; x++)
		{
			texels[y * 2 + x] = textureOffset(_texture, _texCoord, ivec2(x * 2 - 1, y * -2 + 1)).rgb;
		}
	}
	
	const vec3 toLuma = vec3(0.299, 0.587, 0.114);
	
	for(int i = 0; i < 5; i++)
	{
		luma[i] = dot(texels[i], toLuma);
		
		lumaSum += luma[i];
		lumaMin = min(lumaMin, luma[i]);
		lumaMax = max(lumaMax, luma[i]);
	}
	
	float lumaThresholdFalloff = 0.6;
	float thresholdCutoff = int(lumaMax - lumaMin <= lumaMax * lumaThresholdFalloff);
	
	vec2 samplingDirection;
	samplingDirection.y = (luma[0] + luma[1]) - (luma[2] + luma[3]);
	samplingDirection.x = -samplingDirection.x;
	
	float multiplyReduce = 1.0 / 8.0;
	float minimumReduction = 1.0 / 64.0;
	
	float samplingDirectionReduce = max(lumaSum * 0.25 * multiplyReduce, minimumReduction);
	float minimumSamplingDirectionFactor = 1.0 / (min(abs(samplingDirection.x), abs(samplingDirection.y)) + samplingDirectionReduce);
	
	float maxSpan = 8.0;
	
	samplingDirection = clamp(samplingDirection * minimumSamplingDirectionFactor, vec2(-maxSpan), vec2(maxSpan)) * in_TexelStep;
	
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