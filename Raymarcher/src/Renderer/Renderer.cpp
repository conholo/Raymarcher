#include "rmpch.h"
#include "Renderer/Renderer.h"
#include "Renderer/RenderCommand.h"
#include "Renderer/Shader.h"
#include "Core/Application.h"
#include "Core/Input.h"
#include "Core/Time.h"

namespace RM
{
	Ref<VertexArray> Renderer::s_VAO = nullptr;
	Ref<VertexBuffer> Renderer::s_VBO = nullptr;
	Ref<IndexBuffer> Renderer::s_EBO = nullptr;

	void Renderer::Initialize()
	{
		s_VAO = CreateRef<VertexArray>();
		
		float quadVertices[]
		{
			-1.0f, -1.0f, 0.0f,
			 1.0f, -1.0f, 0.0f,
			 1.0f,  1.0f, 0.0f,
			-1.0f,  1.0f, 0.0f
		};

		s_VBO = CreateRef<VertexBuffer>(&quadVertices[0], sizeof(quadVertices));
		BufferLayout layout
		{
			{ "a_Position", ShaderAttributeType::Float3 }
		};
		s_VBO->SetLayout(layout);

		uint32_t quadIndices[] =
		{
			0, 1, 2,
			2, 3, 0
		};
		s_EBO = CreateRef<IndexBuffer>(&quadIndices[0], sizeof(quadIndices) / sizeof(uint32_t));

		s_VAO->SetIndexBuffer(s_EBO);
		s_VAO->EnableVertexAttributes(s_VBO);
	}

	void Renderer::DrawFullScreenQuad(const std::string& shader)
	{
		s_VAO->Bind();
		ShaderLibrary::Get(shader)->Bind();
		glm::vec2 screenResolution = { (float)Application::GetApplication().GetWindow().GetWidth(), (float)Application::GetApplication().GetWindow().GetHeight() };
		glm::vec2 mousePosition = Input::GetMousePosition();
		ShaderLibrary::Get(shader)->UploadUniformFloat("u_ElapsedTime", Time::Elapsed());
		ShaderLibrary::Get(shader)->UploadUniformFloat("u_DeltaTime", Time::DeltaTime());
		ShaderLibrary::Get(shader)->UploadUniformFloat2("u_ScreenResolution", screenResolution);
		ShaderLibrary::Get(shader)->UploadUniformFloat2("u_MousePosition", mousePosition);
		RenderCommand::DrawIndexed(s_VAO);
		s_VAO->Unbind();
	}
}