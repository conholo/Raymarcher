#pragma once

#include "RM.h"

class TestLayer : public RM::Layer
{
public:
	TestLayer(const std::string& name);
	~TestLayer();

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(float deltaTime) override;
	void OnEvent(RM::Event& event) override;
	void OnImGuiRender() override;

private:
	float m_Counter;
	RM::Camera m_Camera;
};