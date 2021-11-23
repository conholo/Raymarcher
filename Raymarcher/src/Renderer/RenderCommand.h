#pragma once

#include <glm/glm.hpp>
#include "Renderer/VertexArray.h"

namespace RM
{
	enum class DrawMode { None = 0, Fill, WireFrame };

	class RenderCommand
	{
	public:
		static void SetViewport(uint32_t width, uint32_t height);
		static void Initialize();

		static void SetDrawMode(DrawMode drawMode);
		static void ClearColor(const glm::vec4& clearColor);
		static void Clear();

		static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0);
	};
}

