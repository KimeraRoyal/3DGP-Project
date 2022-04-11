#pragma once
#include <string>

struct InputAxis
{
private:
	size_t m_negative;
	size_t m_positive;
public:
	InputAxis(const std::string& _negative, const std::string& _positive)
		: m_negative(std::hash<std::string>()(_negative)), m_positive(std::hash<std::string>()(_positive)) {}

	[[nodiscard]] size_t GetNegative() const { return m_negative; }
	[[nodiscard]] size_t GetPositive() const { return m_positive; }
};
