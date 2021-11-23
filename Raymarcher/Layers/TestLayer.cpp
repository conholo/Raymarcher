#include "rmpch.h"
#include "TestLayer.h"

TestLayer::TestLayer(const std::string& name)
	:RM::Layer(name)
{

}

TestLayer::~TestLayer()
{

}

void TestLayer::OnAttach()
{
	RM::ShaderLibrary::Load("TestShader");
}

void TestLayer::OnDetach()
{

}

void TestLayer::OnUpdate(float deltaTime)
{
	m_Camera.Update(deltaTime);
	RM::Renderer::DrawFullScreenQuad("TestShader");
}

void TestLayer::OnEvent(RM::Event& event)
{
	m_Camera.OnEvent(event);
}

void TestLayer::OnImGuiRender()
{

}
