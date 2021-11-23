#pragma once

#include "Renderer/VertexArray.h"

namespace RM
{
	class Renderer
	{
	public:
		static void Initialize();
		static void DrawFullScreenQuad(const std::string& shader);

	private:
		static Ref<VertexArray> s_VAO;
		static Ref<VertexBuffer> s_VBO;
		static Ref<IndexBuffer> s_EBO;
	};
}