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

static RM::Ref<RM::Fractal> Mausoleum()
{
	RM::Ref<RM::Fractal> fractal = RM::CreateRef<RM::Fractal>("Cemetery");
	fractal->SetIterations(5);
	fractal->AddTransformation(RM::CreateRef<RM::ColorModZero>());
	fractal->SetBegin(1);
	fractal->AddTransformation(RM::CreateRef<RM::FoldBox>(glm::vec3(0.34f)));
	fractal->AddTransformation(RM::CreateRef<RM::FoldMenger>());
	fractal->AddTransformation(RM::CreateRef<RM::FoldScaleTranslate>(3.28f, glm::vec3(-5.27, -0.34, 0.0)));
	fractal->AddTransformation(RM::CreateRef<RM::FoldRotateX>(90.0f));
	fractal->AddTransformation(RM::CreateRef<RM::ColorModMax>(glm::vec3(0.42, 0.38, 0.19)));
	fractal->SetEnd(5);
	fractal->AddTransformation(RM::CreateRef<RM::Box>(RM::ColorType::ColorMod, glm::vec3(2.0f)));

	RM::CompiledFractalSrc src = fractal->CompileProcedural();
	RM::ShaderLibrary::Load("TestShaderFrag", src.DefineSrc, src.ProceduralSrc);

	return fractal;
}

static RM::Ref<RM::Fractal> ButterweedHills()
{
	RM::Ref<RM::Fractal> fractal = RM::CreateRef<RM::Fractal>("TheHills");
	fractal->SetIterations(25);
	fractal->AddTransformation(RM::CreateRef<RM::ColorModZero>());
	uint32_t begin = 1;
	fractal->SetBegin(1);
	fractal->AddTransformation(RM::CreateRef<RM::FoldAbs>());
	fractal->AddTransformation(RM::CreateRef<RM::FoldScaleTranslate>(1.5f, glm::vec3(-1.0f, -0.55f, -0.2f)));
	fractal->AddTransformation(RM::CreateRef<RM::ColorModSum>(glm::vec3(0.5f, 0.3f, 0.0)));
	fractal->AddTransformation(RM::CreateRef<RM::FoldRotateX>(206.0f));
	fractal->AddTransformation(RM::CreateRef<RM::FoldRotateY>(116.0f));
	fractal->SetEnd(5);
	fractal->AddTransformation(RM::CreateRef<RM::Sphere>(RM::ColorType::ColorMod));

	RM::CompiledFractalSrc src = fractal->CompileProcedural();
	RM::ShaderLibrary::Load("TestShaderFrag", src.DefineSrc, src.ProceduralSrc);

	return fractal;
}

static RM::Ref<RM::Fractal> TreeWorld()
{
	RM::Ref<RM::Fractal> fractal = RM::CreateRef<RM::Fractal>("TheLorax");
	fractal->SetIterations(30);
	fractal->AddTransformation(RM::CreateRef<RM::ColorModInfinity>());
	fractal->SetBegin(1);
	fractal->AddTransformation(RM::CreateRef<RM::FoldRotateY>(25.0f));
	fractal->AddTransformation(RM::CreateRef<RM::FoldAbs>());
	fractal->AddTransformation(RM::CreateRef<RM::FoldMenger>());
	fractal->AddTransformation(RM::CreateRef<RM::ColorModMinAbs>(glm::vec3(0.25f, 2.28f, 7.6f)));
	fractal->AddTransformation(RM::CreateRef<RM::FoldScaleTranslate>(1.3f, glm::vec3(-2.0f, -4.8f, 0.0f)));
	fractal->AddTransformation(RM::CreateRef<RM::FoldPlane>(RM::FoldPlane::FoldDirection::Back, 0.0f));
	fractal->SetEnd(6);
	fractal->AddTransformation(RM::CreateRef<RM::Box>(RM::ColorType::ColorMod, glm::vec3(10.0f)));

	RM::CompiledFractalSrc src = fractal->CompileProcedural();
	RM::ShaderLibrary::Load("TestShaderFrag", src.DefineSrc, src.ProceduralSrc);

	return fractal;
}

static RM::Ref<RM::Fractal> TheHive()
{
	RM::Ref<RM::Fractal> fractal = RM::CreateRef<RM::Fractal>("TheHive");
	fractal->SetIterations(15);
	fractal->AddTransformation(RM::CreateRef<RM::ColorModInfinity>());
	fractal->SetBegin(1);
	fractal->AddTransformation(RM::CreateRef<RM::FoldRotateY>(25.0f));
	fractal->AddTransformation(RM::CreateRef<RM::FoldAbs>());
	fractal->AddTransformation(RM::CreateRef<RM::FoldMenger>());
	fractal->AddTransformation(RM::CreateRef<RM::ColorModMinAbs>(glm::vec3(0.25f, 2.28f, 7.6f)));
	fractal->AddTransformation(RM::CreateRef<RM::FoldScaleTranslate>(1.5, glm::vec3(-2.5f, -5.5f, 0.5f)));
	fractal->AddTransformation(RM::CreateRef<RM::FoldPlane>(RM::FoldPlane::FoldDirection::Back, 0.0f));
	fractal->SetEnd(6);
	fractal->AddTransformation(RM::CreateRef<RM::Box>(RM::ColorType::ColorMod, glm::vec3(10.0f)));

	RM::CompiledFractalSrc src = fractal->CompileProcedural();
	RM::ShaderLibrary::Load("TestShaderFrag", src.DefineSrc, src.ProceduralSrc);

	return fractal;
}

static RM::Ref<RM::Fractal> GalacticPetal()
{
	RM::Ref<RM::Fractal> fractal = RM::CreateRef<RM::Fractal>("GalacticPetal");
	fractal->SetIterations(15);

	fractal->AddTransformation(RM::CreateRef<RM::ColorModInfinity>());
	fractal->SetBegin(1);
	fractal->AddTransformation(RM::CreateRef<RM::FoldRotateY>(25.0f));
	fractal->AddTransformation(RM::CreateRef<RM::FoldSierpinski>());
	fractal->AddTransformation(RM::CreateRef<RM::ColorModMinAbs>(glm::vec3(0.25f, 0.01f, 1.0f)));
	fractal->AddTransformation(RM::CreateRef<RM::FoldScaleTranslate>(1.4f, glm::vec3(-2.5f, -10.5f, -5.25f)));
	fractal->AddTransformation(RM::CreateRef<RM::FoldPlane>(RM::FoldPlane::FoldDirection::Up, 0.0f));
	fractal->AddTransformation(RM::CreateRef<RM::FoldRotateZ>(25.0f));
	fractal->SetEnd(6);
	fractal->AddTransformation(RM::CreateRef<RM::Box>(RM::ColorType::ColorMod, glm::vec3(10.0f)));

	RM::CompiledFractalSrc src = fractal->CompileProcedural();
	RM::ShaderLibrary::Load("TestShaderFrag", src.DefineSrc, src.ProceduralSrc);

	return fractal;
}

static RM::Ref<RM::Fractal> Test()
{
	RM::Ref<RM::Fractal> fractal = RM::CreateRef<RM::Fractal>("TestFractal");
	fractal->SetIterations(15);

	fractal->AddTransformation(RM::CreateRef<RM::ColorModZero>());
	fractal->SetBegin(1);
	fractal->AddTransformation(RM::CreateRef<RM::FoldRotateY>(25.0f));
	fractal->AddTransformation(RM::CreateRef<RM::ColorModMax>(glm::vec3(0.25f, 0.01f, 1.0f)));
	fractal->AddTransformation(RM::CreateRef<RM::FoldScaleTranslate>(1.9f, glm::vec3(-2.5f, -1.0f, -0.1f)));
	fractal->AddTransformation(RM::CreateRef<RM::FoldPlane>(RM::FoldPlane::FoldDirection::Forward, 0.1f));
	fractal->AddTransformation(RM::CreateRef<RM::FoldRotateZ>(20.0f));
	fractal->AddTransformation(RM::CreateRef<RM::ColorModMin>(glm::vec3(2.0f, 0.01f, 0.1f)));
	fractal->AddTransformation(RM::CreateRef<RM::FoldMenger>());
	fractal->AddTransformation(RM::CreateRef<RM::FoldBox>());
	fractal->SetEnd(8);
	fractal->AddTransformation(RM::CreateRef<RM::FoldScaleTranslate>(1.1f, glm::vec3(0.0f, -1.0f, -0.1f)));
	fractal->AddTransformation(RM::CreateRef<RM::Box>(RM::ColorType::ColorMod, glm::vec3(1.0f)));

	RM::CompiledFractalSrc src = fractal->CompileProcedural();
	RM::ShaderLibrary::Load("TestShaderFrag", src.DefineSrc, src.ProceduralSrc);

	return fractal;
}

static RM::Ref<RM::Fractal> SierpinskiTetrahedron()
{

	RM::Ref<RM::Fractal> fractal = RM::CreateRef<RM::Fractal>("SierpinskiTetrahedron");
	fractal->SetIterations(9);
	fractal->AddTransformation(RM::CreateRef<RM::ColorModZero>());
	fractal->SetBegin(1);
	fractal->AddTransformation(RM::CreateRef<RM::FoldSierpinski>());
	fractal->AddTransformation(RM::CreateRef<RM::FoldScaleTranslate>(2.0f, glm::vec3(-1.0f)));
	fractal->AddTransformation(RM::CreateRef<RM::ColorModSumAbs>(glm::vec3(0.2f, 0.5f, 0.1f)));
	fractal->AddTransformation(RM::CreateRef<RM::ColorModMin>(glm::vec3(0.8f, 0.1f, 0.1f), glm::vec3(-0.8f, 1.0f, 0.0f)));
	fractal->SetEnd(4);
	fractal->AddTransformation(RM::CreateRef<RM::Tetrahedron>(RM::ColorType::ColorMod));

	RM::CompiledFractalSrc src = fractal->CompileProcedural();
	RM::ShaderLibrary::Load("TestShaderFrag", src.DefineSrc, src.ProceduralSrc);

	return fractal;
}

static RM::Ref<RM::Fractal> AlienCube()
{
	const uint32_t iterations = 9;

	RM::Ref<RM::Fractal> fractal = RM::CreateRef<RM::Fractal>("AlienCube");
	fractal->SetIterations(9);

	fractal->AddTransformation(RM::CreateRef<RM::ColorModZero>());
	fractal->SetBegin(1);

	fractal->AddTransformation(RM::CreateRef<RM::FoldBox>(glm::vec3(0.1f, 0.3f, 0.1f)));
	fractal->AddTransformation(RM::CreateRef<RM::FoldMenger>());
	fractal->AddTransformation(RM::CreateRef<RM::FoldScaleTranslate>(3.28f, glm::vec3(0.5f, 0.3f, 0.5f)));

	fractal->AddTransformation(RM::CreateRef<RM::FoldBox>());
	fractal->AddTransformation(RM::CreateRef<RM::FoldRotateX>(90.0f));
	fractal->AddTransformation(RM::CreateRef<RM::ColorModMax>(glm::vec3(0.01f, 0.4f, 0.8f)));
	fractal->SetEnd(6);
	fractal->AddTransformation(RM::CreateRef<RM::Sphere>(RM::ColorType::ColorMod));

	RM::CompiledFractalSrc src = fractal->CompileProcedural();
	RM::ShaderLibrary::Load("TestShaderFrag", src.DefineSrc, src.ProceduralSrc);

	return fractal;
}

void TestLayer::OnAttach()
{
	auto fractal = GalacticPetal();
	RM::FractalSerializer::Serialize(fractal);
	m_Camera.SetPanSpeed(0.1f);
	RM::UI::FractalManagerUI::LoadFromDisk();
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
	ImGui::Begin("Stats");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();

	ImGui::Begin("Fractals");
	RM::UI::FractalManagerUI::DrawFractalUI();
	ImGui::End();
}
