#include "rmpch.h"
#include "Fractal/FractalDefines.h"

#include <glm/gtx/string_cast.hpp>

namespace RM
{
	FractalDefines::FractalDefines(const std::string& fractalName)
		:m_Name(fractalName)
	{
		Initialize();
	}

	void FractalDefines::Initialize()
	{
		m_Vec3Defines[ShaderDefineType::AO_COLOR_DELTA] = glm::vec3(0.8, 0.8, 0.8);
		m_Vec3Defines[ShaderDefineType::BG_COLOR] = glm::vec3(0.7, 0.7, 0.9);
		m_Vec3Defines[ShaderDefineType::GLOW_COLOR_DELTA] = glm::vec3(-0.2f, 0.5f, -0.2f);
		m_Vec3Defines[ShaderDefineType::LIGHT_POSITION] = glm::vec3(100.0f, 200.0f, 10.0f);
		m_Vec3Defines[ShaderDefineType::LIGHT_COLOR] = glm::vec3(1.0f, 1.0f, 1.0f);

		m_FloatDefines[ShaderDefineType::AO_STRENGTH] = 0.01f;
		m_FloatDefines[ShaderDefineType::DOF_STRENGTH] = 1.0f;
		m_FloatDefines[ShaderDefineType::DOF_DISTANCE] = 50.0f;
		m_FloatDefines[ShaderDefineType::EXPOSURE] = 1.0f;
		m_FloatDefines[ShaderDefineType::FOV] = 45.0f;
		m_FloatDefines[ShaderDefineType::GAMMA_CORRECTION] = 2.0f;
		m_FloatDefines[ShaderDefineType::GLOW_SHARPNESS] = 100.0f;
		m_FloatDefines[ShaderDefineType::LOD_MULTIPLIER] = 50.0f;
		m_FloatDefines[ShaderDefineType::MAX_DISTANCE] = 50.0f;
		m_FloatDefines[ShaderDefineType::MAX_MARCHES] = 1000.0f;
		m_FloatDefines[ShaderDefineType::MIN_DISTANCE] = 0.00001f;
		m_FloatDefines[ShaderDefineType::SHADOW_DARKNESS] = 0.8f;
		m_FloatDefines[ShaderDefineType::SHADOW_SHARPNESS] = 8.0f;
		m_FloatDefines[ShaderDefineType::SPECULAR_HIGHTLIGHT] = 4.0f;
		m_FloatDefines[ShaderDefineType::SUN_SIZE] = 0.005f;
		m_FloatDefines[ShaderDefineType::SUN_SHARPNESS] = 2.0f;

		m_BoolDefines[ShaderDefineType::FOG_ENABLED] = true;
		m_BoolDefines[ShaderDefineType::GLOW_ENABLED] = true;
		m_BoolDefines[ShaderDefineType::SHADOWS_ENABLED] = true;
		m_BoolDefines[ShaderDefineType::SUN_ENABLED] = true;

		m_ToStringDict[ShaderDefineType::AO_COLOR_DELTA] = "AO_COLOR_DELTA";
		m_ToStringDict[ShaderDefineType::AO_STRENGTH] = "AO_STRENGTH";
		m_ToStringDict[ShaderDefineType::BG_COLOR] = "BG_COLOR";
		m_ToStringDict[ShaderDefineType::DOF_DISTANCE] = "DOF_DISTANCE";
		m_ToStringDict[ShaderDefineType::DOF_STRENGTH] = "DOF_STRENGTH";
		m_ToStringDict[ShaderDefineType::EXPOSURE] = "EXPOSURE";
		m_ToStringDict[ShaderDefineType::FOG_ENABLED] = "FOG_ENABLED";
		m_ToStringDict[ShaderDefineType::FOV] = "FOV";
		m_ToStringDict[ShaderDefineType::GAMMA_CORRECTION] = "GAMMA_CORRECTION";
		m_ToStringDict[ShaderDefineType::GLOW_COLOR_DELTA] = "GLOW_COLOR_DELTA";
		m_ToStringDict[ShaderDefineType::GLOW_ENABLED] = "GLOW_ENABLED";
		m_ToStringDict[ShaderDefineType::GLOW_SHARPNESS] = "GLOW_SHARPNESS";
		m_ToStringDict[ShaderDefineType::LIGHT_COLOR] = "LIGHT_COLOR";
		m_ToStringDict[ShaderDefineType::LIGHT_POSITION] = "LIGHT_POSITION";
		m_ToStringDict[ShaderDefineType::LOD_MULTIPLIER] = "LOD_MULTIPLIER";
		m_ToStringDict[ShaderDefineType::MAX_DISTANCE] = "MAX_DISTANCE";
		m_ToStringDict[ShaderDefineType::MAX_MARCHES] = "MAX_MARCHES";
		m_ToStringDict[ShaderDefineType::MIN_DISTANCE] = "MIN_DISTANCE";
		m_ToStringDict[ShaderDefineType::SHADOW_DARKNESS] = "SHADOW_DARKNESS";
		m_ToStringDict[ShaderDefineType::SHADOW_SHARPNESS] = "SHADOW_SHARPNESS";
		m_ToStringDict[ShaderDefineType::SHADOWS_ENABLED] = "SHADOWS_ENABLED";
		m_ToStringDict[ShaderDefineType::SPECULAR_HIGHTLIGHT] = "SPECULAR_HIGHTLIGHT";
		m_ToStringDict[ShaderDefineType::SUN_ENABLED] = "SUN_ENABLED";
		m_ToStringDict[ShaderDefineType::SUN_SIZE] = "SUN_SIZE";
		m_ToStringDict[ShaderDefineType::SUN_SHARPNESS] = "SUN_SHARPNESS";
	}

	std::string FractalDefines::Compile()
	{
		std::stringstream ss;

		for (auto boolEntry : m_BoolDefines)
		{
			int value = boolEntry.second ? 1 : 0;
			ss << "#define " << m_ToStringDict[boolEntry.first] << " " << std::to_string(value) << "\n";
		}

		for (auto intEntry : m_IntDefines)
			ss << "#define " << m_ToStringDict[intEntry.first] << " " << std::to_string(intEntry.second) << "\n";

		for (auto floatEntry : m_FloatDefines)
			ss << "#define " << m_ToStringDict[floatEntry.first] << " " << std::to_string(floatEntry.second) << "\n";

		for (auto vec3Entry : m_Vec3Defines)
			ss << "#define " << m_ToStringDict[vec3Entry.first] << " " << glm::to_string(vec3Entry.second) << "\n";
		
		ss << "#define DE DE_" << m_Name << "\n";
		ss << "#define CE CE_" << m_Name;

		return ss.str();
	}
}