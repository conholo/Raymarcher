#include "rmpch.h"
#include "TestLayer.h"
#define PI 3.14159265359

#include <imgui/imgui.h>

TestLayer::TestLayer(const std::string& name)
	:RM::Layer(name)
{

}

TestLayer::~TestLayer()
{

}

static RM::Fractal Mausoleum()
{
	const uint32_t iterations = 8;

	RM::Fractal fractal("TestFractal");
	fractal.AddTransformation(RM::CreateRef<RM::ColorModZero>());
	for (uint32_t i = 0; i < iterations; i++)
	{
		fractal.AddTransformation(RM::CreateRef<RM::FoldBox>(glm::vec3(0.34f)));
		fractal.AddTransformation(RM::CreateRef<RM::FoldMenger>());
		fractal.AddTransformation(RM::CreateRef<RM::FoldRotateY>(90.0f));
		fractal.AddTransformation(RM::CreateRef<RM::ColorModMinAbs>());
		fractal.AddTransformation(RM::CreateRef<RM::FoldScaleTranslate>(2.0f, glm::vec3(-6.27f, -1.5f, 0.0f)));
		fractal.AddTransformation(RM::CreateRef<RM::FoldRotateX>(20.0f));
		fractal.AddTransformation(RM::CreateRef<RM::ColorModMax>(glm::vec3(0.42, 0.38, 0.19)));
	}
	fractal.AddTransformation(RM::CreateRef<RM::Box>(RM::ColorType::ColorMod, glm::vec3(3.0f)));
	
	return fractal;
}

static RM::Fractal ButterweedHills()
{
	const uint32_t iterations = 30;

	RM::Fractal fractal("TestFractal");
	fractal.AddTransformation(RM::CreateRef<RM::ColorModZero>());
	for (uint32_t i = 0; i < iterations; i++)
	{
		fractal.AddTransformation(RM::CreateRef<RM::FoldAbs>());
		fractal.AddTransformation(RM::CreateRef<RM::FoldScaleTranslate>(1.5f, glm::vec3(-1.0f, -0.55f, -0.2f)));
		fractal.AddTransformation(RM::CreateRef<RM::ColorModSum>(glm::vec3(0.5f, 0.3f, 0.0)));
		fractal.AddTransformation(RM::CreateRef<RM::FoldRotateX>(206.0f));
		fractal.AddTransformation(RM::CreateRef<RM::FoldRotateY>(116.0f));

	}
	fractal.AddTransformation(RM::CreateRef<RM::Sphere>(RM::ColorType::ColorMod));

	return fractal;
}

static RM::Fractal TreeWorld()
{
	const uint32_t iterations = 30;

	RM::Fractal fractal("TestFractal");
	fractal.AddTransformation(RM::CreateRef<RM::ColorModInfinity>());
	for (uint32_t i = 0; i < iterations; i++)
	{
		fractal.AddTransformation(RM::CreateRef<RM::FoldRotateY>(25.0f));
		fractal.AddTransformation(RM::CreateRef<RM::FoldAbs>());
		fractal.AddTransformation(RM::CreateRef<RM::FoldMenger>());
		fractal.AddTransformation(RM::CreateRef<RM::ColorModMinAbs>(glm::vec3(0.25f, 2.28f, 7.6f)));
		fractal.AddTransformation(RM::CreateRef<RM::FoldScaleTranslate>(1.3f, glm::vec3(-2.0f, -4.8f, 0.0f)));
		fractal.AddTransformation(RM::CreateRef<RM::FoldPlane>(RM::FoldPlane::FoldDirection::Left, 0.0f));
	}
	fractal.AddTransformation(RM::CreateRef<RM::Box>(RM::ColorType::ColorMod, glm::vec3(10.0f)));

	return fractal;
}

static RM::Fractal TheHive()
{
	const uint32_t iterations = 15;

	RM::Fractal fractal("TestFractal");
	fractal.AddTransformation(RM::CreateRef<RM::ColorModInfinity>());
	for (uint32_t i = 0; i < iterations; i++)
	{
		fractal.AddTransformation(RM::CreateRef<RM::FoldRotateY>(25.0f));
		fractal.AddTransformation(RM::CreateRef<RM::FoldAbs>());
		fractal.AddTransformation(RM::CreateRef<RM::FoldMenger>());
		fractal.AddTransformation(RM::CreateRef<RM::ColorModMinAbs>(glm::vec3(0.25f, 2.28f, 7.6f)));
		fractal.AddTransformation(RM::CreateRef<RM::FoldScaleTranslate>(1.5, glm::vec3(-2.5f, -5.5f, 0.5f)));
		fractal.AddTransformation(RM::CreateRef<RM::FoldPlane>(RM::FoldPlane::FoldDirection::Back, 0.0f));
	}
	fractal.AddTransformation(RM::CreateRef<RM::Box>(RM::ColorType::ColorMod, glm::vec3(10.0f)));

	return fractal;
}

static RM::Fractal GalacticPetal()
{
	const uint32_t iterations = 15;

	RM::Fractal fractal("TestFractal");
	fractal.AddTransformation(RM::CreateRef<RM::ColorModInfinity>());
	for (uint32_t i = 0; i < iterations; i++)
	{
		fractal.AddTransformation(RM::CreateRef<RM::FoldRotateY>(25.0f));
		fractal.AddTransformation(RM::CreateRef<RM::FoldSierpinski>());
		fractal.AddTransformation(RM::CreateRef<RM::ColorModMinAbs>(glm::vec3(0.25f, 0.01f, 1.0f)));
		fractal.AddTransformation(RM::CreateRef<RM::FoldScaleTranslate>(1.4f, glm::vec3(-2.5f, -10.5f, -5.25f)));
		fractal.AddTransformation(RM::CreateRef<RM::FoldPlane>(RM::FoldPlane::FoldDirection::Up, 0.0f));
		fractal.AddTransformation(RM::CreateRef<RM::FoldRotateZ>(25.0f));
	}
	fractal.AddTransformation(RM::CreateRef<RM::Box>(RM::ColorType::ColorMod, glm::vec3(10.0f)));

	return fractal;
}

static RM::Fractal Test()
{
	const uint32_t iterations = 15;

	RM::Fractal fractal("TestFractal");
	fractal.AddTransformation(RM::CreateRef<RM::ColorModZero>());
	for (uint32_t i = 0; i < iterations; i++)
	{
		fractal.AddTransformation(RM::CreateRef<RM::FoldRotateY>(25.0f));
		fractal.AddTransformation(RM::CreateRef<RM::ColorModMax>(glm::vec3(0.25f, 0.01f, 1.0f)));
		fractal.AddTransformation(RM::CreateRef<RM::FoldScaleTranslate>(1.9f, glm::vec3(-2.5f, -1.0f, -0.1f)));
		fractal.AddTransformation(RM::CreateRef<RM::FoldPlane>(RM::FoldPlane::FoldDirection::Forward, 0.1f));
		fractal.AddTransformation(RM::CreateRef<RM::FoldRotateZ>(20.0f));
		fractal.AddTransformation(RM::CreateRef<RM::ColorModMin>(glm::vec3(2.0f, 0.01f, 0.1f)));
		fractal.AddTransformation(RM::CreateRef<RM::FoldMenger>());
		fractal.AddTransformation(RM::CreateRef<RM::FoldBox>());
	}
	fractal.AddTransformation(RM::CreateRef<RM::FoldScaleTranslate>(1.1f, glm::vec3(0.0f, -1.0f, -0.1f)));
	fractal.AddTransformation(RM::CreateRef<RM::Box>(RM::ColorType::ColorMod, glm::vec3(1.0f)));

	return fractal;
}

static RM::Fractal SierpinskiTetrahedron()
{
	const uint32_t iterations = 9;

	RM::Fractal fractal("TestFractal");
	fractal.AddTransformation(RM::CreateRef<RM::ColorModZero>());
	for (uint32_t i = 0; i < iterations; i++)
	{
		fractal.AddTransformation(RM::CreateRef<RM::FoldSierpinski>());
		fractal.AddTransformation(RM::CreateRef<RM::FoldScaleTranslate>(2.0f, glm::vec3(-1.0f)));
		fractal.AddTransformation(RM::CreateRef<RM::ColorModSumAbs>(glm::vec3(0.2f, 0.5f, 0.1f)));
		fractal.AddTransformation(RM::CreateRef<RM::ColorModMin>(glm::vec3(0.8f, 0.1f, 0.1f), glm::vec3(-0.8f, 1.0f, 0.0f)));
	}
	fractal.AddTransformation(RM::CreateRef<RM::Tetrahedron>(RM::ColorType::ColorMod));

	return fractal;
}

static RM::Fractal AlienCube()
{
	const uint32_t iterations = 9;

	RM::Fractal fractal("TestFractal");
	fractal.AddTransformation(RM::CreateRef<RM::ColorModZero>());
	for (uint32_t i = 0; i < iterations; i++)
	{
		fractal.AddTransformation(RM::CreateRef<RM::FoldBox>(glm::vec3(0.1f, 0.3f, 0.1f)));
		fractal.AddTransformation(RM::CreateRef<RM::FoldMenger>());
		fractal.AddTransformation(RM::CreateRef<RM::FoldScaleTranslate>(3.28f, glm::vec3(0.5f, 0.3f, 0.5f)));

		fractal.AddTransformation(RM::CreateRef<RM::FoldBox>());
		fractal.AddTransformation(RM::CreateRef<RM::FoldRotateX>(90.0f));
		fractal.AddTransformation(RM::CreateRef<RM::ColorModMax>(glm::vec3(0.01f, 0.4f, 0.8f)));
	}
	fractal.AddTransformation(RM::CreateRef<RM::Sphere>(RM::ColorType::ColorMod));

	return fractal;
}

void TestLayer::OnAttach()
{
	m_Camera.SetPanSpeed(0.1f);
	RM::Fractal fractal = ButterweedHills();
	//std::string injection = fractal.Compile();
	//RM::ShaderLibrary::Load("TestShaderFrag", injection);
}

void TestLayer::OnDetach()
{

}

void TestLayer::OnUpdate(float deltaTime)
{
	m_Camera.Update(deltaTime);

	RM::RenderCommand::Clear();
	if (!RM::ShaderLibrary::Has("TestShaderFrag")) return;

	RM::Renderer::DrawFullScreenQuad("TestShaderFrag", m_Camera);
}

void TestLayer::OnEvent(RM::Event& event)
{
	m_Camera.OnEvent(event);
}

void TestLayer::OnImGuiRender()
{
	ImGui::Begin("Fractals");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	RM::UI::FractalManagerUI::DrawFractalUI();

	std::vector<RM::UI::FractalCompileData> readyFractalData = RM::UI::FractalManagerUI::GetReadyFractals();

	for (auto data : readyFractalData)
	{
		if (ImGui::Button("Run Fractal"))
		{
			std::string injection = data.Fractal->CompileProcedural(data.Begin, data.End, data.Iterations);
			if (RM::ShaderLibrary::Has("TestShaderFrag"))
				RM::ShaderLibrary::Recompile("TestShaderFrag", injection);
			else
				RM::ShaderLibrary::Load("TestShaderFrag", injection);
		}
	}
	ImGui::End();
}
