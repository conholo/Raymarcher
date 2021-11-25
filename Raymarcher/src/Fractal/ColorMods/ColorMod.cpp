#include "rmpch.h"
#include "Fractal/ColorMods/ColorMod.h"

#include <glm/gtx/string_cast.hpp>

namespace RM
{
	ColorMod::ColorMod()
		:IGLSLConvertable(ColorType::None, AttributeType::ColorMod)
	{
	}

	std::string ColorModZero::ColorModToGLSL() const
	{
		return "\tvec3 orbit = vec3(0.0);\n";
	}

	std::string ColorModInfinity::ColorModToGLSL() const
	{
		return "\tvec3 orbit = vec3(1e20);\n";
	}

	std::string ColorModNegativeInfinity::ColorModToGLSL() const
	{
		return "\tvec3 orbit = vec3(-1e20);\n";
	}

	std::string ColorModSum::ColorModToGLSL() const
	{
		return "\torbit += (position.xyz - " + glm::to_string(m_Origin) + ") * " + glm::to_string(m_Scale) + ";\n";
	}

	std::string ColorModSumAbs::ColorModToGLSL() const
	{
		return "\torbit += abs((position.xyz - " + glm::to_string(m_Origin) + ") * " + glm::to_string(m_Scale) + ");\n";
	}

	std::string ColorModMinAbs::ColorModToGLSL() const
	{
		return "\torbit = min(orbit, abs((position.xyz - " + glm::to_string(m_Origin) + ") * " + glm::to_string(m_Scale) + "));\n";
	}

	std::string ColorModMin::ColorModToGLSL() const
	{
		return "\torbit = min(orbit, abs(position.xyz - " + glm::to_string(m_Origin) + ") * " + glm::to_string(m_Scale) + ");\n";
	}

	std::string ColorModMax::ColorModToGLSL() const
	{
		return "\torbit = max(orbit, abs(position.xyz - " + glm::to_string(m_Origin) + ") * " + glm::to_string(m_Scale) + ");\n";
	}

	std::string ColorModMaxAbs::ColorModToGLSL() const
	{
		return "\torbit = max(orbit, abs((position.xyz - " + glm::to_string(m_Origin) + ") * " + glm::to_string(m_Scale) + "));\n";
	}
}