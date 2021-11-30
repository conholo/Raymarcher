#pragma once

#include <glm/glm.hpp>

namespace RM
{
	enum class ShaderDefineType
	{
		AA_SAMPLES,
		AO_STRENGTH,
		AO_COLOR_DELTA,
		BG_COLOR,
		DOF_STRENGTH,
		DOF_DISTANCE,
		EXPOSURE,
		FOV,
		FOG_ENABLED,
		GAMMA_CORRECTION,
		GLOW_ENABLED,
		GLOW_COLOR_DELTA,
		GLOW_SHARPNESS,
		LIGHT_COLOR,
		LIGHT_POSITION,
		LOD_MULTIPLIER,
		MAX_MARCHES,
		MAX_DISTANCE,
		MIN_DISTANCE,
		MOTION_BLUR_LEVEL,
		MOTION_BLUR_RATIO,
		REFLECTION_LEVEL,
		REFLECTION_ATTENUATION,
		SUN_ENABLED,
		SUN_SIZE,
		SUN_SHARPNESS,
		SHADOWS_ENABLED,
		SHADOW_DARKNESS,
		SHADOW_SHARPNESS,
		SPECULAR_HIGHTLIGHT,
	};

	class FractalDefines
	{
	public:

		FractalDefines(const std::string& fractalName);

		template<typename T>
		void Set(ShaderDefineType type, const T& value)
		{
			if (typeid(T) == typeid(glm::vec3))
				m_Vec3Defines[type] = value;
			else if (typeid(T) == typeid(int))
				m_IntDefines[type] = value;
			else if (typeid(T) == typeid(float))
				m_FloatDefines[type] = value;
			else if (typeid(T) == typeid(bool))
				m_BoolDefines[type] = value;
		}

		template<typename T>
		T& Get(ShaderDefineType type)
		{
			if (typeid(T) == typeid(glm::vec3))
				return m_Vec3Defines[type];
			else if (typeid(T) == typeid(int))
				return m_IntDefines[type];
			else if (typeid(T) == typeid(float))
				return m_FloatDefines[type];
			else (typeid(T) == typeid(bool))
				return m_BoolDefines[type];
		}

		std::string Compile();

		const std::string DefineToString(ShaderDefineType type) { return m_ToStringDict[type]; }

		std::unordered_map<ShaderDefineType, bool>& BoolDefines() { return m_BoolDefines; }
		std::unordered_map<ShaderDefineType, int>& IntDefines() { return m_IntDefines; }
		std::unordered_map<ShaderDefineType, float>& FloatDefines() { return m_FloatDefines; }
		std::unordered_map<ShaderDefineType, glm::vec3>& Vec3Defines() { return m_Vec3Defines; }

	private:
		void Initialize();

	private:
		std::string m_Name;
		std::unordered_map<ShaderDefineType, std::string> m_ToStringDict;
		std::unordered_map<ShaderDefineType, glm::vec3> m_Vec3Defines;
		std::unordered_map<ShaderDefineType, int> m_IntDefines;
		std::unordered_map<ShaderDefineType, float> m_FloatDefines;
		std::unordered_map<ShaderDefineType, bool> m_BoolDefines;
	};
}