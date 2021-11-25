#pragma once

#include "Fractal/IGLSLConvertable.h"
#include <glm/glm.hpp>

namespace RM
{
	class FractalUtility
	{
	public:

		static std::string ColorToGLSL(const IGLSLConvertable& convertable);
		static std::string SubtractVec3(const glm::vec3& vector3);
	};
}