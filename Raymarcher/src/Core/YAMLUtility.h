#pragma once

#include <glm/glm.hpp>
#include <yaml-cpp/yaml.h>

namespace RM
{
	YAML::Emitter& operator <<(YAML::Emitter& out, const glm::vec3& v);
}

