#pragma once

#include "Event/Event.h"

struct GLFWwindow;

namespace RM
{
	class Window
	{
	public:

		using EventCallbackFunction = std::function<void(Event&)>;

		Window(const std::string& name = "Raymarcher", uint32_t width = 1920, uint32_t height = 1080);
		~Window();

		void Update();
		void SetEventCallbackFunction(const EventCallbackFunction& callback) { m_WindowData.Callback = callback; }
		void ToggleMaximize(bool maximize);

		uint32_t GetWidth() const { return m_WindowData.Width; }
		uint32_t GetHeight() const { return m_WindowData.Height; }
		float GetAspectRatio() const { return (float)m_WindowData.Width / (float)m_WindowData.Height; }

		void SetVSync(bool enable);
		bool IsVSync() const { return m_WindowData.VSync; }

		GLFWwindow* GetWindowHandle() const { return m_WindowHandle; }

	private:
		void Initialize();
		void Shutdown();

	private:
		GLFWwindow* m_WindowHandle;

		struct WindowData
		{
			std::string Name;
			uint32_t Width, Height;
			EventCallbackFunction Callback;
			bool VSync;


			WindowData(const std::string& name = "Ohm Engine", uint32_t width = 1920, uint32_t height = 1080, bool vSync = true)
				:Name(name), Width(width), Height(height), VSync(vSync)
			{
			}
		};

		WindowData m_WindowData;
	};
}