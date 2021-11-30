#include "rmpch.h"
#include "Core/YAMLUtility.h"

namespace RM
{
	YAML::Emitter& RM::operator<<(YAML::Emitter& out, const glm::vec3& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
		return out;
	}
}

