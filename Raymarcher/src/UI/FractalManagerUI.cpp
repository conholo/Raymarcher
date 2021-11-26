#include "rmpch.h"
#include "UI/FractalManagerUI.h"
#include "Renderer/Shader.h"

#include <imgui/imgui.h>

namespace RM
{
	namespace UI
	{
		std::vector<Ref<FractalViewerUI>> FractalManagerUI::s_Views;
		std::string FractalManagerUI::s_InputFractalName = "";
		bool FractalManagerUI::s_EditorOpen = false;
		Ref<FractalViewerUI> FractalManagerUI::s_ActiveViewer = nullptr;

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

				if (ImGui::TreeNodeEx("Fractals"))
				{
					for (uint32_t i = 0; i < s_Views.size(); i++)
					{
						if (ImGui::Button(s_Views[i]->GetName().c_str()))
						{
							if (s_ActiveViewer != nullptr && s_ActiveViewer == s_Views[i])
							{
								s_ActiveViewer = nullptr;
								continue;
							}
							s_ActiveViewer = s_Views[i];
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

				ImGui::TreePop();
			}
		}

		std::vector<FractalCompileData> FractalManagerUI::GetReadyFractals()
		{
			std::vector<FractalCompileData> readyFractalData;
			for (auto viewer : s_Views)
			{
				if (!viewer->CanCompile()) continue;
				FractalCompileData data = { viewer->GetFractal(), viewer->GetBegin(), viewer->GetEnd(), viewer->GetIterations() };
				readyFractalData.push_back(data);
			}

			return readyFractalData;
		}
	}
}