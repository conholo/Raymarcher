#include "rmpch.h"
#include "Core/Application.h"
#include "Core/Time.h"
#include "Renderer/RenderCommand.h"
#include "Renderer/Renderer.h"
#include "Core/Random.h"

namespace RM
{
	Application* Application::s_Instance = nullptr;

	Application::Application(const Ref<Layer>& layer)
		:m_ApplicationName(layer->GetName()), m_ActiveLayer(layer)
	{
		s_Instance = this;
		m_Window = CreateScope<Window>(layer->GetName());
		m_Window->SetEventCallbackFunction(BIND_FN(Application::OnEvent));

		m_ImGuiLayer = CreateRef<ImGuiLayer>();

		m_ImGuiLayer->OnAttach();
		RenderCommand::Initialize();
		RenderCommand::SetViewport(m_Window->GetWidth(), m_Window->GetHeight());
		Renderer::Initialize();
		Random::Initialize();

		m_Window->ToggleMaximize(true);

		m_ActiveLayer->OnAttach();
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_IsRunning)
		{
			Time::Tick();

			m_ActiveLayer->OnUpdate(Time::DeltaTime());

			{
				m_ImGuiLayer->Begin();
				m_ActiveLayer->OnImGuiRender();
				m_ImGuiLayer->End();
			}

			m_Window->Update();
		}
	}

	void Application::Shutdown()
	{
		m_ActiveLayer->OnDetach();
		m_ImGuiLayer->OnDetach();
		m_IsRunning = false;
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);

		m_ImGuiLayer->OnEvent(event);
		dispatcher.Dispatch<WindowResizedEvent>(BIND_FN(Application::OnResize));
		dispatcher.Dispatch<WindowClosedEvent>(BIND_FN(Application::OnWindowClosed));
		m_ActiveLayer->OnEvent(event);
	}

	bool Application::OnResize(WindowResizedEvent& resizeEvent)
	{
		RenderCommand::SetViewport(resizeEvent.GetWidth(), resizeEvent.GetHeight());
		return false;
	}

	bool Application::OnWindowClosed(WindowClosedEvent& closedEvent)
	{
		m_IsRunning = false;
		return true;
	}
}