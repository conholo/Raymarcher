#pragma once

#include "Core/Memory.h"

#include <glm/glm.hpp>

typedef unsigned int GLenum;
typedef int GLint;

namespace RM
{
	class Shader
	{
	public:
		Shader(const std::string& filePath);
		~Shader();

		void Bind() const;
		void Unbind() const;

		uint32_t GetID() const { return m_ID; }
		std::string GetName() const { return m_Name; }

		GLint UploadUniformFloat(const std::string& name, float value);
		GLint UploadUniformFloat2(const std::string& name, const glm::vec2& value);
		GLint UploadUniformFloat3(const std::string& name, const glm::vec3& value);
		GLint UploadUniformFloat4(const std::string& name, const glm::vec4& value);
		GLint UploadUniformInt(const std::string& name, int value);
		GLint UploadUniformIntArray(const std::string& name, uint32_t count, int* basePtr);
		GLint UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		GLint UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
		GLint UploadUniformMat4Array(const std::string& name, uint32_t count, float* start);

		void EnableShaderImageAccessBarrierBit();
		void EnableTextureFetchBarrierBit();
		bool IsCompute() const { return m_IsCompute; }

		void DispatchCompute(uint32_t groupX, uint32_t groupY, uint32_t groupZ);

	private:
		bool m_IsCompute = false;
		std::string ReadFile(const std::string& filePath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

	private:
		std::string m_Name;
		uint32_t m_ID;
	};


	class ShaderLibrary
	{
	public:
		static void Add(const Ref<Shader>& shader);
		static void Load(const std::string& shaderName);

		static const Ref<Shader>& Get(const std::string& name);

	private:
		static std::unordered_map<std::string, Ref<Shader>> s_ShaderLibrary;
	};
}

