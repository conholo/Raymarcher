#include "rmpch.h"
#include "Fractal/Folds/Folds.h"

#include "Fractal/FractalUtility.h"
#include <glm/gtx/string_cast.hpp>

namespace RM
{
	Fold::Fold()
		:IGLSLConvertable(ColorType::None, AttributeType::Fold)
	{
	}

	std::string FoldScaleTranslate::TransformationToGLSL() const
	{
		std::stringstream ss;

		if (m_Scale != 1.0)
		{
			if (m_Scale >= 0)
			{
				ss << "\tposition *= " << std::to_string(m_Scale) << ";\n";
			}
			else
			{
				ss << "\tposition.xyz *= " << std::to_string(m_Scale) << ";\n";
				ss << "\tposition.w *= abs(" << std::to_string(m_Scale) << ");\n";
			}
		}
		if(m_Translation != glm::vec3(0.0f))
		{
			ss << "\tposition.xyz += " << glm::to_string(m_Translation) << ";\n";
		}

		return ss.str();
	}

	std::string FoldPlane::TransformationToGLSL() const
	{
		switch (m_Direction)
		{
			case FoldDirection::Right:		return "\tposition.x = abs(position.x - " + std::to_string(m_Factor) + ") + " + std::to_string(m_Factor) + ";\n";
			case FoldDirection::Up:			return "\tposition.y = abs(position.y - " + std::to_string(m_Factor) + ") + " + std::to_string(m_Factor) + ";\n";
			case FoldDirection::Forward:	return "\tposition.z = abs(position.z - " + std::to_string(m_Factor) + ") + " + std::to_string(m_Factor) + ";\n";
			case FoldDirection::Left:		return "\tposition.x = -abs(position.x + " + std::to_string(m_Factor) + ") - " + std::to_string(m_Factor) + ";\n";
			case FoldDirection::Down:		return "\tposition.y = -abs(position.y + " + std::to_string(m_Factor) + ") - " + std::to_string(m_Factor) + ";\n";
			case FoldDirection::Back:		return "\tposition.z = -abs(position.z + " + std::to_string(m_Factor) + ") - " + std::to_string(m_Factor) + ";\n";
			case FoldDirection::None:		return "";
		}

		return "";
	}

	std::string FoldMenger::TransformationToGLSL() const
	{
		return "\tMengerFold(position);\n";
	}


	std::string FoldSierpinski::TransformationToGLSL() const
	{
		return "\SierpinskiFold(position);\n";
	}

	std::string FoldBox::TransformationToGLSL() const
	{
		return "\tBoxFold(position, " + glm::to_string(m_Range) + ");\n";
	}

	std::string FoldSphere::TransformationToGLSL() const
	{
		return "\tSphereFold(position, " + std::to_string(m_MinRadius) + ", " + std::to_string(m_MaxRadius) + ");\n";
	}

	std::string FoldAbs::TransformationToGLSL() const
	{
		return "\tAbsFold(position, " + glm::to_string(m_Center) + ");\n";
	}

	std::string FoldInversion::TransformationToGLSL() const
	{	
		return "\tposition *= 1.0 / (dot(position.xyz, position.xyz) + " + std::to_string(m_Epsilon) + ");\n";
	}

	std::string FoldRotateX::TransformationToGLSL() const
	{
		return "\tRotationXFold(position, " + std::to_string(glm::sin(m_Radians)) + ", " + std::to_string(glm::cos(m_Radians)) + ");\n";
	}

	std::string FoldRotateY::TransformationToGLSL() const
	{
		return "\tRotationYFold(position, " + std::to_string(glm::sin(m_Radians)) + ", " + std::to_string(glm::cos(m_Radians)) + ");\n";
	}

	std::string FoldRotateZ::TransformationToGLSL() const
	{
		return "\tRotationZFold(position, " + std::to_string(glm::sin(m_Radians)) + ", " + std::to_string(glm::cos(m_Radians)) + ");\n";
	}

	std::string FoldRepeatX::TransformationToGLSL() const
	{
		return "\tposition.x = abs(mod(position.x - " + std::to_string(m_Step) + " / 2, " + std::to_string(m_Step) + ") - " + std::to_string(m_Step) + " / 2);\n";
	}

	std::string FoldRepeatY::TransformationToGLSL() const
	{
		return "\tposition.y = abs(mod(position.y - " + std::to_string(m_Step) + " / 2, " + std::to_string(m_Step) + ") - " + std::to_string(m_Step) + " / 2);\n";
	}

	std::string FoldRepeatZ::TransformationToGLSL() const
	{
		return "\tposition.z = abs(mod(position.z - " + std::to_string(m_Step) + " / 2, " + std::to_string(m_Step) + ") - " + std::to_string(m_Step) + " / 2);\n";
	}

	std::string FoldRepeatXYZ::TransformationToGLSL() const
	{
		return "\tposition.xyz = abs(mod(position.xyz - " + std::to_string(m_Step) + " / 2, " + std::to_string(m_Step) + ") - " + std::to_string(m_Step) + " / 2);\n";
	}

	std::string FoldScaleOrigin::TransformationToGLSL() const
	{
		return "\tposition = position * " + std::to_string(m_Scale) + "; position.w = abs(position.w); position += o;\n";
	}

	void FoldScaleTranslate::Serialize(YAML::Emitter& out)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Type" << YAML::Value << ToString();
		out << YAML::Key << "Fields" << YAML::Value << YAML::BeginMap;

		out << YAML::Key << "Scale" << YAML::Value << m_Scale;
		out << YAML::Key << "Translation" << YAML::Value << m_Translation;

		out << YAML::EndMap;
		out << YAML::EndMap;
	}

	void FoldScaleOrigin::Serialize(YAML::Emitter& out)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Type" << YAML::Value << ToString();
		out << YAML::Key << "Fields" << YAML::Value << YAML::BeginMap;

		out << YAML::Key << "Scale" << YAML::Value << m_Scale;
		out << YAML::Key << "Origin" << YAML::Value << m_Origin;

		out << YAML::EndMap;
		out << YAML::EndMap;
	}

	void FoldPlane::Serialize(YAML::Emitter& out)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Type" << YAML::Value << ToString();
		out << YAML::Key << "Fields" << YAML::Value << YAML::BeginMap;

		out << YAML::Key << "Factor" << YAML::Value << m_Factor;
		out << YAML::Key << "Direction" << YAML::Value << (int)m_Direction;

		out << YAML::EndMap;
		out << YAML::EndMap;
	}

	void FoldMenger::Serialize(YAML::Emitter& out)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Type" << YAML::Value << ToString();
		out << YAML::EndMap;
	}

	void FoldSierpinski::Serialize(YAML::Emitter& out)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Type" << YAML::Value << ToString();
		out << YAML::EndMap;
	}

	void FoldBox::Serialize(YAML::Emitter& out)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Type" << YAML::Value << ToString();
		out << YAML::Key << "Fields" << YAML::Value << YAML::BeginMap;

		out << YAML::Key << "Range" << YAML::Value << m_Range;

		out << YAML::EndMap;
		out << YAML::EndMap;
	}

	void FoldSphere::Serialize(YAML::Emitter& out)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Type" << YAML::Value << ToString();
		out << YAML::Key << "Fields" << YAML::Value << YAML::BeginMap;

		out << YAML::Key << "Min Radius" << YAML::Value << m_MinRadius;
		out << YAML::Key << "Max Radius" << YAML::Value << m_MaxRadius;

		out << YAML::EndMap;
		out << YAML::EndMap;
	}

	void FoldAbs::Serialize(YAML::Emitter& out)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Type" << YAML::Value << ToString();
		out << YAML::Key << "Fields" << YAML::Value << YAML::BeginMap;

		out << YAML::Key << "Center" << YAML::Value << m_Center;

		out << YAML::EndMap;
		out << YAML::EndMap;
	}

	void FoldInversion::Serialize(YAML::Emitter& out)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Type" << YAML::Value << ToString();
		out << YAML::Key << "Fields" << YAML::Value << YAML::BeginMap;

		out << YAML::Key << "Epsilon" << YAML::Value << m_Epsilon;

		out << YAML::EndMap;
		out << YAML::EndMap;
	}

	void FoldRotateX::Serialize(YAML::Emitter& out)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Type" << YAML::Value << ToString();
		out << YAML::Key << "Fields" << YAML::Value << YAML::BeginMap;

		out << YAML::Key << "Radians" << YAML::Value << m_Radians;

		out << YAML::EndMap;
		out << YAML::EndMap;
	}

	void FoldRotateY::Serialize(YAML::Emitter& out)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Type" << YAML::Value << ToString();
		out << YAML::Key << "Fields" << YAML::Value << YAML::BeginMap;

		out << YAML::Key << "Radians" << YAML::Value << m_Radians;

		out << YAML::EndMap;
		out << YAML::EndMap;
	}

	void FoldRotateZ::Serialize(YAML::Emitter& out)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Type" << YAML::Value << ToString();
		out << YAML::Key << "Fields" << YAML::Value << YAML::BeginMap;

		out << YAML::Key << "Radians" << YAML::Value << m_Radians;

		out << YAML::EndMap;
		out << YAML::EndMap;
	}

	void FoldRepeatX::Serialize(YAML::Emitter& out)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Type" << YAML::Value << ToString();
		out << YAML::Key << "Fields" << YAML::Value << YAML::BeginMap;

		out << YAML::Key << "Step" << YAML::Value << m_Step;

		out << YAML::EndMap;
		out << YAML::EndMap;
	}

	void FoldRepeatY::Serialize(YAML::Emitter& out)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Type" << YAML::Value << ToString();
		out << YAML::Key << "Fields" << YAML::Value << YAML::BeginMap;

		out << YAML::Key << "Step" << YAML::Value << m_Step;

		out << YAML::EndMap;
		out << YAML::EndMap;
	}

	void FoldRepeatZ::Serialize(YAML::Emitter& out)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Type" << YAML::Value << ToString();
		out << YAML::Key << "Fields" << YAML::Value << YAML::BeginMap;

		out << YAML::Key << "Step" << YAML::Value << m_Step;

		out << YAML::EndMap;
		out << YAML::EndMap;
	}

	void FoldRepeatXYZ::Serialize(YAML::Emitter& out)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Type" << YAML::Value << ToString();
		out << YAML::Key << "Fields" << YAML::Value << YAML::BeginMap;

		out << YAML::Key << "Step" << YAML::Value << m_Step;

		out << YAML::EndMap;
		out << YAML::EndMap;
	}
}