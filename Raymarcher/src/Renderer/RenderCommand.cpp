#include "rmpch.h"
#include "Renderer/RenderCommand.h"

#include <glad/glad.h>


namespace RM
{
	void OpenGLMessageCallback(
		unsigned source,
		unsigned type,
		unsigned id,
		unsigned severity,
		int length,
		const char* message,
		const void* userParam
	)
	{
		std::cout << message << std::endl;
	}

	void RenderCommand::Initialize()
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLMessageCallback, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
		glEnable(GL_CULL_FACE);
	}

	void RenderCommand::SetDrawMode(DrawMode drawMode)
	{
		glPolygonMode(GL_FRONT_AND_BACK, drawMode == DrawMode::Fill ? GL_FILL : GL_LINE);
	}

	void RenderCommand::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void RenderCommand::SetViewport(uint32_t width, uint32_t height)
	{
		glViewport(0, 0, width, height);
	}

	void RenderCommand::ClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void RenderCommand::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount)
	{
		uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetIndexCount();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}
}
