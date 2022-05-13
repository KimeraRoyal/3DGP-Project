#include "FXAA.h"

#include <string>

#include "ShaderProgram.h"
#include "Window.h"

size_t FXAA::s_enabledKey = std::hash<std::string>()("in_Fxaa.enabled");
size_t FXAA::s_lumaThresholdFalloffKey = std::hash<std::string>()("in_Fxaa.lumaThresholdFalloff");
size_t FXAA::s_multiplyReductionKey = std::hash<std::string>()("in_Fxaa.multiplyReduction");
size_t FXAA::s_minimumReductionKey = std::hash<std::string>()("in_Fxaa.minimumReduction");
size_t FXAA::s_maxSpanKey = std::hash<std::string>()("in_Fxaa.maxSpan");
size_t FXAA::s_texelStepKey = std::hash<std::string>()("in_Fxaa.texelStep");

FXAA::FXAA(const bool _enabled, const float _lumaThresholdFalloff, const float _multiplyReduction, const float _minimumReduction, const float _maxSpan)
	: m_enabled(_enabled), m_lumaThresholdFalloff(_lumaThresholdFalloff),
		m_multiplyReduction(_multiplyReduction), m_minimumReduction(_minimumReduction), m_maxSpan(_maxSpan) { }

void FXAA::AssignUniforms(const std::shared_ptr<ShaderProgram>& _program) const
{
	_program->SetUniformValueByKey(s_enabledKey, m_enabled);
	
	_program->SetUniformValueByKey(s_lumaThresholdFalloffKey, m_lumaThresholdFalloff);
	
	_program->SetUniformValueByKey(s_multiplyReductionKey, 1.0f / m_multiplyReduction);
	_program->SetUniformValueByKey(s_minimumReductionKey, 1.0f / m_minimumReduction);
	
	_program->SetUniformValueByKey(s_maxSpanKey, m_maxSpan);
	
	_program->SetUniformValueByKey(s_texelStepKey, 1.0f / static_cast<glm::vec2>(Window::GetInstance()->GetResolution()));
}
