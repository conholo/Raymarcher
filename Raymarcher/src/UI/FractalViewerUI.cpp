#include "rmpch.h"
#include "UI/FractalViewerUI.h"
#include <imgui/imgui.h>

namespace RM
{
	namespace UI
	{
		Ref<FractalComponentEditorUI> FractalViewerUI::s_ActiveEditor = nullptr;

		FractalViewerUI::FractalViewerUI(const Ref<Fractal>& fractal)
			:m_Fractal(fractal)
		{
			m_ColorModOptions =
			{
				ColorModZero::ToString(),
				ColorModInfinity::ToString(),
				ColorModNegativeInfinity::ToString(),
				ColorModSum::ToString(),
				ColorModSumAbs::ToString(),
				ColorModMin::ToString(),
				ColorModMinAbs::ToString(),
				ColorModMax::ToString(),
				ColorModMaxAbs::ToString(),
			};
		}

		void FractalViewerUI::DisplayFractalViewer()
		{
			ImGui::Text(m_Fractal->GetName().c_str());
			
			if (ImGui::TreeNodeEx("Add Component"))
			{
				if (ImGui::TreeNode("Add Color Mod"))
				{
					for (uint32_t i = 0; i < m_ColorModOptions.size(); i++)
					{
						if (ImGui::Button(m_ColorModOptions[i].c_str()))
							AddColorMod(m_ColorModOptions[i]);
					}
					ImGui::TreePop();
				}

				if (ImGui::TreeNode("Add Fold"))
				{
					ImGui::TreePop();
				}

				if (ImGui::TreeNode("Add Geometry"))
				{
					ImGui::TreePop();
				}

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("View Mods"))
			{
				enum Mode
				{
					ModeEdit,
					ModeSwap,
					ModeDelete
				};
				static int mode = 0;
				if (ImGui::RadioButton("Edit", mode == ModeEdit)) { mode = ModeEdit; } ImGui::SameLine();
				if (ImGui::RadioButton("Swap", mode == ModeSwap)) { mode = ModeSwap; } ImGui::SameLine();
				if (ImGui::RadioButton("Delete", mode == ModeDelete)) { mode = ModeDelete; }
				
				
				for (uint32_t i = 0; i < m_ComponentEditors.size(); i++)
				{
					std::string id = m_ComponentEditors[i]->GetUIID();
					ImGui::PushID(id.c_str());

					if (ImGui::Button(id.c_str(), ImVec2(200, 60)) && mode == (Mode)ModeEdit)
						s_ActiveEditor = m_ComponentEditors[i];

					if (s_ActiveEditor != nullptr)
					{
						std::string windowName = GetName() + ": " + s_ActiveEditor->GetUIID();
						ImGui::Begin(windowName.c_str());
						s_ActiveEditor->DrawEditor(GetName());
						ImGui::End();
					}

					if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
					{
						ImGui::EndDragDropSource();
					}

					if (ImGui::BeginDragDropTarget())
					{
						ImGui::EndDragDropTarget();
					}

					ImGui::PopID();
				}

				ImGui::TreePop();
			}
		}

		void FractalViewerUI::AddColorMod(const std::string& name)
		{
			if (name == ColorModZero::ToString())
			{
				Ref<ColorModZeroUI> zeroUI = CreateRef<ColorModZeroUI>(m_ComponentCount++);
				m_ComponentEditors.push_back(zeroUI);
			}
			else if (name == ColorModInfinity::ToString())
			{
				Ref<ColorModInfinityUI> inifinityUI = CreateRef<ColorModInfinityUI>(m_ComponentCount++);
				m_ComponentEditors.push_back(inifinityUI);
			}
			else if (name == ColorModNegativeInfinity::ToString())
			{
				Ref<ColorModNegativeInfinityUI> negativeInfinityUI = CreateRef<ColorModNegativeInfinityUI>(m_ComponentCount++);
				m_ComponentEditors.push_back(negativeInfinityUI);
			}
			else if (name == ColorModSum::ToString())
			{
				Ref<ColorModSumUI> sumUI = CreateRef<ColorModSumUI>(m_ComponentCount++, CreateRef<ColorModSum>());
				m_ComponentEditors.push_back(sumUI);
			}
			else if (name == ColorModSumAbs::ToString())
			{
				Ref<ColorModSumAbsUI> sumAbsUI = CreateRef<ColorModSumAbsUI>(m_ComponentCount++, CreateRef<ColorModSumAbs>());
				m_ComponentEditors.push_back(sumAbsUI);
			}
			else if (name == ColorModMin::ToString())
			{
				Ref<ColorModMinUI> minUI = CreateRef<ColorModMinUI>(m_ComponentCount++, CreateRef<ColorModMin>());
				m_ComponentEditors.push_back(minUI);
			}
			else if (name == ColorModMinAbs::ToString())
			{
				Ref<ColorModMinAbsUI> minAbsUI = CreateRef<ColorModMinAbsUI>(m_ComponentCount++, CreateRef<ColorModMinAbs>());
				m_ComponentEditors.push_back(minAbsUI);
			}
			else if (name == ColorModMax::ToString())
			{
				Ref<ColorModMaxUI> maxUI = CreateRef<ColorModMaxUI>(m_ComponentCount++, CreateRef<ColorModMax>());
				m_ComponentEditors.push_back(maxUI);
			}
			else if (name == ColorModMaxAbs::ToString())
			{
				Ref<ColorModMaxAbsUI> maxAbsUI = CreateRef<ColorModMaxAbsUI>(m_ComponentCount++, CreateRef<ColorModMaxAbs>());
				m_ComponentEditors.push_back(maxAbsUI);
			}

			s_ActiveEditor = nullptr;
		}
	}
}