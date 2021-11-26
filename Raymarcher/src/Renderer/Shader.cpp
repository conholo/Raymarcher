#include "rmpch.h"
#include "Renderer/Shader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace RM
{
	Shader::Shader(const std::string& filePath, const std::string& injection)
	{
		size_t shaderLocationOffset = filePath.rfind("\/") + 1;
		size_t extensionOffset = filePath.find_first_of(".", shaderLocationOffset);

		m_Name = filePath.substr(shaderLocationOffset, extensionOffset - shaderLocationOffset);

		std::string fragmentSource = ReadFile(filePath);
		std::string vertexSource = ReadFile(m_VertFilePath);
		
		Inject(fragmentSource, injection);

		std::ofstream outFile("assets/shaders/Debug/DebugFrag.shader");
		outFile << fragmentSource + "\n";
		outFile.close();

		Compile(fragmentSource, vertexSource);
	}

	Shader::~Shader()
	{
		glDeleteShader(m_ID);
	}

	void Shader::Bind() const
	{
		glUseProgram(m_ID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}

	std::string Shader::ReadFile(const std::string& filePath)
	{
		std::string result;
		std::ifstream input(filePath, std::ios::binary | std::ios::in);

		if (input)
		{
			input.seekg(0, std::ios::end);
			size_t size = input.tellg();

			if (size != -1)
			{
				result.resize(size);
				input.seekg(0, std::ios::beg);
				input.read(&result[0], size);
			}
		}

		return result;
	}

	void Shader::Inject(std::string& fragmentSource, const std::string& injection)
	{
		std::string result;
		
		size_t tokenSize = strlen("//DE/CE Begin");
		size_t cursor = fragmentSource.find("//DE/CE Begin");

		fragmentSource.insert(cursor + tokenSize + 1, "\n\n" + injection);
	}

	GLint Shader::CompileShader(ShaderType type, const std::string& source, GLuint program)
	{
		GLuint shader = glCreateShader(type == ShaderType::Fragment ? GL_FRAGMENT_SHADER : GL_VERTEX_SHADER);

		const GLchar* sourceCStr = source.c_str();
		glShaderSource(shader, 1, &sourceCStr, 0);
		glCompileShader(shader);

		GLint isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

			std::string errorHeader = type == ShaderType::Fragment ? "FRAGMENT COMPILATION ERROR" : "VERTEX COMPILATION ERROR";
			std::stringstream ss;
			ss << m_Name << ":\n" << errorHeader << infoLog.data();
			std::cout << ss.str() << "\n";

			glDeleteShader(shader);
			return -1;
		}

		glAttachShader(program, shader);

		return shader;
	}

	void Shader::Compile(const std::string& fragmentSource, const std::string& vertexSource)
	{
		GLuint program = glCreateProgram();

		GLint vertexShader = CompileShader(ShaderType::Vertex, vertexSource, program);
		GLint fragmentShader = CompileShader(ShaderType::Fragment, fragmentSource, program);
		m_ID = program;
		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			std::stringstream ss;
			std::string messageHeader = m_Name + ": LINKING ERROR:\n";
			ss << messageHeader << infoLog.data();
			std::cout << ss.str() << "\n";

			glDeleteProgram(program);
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
			return;
		}

		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	GLint Shader::UploadUniformFloat(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(m_ID, name.c_str());
		glUniform1f(location, value);
		return location;
	}

	GLint Shader::UploadUniformFloat2(const std::string& name, const glm::vec2& value)
	{
		GLint location = glGetUniformLocation(m_ID, name.c_str());
		glUniform2f(location, value.x, value.y);
		return location;
	}

	GLint Shader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
	{
		GLint location = glGetUniformLocation(m_ID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
		return location;
	}

	GLint Shader::UploadUniformFloat4(const std::string& name, const glm::vec4& value)
	{
		GLint location = glGetUniformLocation(m_ID, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
		return location;
	}

	GLint Shader::UploadUniformInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_ID, name.c_str());
		glUniform1i(location, value);
		return location;
	}

	GLint Shader::UploadUniformIntArray(const std::string& name, uint32_t count, int* basePtr)
	{
		GLint location = glGetUniformLocation(m_ID, name.c_str());
		glUniform1iv(location, count, basePtr);
		return location;
	}

	GLint Shader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(m_ID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
		return location;
	}

	GLint Shader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_ID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
		return location;
	}

	GLint Shader::UploadUniformMat4Array(const std::string& name, uint32_t count, float* start)
	{
		GLint location = glGetUniformLocation(m_ID, name.c_str());
		glUniformMatrix4fv(location, count, GL_FALSE, start);
		return location;
	}

	void Shader::EnableShaderImageAccessBarrierBit()
	{
		glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT | GL_TEXTURE_FETCH_BARRIER_BIT);
	}

	void Shader::EnableTextureFetchBarrierBit()
	{
		glMemoryBarrier(GL_TEXTURE_FETCH_BARRIER_BIT);
	}

	void Shader::DispatchCompute(uint32_t groupX, uint32_t groupY, uint32_t groupZ)
	{
		if (!m_IsCompute)
		{
			std::cout << m_Name << " is not of type Compute Shader.  Cannot dispatch." << std::endl;
			return;
		}

		glUseProgram(m_ID);
		glDispatchCompute(groupX, groupY, groupZ);
	}

	std::unordered_map<std::string, Ref<Shader>> ShaderLibrary::s_ShaderLibrary;

	bool ShaderLibrary::Has(const std::string& shaderName)
	{
		return s_ShaderLibrary.find(shaderName) != s_ShaderLibrary.end();
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		if (s_ShaderLibrary.find(shader->GetName()) == s_ShaderLibrary.end())
		{
			s_ShaderLibrary[shader->GetName()] = shader;
		}
		else
		{
			std::cout << "Shader already contained in Shader Library.  Attempted to add (" << shader->GetName() << ") Shader to Library." << "\n";
		}
	}

	void ShaderLibrary::Load(const std::string& shaderName, const std::string& injection)
	{
		const std::string shaderPath = "assets/shaders/" + shaderName + ".shader";
		Ref<Shader> shader = CreateRef<Shader>(shaderPath, injection);
		Add(shader);
	}

	void ShaderLibrary::Recompile(const std::string& shaderName, const std::string& injection)
	{
		if (!Has(shaderName)) return;

		const std::string shaderPath = "assets/shaders/" + shaderName + ".shader";
		Ref<Shader> shader = CreateRef<Shader>(shaderPath, injection);
		s_ShaderLibrary[shader->GetName()] = shader;
	}

	const Ref<Shader>& ShaderLibrary::Get(const std::string& name)
	{
		if (s_ShaderLibrary.find(name) == s_ShaderLibrary.end())
		{
			//std::cout << "No shader with name:( " << name << ") found in Shader Library." << "\n";
			return nullptr;
		}

		return s_ShaderLibrary.at(name);
	}
}

