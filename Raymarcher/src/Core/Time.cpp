#include "rmpch.h"
#include "Core/Time.h"
#include <GLFW/glfw3.h>

namespace RM
{
	float Time::s_LastFrameTime = 0.0f;
	float Time::s_DeltaTime = 0.0f;
	float Time::s_Elapsed = 0.0f;

	void Time::Tick()
	{
		s_Elapsed = (float)glfwGetTime();
		s_DeltaTime = s_Elapsed - s_LastFrameTime;
		s_LastFrameTime = s_Elapsed;
	}
}