#include "rmpch.h"
#include "Fractal/FractalGeometry.h"
#include "Fractal/FractalUtility.h"

#include <glm/gtx/string_cast.hpp>

namespace RM
{
	FractalGeometry::FractalGeometry(ColorType colorType, const glm::vec3& color)
		:IGLSLConvertable(colorType, AttributeType::Geometry, color)
	{

	}
	Box::Box(ColorType colorType, const glm::vec3& scale, const glm::vec3& offset, const glm::vec3& color)
		:FractalGeometry(colorType, color), m_Scale(scale), m_Offset(offset)
	{

	}

	std::string Box::TransformationToGLSL() const
	{
		std::stringstream ss;

		ss << "DE_Box(position" << FractalUtility::SubtractVec3(m_Offset) << ", " << glm::to_string(m_Scale) << ")";

		return ss.str();
	}

	std::string Box::ColorToGLSL() const
	{
		return FractalUtility::ColorToGLSL(*this);
	}

	void Box::Serialize(YAML::Emitter& out)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Type" << YAML::Value << ToString();
		out << YAML::Key << "Fields" << YAML::Value << YAML::BeginMap;

		out << YAML::Key << "Scale" << YAML::Value << m_Scale;
		out << YAML::Key << "Offset" << YAML::Value << m_Offset;
		out << YAML::Key << "Color" << YAML::Value << m_Color;
		out << YAML::Key << "ColorType" << YAML::Value << (int)m_ColorType;

		out << YAML::EndMap;
		out << YAML::EndMap;
	}

	Sphere::Sphere(ColorType colorType, float radius, const glm::vec3& center, const glm::vec3& color)
		:FractalGeometry(colorType, color), m_Radius(radius), m_Center(center)
	{
	}

	std::string Sphere::TransformationToGLSL() const
	{
		std::stringstream ss;
		ss << "DE_Sphere(position" << FractalUtility::SubtractVec3(m_Center) << ", " << std::to_string(m_Radius) << ")";

		return ss.str();
	}

	std::string Sphere::ColorToGLSL() const
	{
		return FractalUtility::ColorToGLSL(*this);
	}

	void Sphere::Serialize(YAML::Emitter& out)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Type" << YAML::Value << ToString();
		out << YAML::Key << "Fields" << YAML::Value << YAML::BeginMap;

		out << YAML::Key << "Radius" << YAML::Value << m_Radius;
		out << YAML::Key << "Center" << YAML::Value << m_Center;
		out << YAML::Key << "Color" << YAML::Value << m_Color;
		out << YAML::Key << "ColorType" << YAML::Value << (int)m_ColorType;

		out << YAML::EndMap;
		out << YAML::EndMap;
	}

	Tetrahedron::Tetrahedron(ColorType colorType, float radius, const glm::vec3& center, const glm::vec3& color)
		:FractalGeometry(colorType, color), m_Radius(radius), m_Center(center)
	{
	}

	std::string Tetrahedron::TransformationToGLSL() const
	{
		std::stringstream ss; 
		ss << "\tDE_Tetrahedron(position" << FractalUtility::SubtractVec3(m_Center) << ", " << std::to_string(m_Radius) << ")";
		return ss.str();
	}

	std::string Tetrahedron::ColorToGLSL() const
	{
		return FractalUtility::ColorToGLSL(*this);
	}

	void Tetrahedron::Serialize(YAML::Emitter& out)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Type" << YAML::Value << ToString();
		out << YAML::Key << "Fields" << YAML::Value << YAML::BeginMap;

		out << YAML::Key << "Radius" << YAML::Value << m_Radius;
		out << YAML::Key << "Center" << YAML::Value << m_Center;
		out << YAML::Key << "Color" << YAML::Value << m_Color;
		out << YAML::Key << "ColorType" << YAML::Value << (int)m_ColorType;

		out << YAML::EndMap;
		out << YAML::EndMap;
	}
}