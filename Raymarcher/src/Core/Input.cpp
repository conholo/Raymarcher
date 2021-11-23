#include "rmpch.h"
#include "Core/Input.h"
#include "Core/Application.h"

#include <GLFW/glfw3.h>

namespace RM
{
	bool Input::IsKeyPressed(KeyCode key)
	{
		GLFWwindow* window = Application::GetApplication().GetWindow().GetWindowHandle();
		int action = glfwGetKey(window, key);

		return action == GLFW_PRESS || action == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(MouseCode button)
	{
		GLFWwindow* window = Application::GetApplication().GetWindow().GetWindowHandle();
		int action = glfwGetMouseButton(window, button);

		return action == GLFW_PRESS || action == GLFW_REPEAT;
	}

	glm::vec2 Input::GetMousePosition()
	{
		GLFWwindow* window = Application::GetApplication().GetWindow().GetWindowHandle();

		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);

		return { (float)xPos, (float)yPos };
	}

	float Input::GetMouseX()
	{
		return GetMousePosition().x;
	}

	float Input::GetMouseY()
	{
		return GetMousePosition().y;
	}

}