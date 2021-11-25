#include "rmpch.h"
#include "Fractal/FractalUtility.h"

#include <glm/gtx/string_cast.hpp>

namespace RM
{
	std::string FractalUtility::ColorToGLSL(const IGLSLConvertable& convertable)
	{	
		std::stringstream ss;

		switch (convertable.GetColorType())
		{
			case ColorType::ColorMod:
			{
				ss << "vec4(orbit, " << convertable.TransformationToGLSL() << ")";
				break;
			}
			case ColorType::FromVec3Color:
			{
				ss << "vec4(" << glm::to_string(convertable.GetColor()) << "," << convertable.TransformationToGLSL() << ")";
				break;
			}
			case ColorType::None:
			{
				ss << "";
				break;
			}
		}

		return ss.str();
	}

	std::string FractalUtility::SubtractVec3(const glm::vec3& vector3)
	{
		std::stringstream ss;

		ss << " - vec4(" << glm::to_string(vector3) << ", 0.0)";

		return ss.str();
	}
}

