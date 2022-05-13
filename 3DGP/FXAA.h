#pragma once

#include <memory>

class ShaderProgram;

class FXAA
{
private:
	static size_t s_enabledKey;
	static size_t s_lumaThresholdFalloffKey;
	static size_t s_multiplyReductionKey;
	static size_t s_minimumReductionKey;
	static size_t s_maxSpanKey;
	static size_t s_texelStepKey;

	bool m_enabled;

	float m_lumaThresholdFalloff;
	
	float m_multiplyReduction;
	float m_minimumReduction;

	float m_maxSpan;
public:
	FXAA(bool _enabled, float _lumaThresholdFalloff, float _multiplyReduction, float _minimumReduction, float _maxSpan);
	
	void AssignUniforms(const std::shared_ptr<ShaderProgram>& _program) const;

	bool GetEnabled() const { return m_enabled; }

	float GetLumaThresholdFalloff() const { return m_lumaThresholdFalloff; }

	float GetMultiplyReduction() const { return m_multiplyReduction; }
	float GetMinimumReduction() const { return m_minimumReduction; }

	float GetMaxSpan() const { return m_maxSpan; }

	void SetEnabled(const bool _enabled) { m_enabled = _enabled; }

	void SetLumaThresholdFalloff(const float _lumaThresholdFalloff) { m_lumaThresholdFalloff = _lumaThresholdFalloff; }

	void SetMultiplyReduction(const float _multiplyReduction) { m_multiplyReduction = _multiplyReduction; }
	void SetMinimumReduction(const float _minimumReduction) { m_minimumReduction = _minimumReduction; }

	void SetMaxSpan(const float _maxSpan) { m_maxSpan = _maxSpan; }
};

