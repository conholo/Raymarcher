#pragma once

#include "Event/WindowEvent.h"
#include "Core/Window.h"
#include "Core/Layer.h"
#include "ImGui/ImGuiLayer.h"

namespace RM
{
	class Application
	{
	public:
		Application(const Ref<Layer>& layer);
		~Application();

		void Run();
		void Shutdown();

		static Application& GetApplication() { return *s_Instance; }
		Window& GetWindow() const { return *m_Window; }
		const std::string& GetName() const { return m_ApplicationName; }

		void OnEvent(Event& event);

	private:
		bool OnResize(WindowResizedEvent& resizeEvent);
		bool OnWindowClosed(WindowClosedEvent& closedEvent);

	private:
		static Application* s_Instance;

	private:
		Ref<ImGuiLayer> m_ImGuiLayer;
		Ref<Layer> m_ActiveLayer;
		Scope<Window> m_Window;

		std::string m_ApplicationName;
		bool m_IsRunning = true;
	};
}