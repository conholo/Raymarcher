#include "rmpch.h"
#include "UI/FractalManagerUI.h"
#include "Renderer/Shader.h"
#include "Fractal/FractalSerializer.h"

#include <imgui/imgui.h>

namespace RM
{
	namespace UI
	{
		std::vector<Ref<FractalViewerUI>> FractalManagerUI::s_Views;
		std::string FractalManagerUI::s_InputFractalName = "";
		bool FractalManagerUI::s_EditorOpen = false;
		Ref<FractalViewerUI> FractalManagerUI::s_ActiveViewer = nullptr;

		void FractalManagerUI::LoadFromDisk()
		{
			std::string path = "assets/fractals";
			for (const auto& entry : std::filesystem::directory_iterator(path))
			{
				std::string fractalPath = entry.path().generic_string();
				const Ref<Fractal>& fractal = FractalSerializer::Deserialize(fractalPath);
				Ref<FractalViewerUI> viewer = CreateRef<FractalViewerUI>(fractal);
				viewer->SetBegin(fractal->GetBegin());
				viewer->SetEnd(fractal->GetEnd());
				viewer->SetIterationCount(fractal->GetIterations());
				s_Views.push_back(viewer);
			}
		}

		void FractalManagerUI::CreateFractal(const std::string& fractalName)
		{
			s_Views.push_back(CreateRef<FractalViewerUI>(CreateRef<Fractal>(fractalName)));
		}

		void FractalManagerUI::AddFractal(const Ref<Fractal>& fractal)
		{

		}

		void FractalManagerUI::DeleteFractal()
		{

		}

		void FractalManagerUI::DrawFractalUI()
		{
			if (ImGui::TreeNode("Fractal Creator"))
			{
				char buffer[256];
				memset(buffer, 0, sizeof(buffer));
				std::strncpy(buffer, s_InputFractalName.c_str(), sizeof(buffer));
				if (ImGui::InputText("##Fractal Name", buffer, sizeof(buffer)))
					s_InputFractalName = std::string(buffer);

				if (s_InputFractalName.empty())
					ImGui::Button("Please enter a valid name.");
				else
				{
					if (ImGui::Button("Create"))
						CreateFractal(s_InputFractalName);
				}

				ImGui::TreePop();
			}

			if (ImGui::TreeNodeEx("Fractals"))
			{
				for (uint32_t i = 0; i < s_Views.size(); i++)
				{
					if (ImGui::TreeNode(s_Views[i]->GetName().c_str()))
					{
						std::string editLabel = "Edit##" + s_Views[i]->GetName();
						if (ImGui::Button(editLabel.c_str()))
						{
							if (s_ActiveViewer != nullptr && s_ActiveViewer == s_Views[i])
							{
								s_ActiveViewer = nullptr;
								ImGui::TreePop();
								continue;
							}
							s_ActiveViewer = s_Views[i];
						}

						std::string compileLabel = "Compile and Execute##" + s_Views[i]->GetName();
						if (s_Views[i]->CanCompile() && ImGui::Button(compileLabel.c_str()))
						{
							RM::CompiledFractalSrc injection = s_Views[i]->GetFractal()->CompileProcedural();
							if (RM::ShaderLibrary::Has("TestShaderFrag"))
								RM::ShaderLibrary::Recompile("TestShaderFrag", injection.DefineSrc, injection.ProceduralSrc);
							else
								RM::ShaderLibrary::Load("TestShaderFrag", injection.DefineSrc, injection.ProceduralSrc);
						}

						std::string saveLabel = "Save##" + s_Views[i]->GetName();
						if (s_Views[i]->CanCompile() && ImGui::Button(saveLabel.c_str()))
						{
							FractalSerializer::Serialize(s_Views[i]->GetFractal());
						}

						ImGui::TreePop();
					}
				}

				if (s_ActiveViewer != nullptr)
				{
					ImGui::Begin("Fractal Editor");
					s_ActiveViewer->DisplayFractalViewer();
					ImGui::End();
				}

				ImGui::TreePop();
			}
		}
	}
}