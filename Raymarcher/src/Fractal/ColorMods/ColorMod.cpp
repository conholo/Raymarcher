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

	void ColorModZero::Serialize(YAML::Emitter& out)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Type" << YAML::Value << ToString();
		out << YAML::EndMap;
	}

	std::string ColorModInfinity::ColorModToGLSL() const
	{
		return "\tvec3 orbit = vec3(1e20);\n";
	}

	void ColorModInfinity::Serialize(YAML::Emitter& out)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Type" << YAML::Value << ToString();
		out << YAML::EndMap;
	}

	std::string ColorModNegativeInfinity::ColorModToGLSL() const
	{
		return "\tvec3 orbit = vec3(-1e20);\n";
	}

	void ColorModNegativeInfinity::Serialize(YAML::Emitter& out)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Type" << YAML::Value << ToString();
		out << YAML::EndMap;
	}

	std::string ColorModSum::ColorModToGLSL() const
	{
		return "\torbit += (position.xyz - " + glm::to_string(m_Origin) + ") * " + glm::to_string(m_Scale) + ";\n";
	}

	void ColorModSum::Serialize(YAML::Emitter& out)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Type" << YAML::Value << ToString();
		out << YAML::Key << "Fields" << YAML::Value << YAML::BeginMap;

		out << YAML::Key << "Scale" << YAML::Value << m_Scale;
		out << YAML::Key << "Origin" << YAML::Value << m_Origin;

		out << YAML::EndMap;
		out << YAML::EndMap;
	}

	std::string ColorModSumAbs::ColorModToGLSL() const
	{
		return "\torbit += abs((position.xyz - " + glm::to_string(m_Origin) + ") * " + glm::to_string(m_Scale) + ");\n";
	}

	void ColorModSumAbs::Serialize(YAML::Emitter& out)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Type" << YAML::Value << ToString();
		out << YAML::Key << "Fields" << YAML::Value << YAML::BeginMap;

		out << YAML::Key << "Scale" << YAML::Value << m_Scale;
		out << YAML::Key << "Origin" << YAML::Value << m_Origin;

		out << YAML::EndMap;
		out << YAML::EndMap;
	}

	std::string ColorModMinAbs::ColorModToGLSL() const
	{
		return "\torbit = min(orbit, abs((position.xyz - " + glm::to_string(m_Origin) + ") * " + glm::to_string(m_Scale) + "));\n";
	}

	void ColorModMinAbs::Serialize(YAML::Emitter& out)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Type" << YAML::Value << ToString();
		out << YAML::Key << "Fields" << YAML::Value << YAML::BeginMap;

		out << YAML::Key << "Scale" << YAML::Value << m_Scale;
		out << YAML::Key << "Origin" << YAML::Value << m_Origin;

		out << YAML::EndMap;
		out << YAML::EndMap;
	}

	std::string ColorModMin::ColorModToGLSL() const
	{
		return "\torbit = min(orbit, abs(position.xyz - " + glm::to_string(m_Origin) + ") * " + glm::to_string(m_Scale) + ");\n";
	}

	void ColorModMin::Serialize(YAML::Emitter& out)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Type" << YAML::Value << ToString();
		out << YAML::Key << "Fields" << YAML::Value << YAML::BeginMap;

		out << YAML::Key << "Scale" << YAML::Value << m_Scale;
		out << YAML::Key << "Origin" << YAML::Value << m_Origin;

		out << YAML::EndMap;
		out << YAML::EndMap;
	}

	std::string ColorModMax::ColorModToGLSL() const
	{
		return "\torbit = max(orbit, abs(position.xyz - " + glm::to_string(m_Origin) + ") * " + glm::to_string(m_Scale) + ");\n";
	}

	void ColorModMax::Serialize(YAML::Emitter& out)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Type" << YAML::Value << ToString();
		out << YAML::Key << "Fields" << YAML::Value << YAML::BeginMap;

		out << YAML::Key << "Scale" << YAML::Value << m_Scale;
		out << YAML::Key << "Origin" << YAML::Value << m_Origin;

		out << YAML::EndMap;
		out << YAML::EndMap;
	}

	std::string ColorModMaxAbs::ColorModToGLSL() const
	{
		return "\torbit = max(orbit, abs((position.xyz - " + glm::to_string(m_Origin) + ") * " + glm::to_string(m_Scale) + "));\n";
	}

	void ColorModMaxAbs::Serialize(YAML::Emitter& out)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Type" << YAML::Value << ToString();
		out << YAML::Key << "Fields" << YAML::Value << YAML::BeginMap;

		out << YAML::Key << "Scale" << YAML::Value << m_Scale;
		out << YAML::Key << "Origin" << YAML::Value << m_Origin;

		out << YAML::EndMap;
		out << YAML::EndMap;
	}
}