#include "rmpch.h"
#include "UI/FractalViewerUI.h"
#include "Renderer/Shader.h"
#include <imgui/imgui.h>

namespace RM
{
	namespace UI
	{
		Ref<FractalComponentEditorUI> FractalViewerUI::s_ActiveEditor = nullptr;
		bool FractalViewerUI::s_EditorOpen = false;

		FractalViewerUI::FractalViewerUI(const Ref<Fractal>& fractal)
			:m_Fractal(fractal)
		{
			if (m_Fractal->Transformations().size() > 0)
			{
				for (auto transformation : m_Fractal->Transformations())
				{
					AddColorMod(transformation->Name(), transformation);
					AddFold(transformation->Name(), transformation);
					AddGeometry(transformation->Name(), transformation);
				}

				m_Finalized = true;
			}

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

			m_FoldsOptions =
			{
				FoldAbs::ToString(),
				FoldBox::ToString(),
				FoldSphere::ToString(),
				FoldInversion::ToString(),
				FoldMenger::ToString(),
				FoldPlane::ToString(),
				FoldRepeatX::ToString(),
				FoldRepeatY::ToString(),
				FoldRepeatZ::ToString(),
				FoldRepeatXYZ::ToString(),
				FoldRotateX::ToString(),
				FoldRotateY::ToString(),
				FoldRotateZ::ToString(),
				FoldScaleTranslate::ToString(),
				FoldScaleOrigin::ToString(),
				FoldSierpinski::ToString(),
			};

			m_GeometryOptions =
			{
				Box::ToString(),
				Sphere::ToString(),
				Tetrahedron::ToString(),
			};
		}

		void FractalViewerUI::DisplayFractalViewer()
		{
			ImGui::Text(m_Fractal->GetName().c_str());
			
			static const uint32_t columnCount = 4;
			static ImGuiTableFlags flags = ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable;

			if (m_ComponentEditors.size() > 0())
			{
				if (ImGui::Button("Finalize", { 200, 50 }))
				{
					m_Fractal = CreateRef<Fractal>(GetName());

					std::vector<Ref<IGLSLConvertable>> convertables;
					for (auto editor : m_ComponentEditors)
						convertables.push_back(editor->GetConvertable());

					m_Fractal->SetTransformations(convertables);
					m_Fractal->SetBegin(m_IterationIndexBegin);
					m_Fractal->SetEnd(m_IterationIndexEnd);
					m_Fractal->SetIterations(m_IterationCount);

					m_Finalized = true;
				}
			}


			if (ImGui::TreeNodeEx("Scene Parameters"))
			{
				FractalDefines& defines = m_Fractal->GetDefines();

				for (auto boolDefine : defines.BoolDefines())
				{
					std::string name = defines.DefineToString(boolDefine.first);
					bool value = boolDefine.second;
					ImGui::Checkbox(name.c_str(), &value);

					if (value != boolDefine.second)
						defines.BoolDefines()[boolDefine.first] = value;
				}

				for (auto floatDefines : defines.FloatDefines())
				{
					std::string name = defines.DefineToString(floatDefines.first);
					float value = floatDefines.second;
					ImGui::DragFloat(name.c_str(), &value, 0.01f, -1000.0, 1000.0, "%.5f");

					if (value != floatDefines.second)
						defines.FloatDefines()[floatDefines.first] = value;
				}

				for (auto vec3Define : defines.Vec3Defines())
				{
					std::string name = defines.DefineToString(vec3Define.first);
					glm::vec3 value = vec3Define.second;
					ImGui::DragFloat3(name.c_str(), &value.x, 0.01f);

					if (value != vec3Define.second)
						defines.Vec3Defines()[vec3Define.first] = value;
				}

				ImGui::TreePop();
			}

			if (ImGui::TreeNodeEx("Add Component"))
			{
				if (ImGui::TreeNode("Add Color Mod"))
				{
					if (ImGui::BeginTable("Color Mods", columnCount, flags))
					{
						ImGui::TableSetupScrollFreeze(0, 1); // Make top row always visible

						uint32_t rowCount = glm::ceil((float)m_ColorModOptions.size() / (float)4);
						ImGui::TableHeadersRow();

						for (uint32_t row = 0; row < rowCount; row++)
						{
							ImGui::TableNextRow();
							for (uint32_t column = 0; column < 4; column++)
							{
								uint32_t index = columnCount * row + column;

								if (index > m_ColorModOptions.size() - 1) continue;

								ImGui::TableSetColumnIndex(column);
								if (ImGui::Button(m_ColorModOptions[index].c_str()))
									AddColorMod(m_ColorModOptions[index]);
							}
						}
						ImGui::EndTable();
					}
					ImGui::TreePop();
				}

				if (ImGui::TreeNode("Add Fold"))
				{
					if (ImGui::BeginTable("Folds", columnCount, flags))
					{
						ImGui::TableSetupScrollFreeze(0, 1); // Make top row always visible

						uint32_t rowCount = glm::ceil((float)m_FoldsOptions.size() / (float)4);
						ImGui::TableHeadersRow();

						for (uint32_t row = 0; row < rowCount; row++)
						{
							ImGui::TableNextRow();
							for (uint32_t column = 0; column < 4; column++)
							{
								uint32_t index = columnCount * row + column;

								if (index > m_FoldsOptions.size() - 1) continue;

								ImGui::TableSetColumnIndex(column);
								if (ImGui::Button(m_FoldsOptions[index].c_str()))
									AddFold(m_FoldsOptions[index]);
							}
						}
						ImGui::EndTable();
					}
					ImGui::TreePop();
				}

				if (ImGui::TreeNode("Add Geometry"))
				{
					if (ImGui::BeginTable("Fractal Geometries", columnCount, flags))
					{
						ImGui::TableSetupScrollFreeze(0, 1); // Make top row always visible

						uint32_t rowCount = glm::ceil((float)m_GeometryOptions.size() / (float)4);
						ImGui::TableHeadersRow();

						for (uint32_t row = 0; row < rowCount; row++)
						{
							ImGui::TableNextRow();
							for (uint32_t column = 0; column < 4; column++)
							{
								uint32_t index = columnCount * row + column;

								if (index > m_GeometryOptions.size() - 1) continue;

								ImGui::TableSetColumnIndex(column);
								if (ImGui::Button(m_GeometryOptions[index].c_str()))
									AddGeometry(m_GeometryOptions[index]);
							}
						}
						ImGui::EndTable();
					}
					ImGui::TreePop();
				}

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("View Mods"))
			{
				ImGui::SliderInt("Iterations", &m_IterationCount, 1, 100);
				ImGui::SliderInt("Begin Iterations", &m_IterationIndexBegin, 0, m_ComponentEditors.size() == 0 ? 0 : m_ComponentEditors.size() - 1);
				if (m_IterationIndexBegin > m_IterationIndexEnd)
					m_IterationIndexEnd = m_IterationIndexBegin;
				ImGui::SliderInt("End Iterations", &m_IterationIndexEnd, m_IterationIndexBegin, m_ComponentEditors.size() == 0 ? 0 : m_ComponentEditors.size() - 1);

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
					if (i == m_IterationIndexBegin)
						ImGui::TextColored({ 0.0f, 1.0f, 0.0f, 1.0f }, "Iteration Begin");

					std::string id = m_ComponentEditors[i]->GetUIID();
					ImGui::PushID(id.c_str());

					if (ImGui::Button(id.c_str(), ImVec2(200, 60)))
					{
						if (mode == (Mode)ModeEdit)
						{
							if (s_EditorOpen && m_ComponentEditors[i] == s_ActiveEditor)
							{
								s_EditorOpen = false;
								s_ActiveEditor = nullptr;
								ImGui::PopID();
								continue;
							}

							s_ActiveEditor = m_ComponentEditors[i];
							s_EditorOpen = true;
						}
						else if (mode == (Mode)ModeDelete)
						{
							s_EditorOpen = false;
							s_ActiveEditor = nullptr;
							ImGui::OpenPopup("Delete?");
						}

					}

					if (mode == (Mode)ModeSwap)
					{
						s_EditorOpen = false;
						s_ActiveEditor = nullptr;
						if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
						{
							ImGui::SetDragDropPayload("Component", &i, sizeof(uint32_t));
							std::string id = "Swap " +  m_ComponentEditors[i]->GetUIID();
							ImGui::Text(id.c_str());
							ImGui::EndDragDropSource();
						}

						if (ImGui::BeginDragDropTarget())
						{
							if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Component"))
							{
								uint32_t payloadID = *(const uint32_t*)payload->Data;
								
								Ref<FractalComponentEditorUI> temp = m_ComponentEditors[i];
								m_ComponentEditors[i] = m_ComponentEditors[payloadID];
								m_ComponentEditors[i]->SetID(i);
								m_ComponentEditors[payloadID] = temp;
								m_ComponentEditors[payloadID]->SetID(payloadID);
							}
							ImGui::EndDragDropTarget();
						}
					}

					if (i == m_IterationIndexEnd)
						ImGui::TextColored({ 0.0f, 1.0f, 0.0f, 1.0f }, "Iteration End");

					if (ImGui::BeginPopupModal("Delete?", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
					{
						ImGui::Text("Are you sure you want to delete?  Your fractal component will be deleted.");
						ImGui::Separator();

						if (ImGui::Button("OK", ImVec2(120, 0)))
						{
							uint32_t deleteID = i;

							m_ComponentEditors.erase(m_ComponentEditors.begin() + deleteID);
							m_ComponentCount--;

							for (uint32_t j = 0; j < m_ComponentEditors.size(); j++)
								m_ComponentEditors[j]->SetID(j);


							ImGui::CloseCurrentPopup();
						}
						ImGui::SetItemDefaultFocus();
						ImGui::SameLine();
						if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
						ImGui::EndPopup();
					}

					ImGui::PopID();
				}

				if (s_EditorOpen)
				{
					std::string windowName = GetName() + ": " + s_ActiveEditor->GetUIID();

					if (!ImGui::Begin(windowName.c_str(), &s_EditorOpen, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_AlwaysAutoResize))
					{
						ImGui::End();
					}
					else
					{
						s_ActiveEditor->DrawEditor(GetName());
						ImGui::End();
					}
				}

				ImGui::TreePop();
			}
		}

		void FractalViewerUI::AddColorMod(const std::string& name, const Ref<IGLSLConvertable>& convertable)
		{
			if (name == ColorModZero::ToString())
			{
				auto reference = std::dynamic_pointer_cast<ColorModZero>(convertable);
				Ref<ColorModZeroUI> zeroUI = CreateRef<ColorModZeroUI>(m_ComponentCount++, reference == nullptr ? CreateRef<ColorModZero>() : reference);
				m_ComponentEditors.push_back(zeroUI);
			}
			else if (name == ColorModInfinity::ToString())
			{
				auto reference = std::dynamic_pointer_cast<ColorModInfinity>(convertable);
				Ref<ColorModInfinityUI> inifinityUI = CreateRef<ColorModInfinityUI>(m_ComponentCount++, reference == nullptr ? CreateRef<ColorModInfinity>() : reference);
				m_ComponentEditors.push_back(inifinityUI);
			}
			else if (name == ColorModNegativeInfinity::ToString())
			{
				auto reference = std::dynamic_pointer_cast<ColorModNegativeInfinity>(convertable);
				Ref<ColorModNegativeInfinityUI> negativeInfinityUI = CreateRef<ColorModNegativeInfinityUI>(m_ComponentCount++, 
					reference == nullptr ? CreateRef<ColorModNegativeInfinity>() : reference);
				m_ComponentEditors.push_back(negativeInfinityUI);
			}
			else if (name == ColorModSum::ToString())
			{
				auto reference = std::dynamic_pointer_cast<ColorModSum>(convertable);
				Ref<ColorModSumUI> sumUI = CreateRef<ColorModSumUI>(m_ComponentCount++, 
					reference == nullptr ? CreateRef<ColorModSum>() : reference);
				m_ComponentEditors.push_back(sumUI);
			}
			else if (name == ColorModSumAbs::ToString())
			{
				auto reference = std::dynamic_pointer_cast<ColorModSumAbs>(convertable);
				Ref<ColorModSumAbsUI> sumAbsUI = CreateRef<ColorModSumAbsUI>(m_ComponentCount++, 
					reference == nullptr ? CreateRef<ColorModSumAbs>() : reference);
				m_ComponentEditors.push_back(sumAbsUI);
			}
			else if (name == ColorModMin::ToString())
			{
				auto reference = std::dynamic_pointer_cast<ColorModMin>(convertable);
				Ref<ColorModMinUI> minUI = CreateRef<ColorModMinUI>(m_ComponentCount++, 
					reference == nullptr ? CreateRef<ColorModMin>() : reference);
				m_ComponentEditors.push_back(minUI);
			}
			else if (name == ColorModMinAbs::ToString())
			{
				auto reference = std::dynamic_pointer_cast<ColorModMinAbs>(convertable);
				Ref<ColorModMinAbsUI> minAbsUI = CreateRef<ColorModMinAbsUI>(m_ComponentCount++, 
					reference == nullptr ? CreateRef<ColorModMinAbs>() : reference);
				m_ComponentEditors.push_back(minAbsUI);
			}
			else if (name == ColorModMax::ToString())
			{
				auto reference = std::dynamic_pointer_cast<ColorModMax>(convertable);
				Ref<ColorModMaxUI> maxUI = CreateRef<ColorModMaxUI>(m_ComponentCount++, 
					reference == nullptr ? CreateRef<ColorModMax>() : reference);
				m_ComponentEditors.push_back(maxUI);
			}
			else if (name == ColorModMaxAbs::ToString())
			{
				auto reference = std::dynamic_pointer_cast<ColorModMaxAbs>(convertable);
				Ref<ColorModMaxAbsUI> maxAbsUI = CreateRef<ColorModMaxAbsUI>(m_ComponentCount++, 
					reference == nullptr ? CreateRef<ColorModMaxAbs>() : reference);
				m_ComponentEditors.push_back(maxAbsUI);
			}

			s_EditorOpen = false;
		}

		void FractalViewerUI::AddFold(const std::string& name, const Ref<IGLSLConvertable>& convertable)
		{
			if (name == FoldAbs::ToString())
			{
				auto reference = std::dynamic_pointer_cast<FoldAbs>(convertable);
				Ref<FoldAbsUI> fold = CreateRef<FoldAbsUI>(m_ComponentCount++, 
					reference == nullptr ? CreateRef<FoldAbs>() : reference);
				m_ComponentEditors.push_back(fold);
			}
			else if (name == FoldBox::ToString())
			{
				auto reference = std::dynamic_pointer_cast<FoldBox>(convertable);
				Ref<FoldBoxUI> fold = CreateRef<FoldBoxUI>(m_ComponentCount++, 
					reference == nullptr ? CreateRef<FoldBox>() : reference);
				m_ComponentEditors.push_back(fold);
			}
			else if (name == FoldInversion::ToString())
			{
				auto reference = std::dynamic_pointer_cast<FoldInversion>(convertable);
				Ref<FoldInversionUI> fold = CreateRef<FoldInversionUI>(m_ComponentCount++, 
					reference == nullptr ? CreateRef<FoldInversion>() : reference);
				m_ComponentEditors.push_back(fold);
			}
			else if (name == FoldMenger::ToString())
			{
				auto reference = std::dynamic_pointer_cast<FoldMenger>(convertable);
				Ref<FoldMengerUI> fold = CreateRef<FoldMengerUI>(m_ComponentCount++, 
					reference == nullptr ? CreateRef<FoldMenger>() : reference);
				m_ComponentEditors.push_back(fold);
			}
			else if (name == FoldPlane::ToString())
			{
				auto reference = std::dynamic_pointer_cast<FoldPlane>(convertable);
				Ref<FoldPlaneUI> fold = CreateRef<FoldPlaneUI>(m_ComponentCount++, 
					reference == nullptr ? CreateRef<FoldPlane>() : reference);
				if (reference != nullptr)
					fold->SetSelectedFoldDirection((int)reference->GetDirection());
				m_ComponentEditors.push_back(fold);
			}
			else if (name == FoldRepeatX::ToString())
			{
				auto reference = std::dynamic_pointer_cast<FoldRepeatX>(convertable);
				Ref<FoldRepeatXUI> fold = CreateRef<FoldRepeatXUI>(m_ComponentCount++, 
					reference == nullptr ? CreateRef<FoldRepeatX>() : reference);
				m_ComponentEditors.push_back(fold);
			}
			else if (name == FoldRepeatY::ToString())
			{
				auto reference = std::dynamic_pointer_cast<FoldRepeatY>(convertable);
				Ref<FoldRepeatYUI> fold = CreateRef<FoldRepeatYUI>(m_ComponentCount++, 
					reference == nullptr ? CreateRef<FoldRepeatY>() : reference);
				m_ComponentEditors.push_back(fold);
			}
			else if (name == FoldRepeatZ::ToString())
			{
				auto reference = std::dynamic_pointer_cast<FoldRepeatZ>(convertable);
				Ref<FoldRepeatZUI> fold = CreateRef<FoldRepeatZUI>(m_ComponentCount++, 
					reference == nullptr ? CreateRef<FoldRepeatZ>() : reference);
				m_ComponentEditors.push_back(fold);
			}
			else if (name == FoldRepeatXYZ::ToString())
			{
				auto reference = std::dynamic_pointer_cast<FoldRepeatXYZ>(convertable);
				Ref<FoldRepeatXYZUI> fold = CreateRef<FoldRepeatXYZUI>(m_ComponentCount++, 
					reference == nullptr ? CreateRef<FoldRepeatXYZ>() : reference);
				m_ComponentEditors.push_back(fold);
			}
			else if (name == FoldRotateX::ToString())
			{
				auto reference = std::dynamic_pointer_cast<FoldRotateX>(convertable);
				Ref<FoldRotateXUI> fold = CreateRef<FoldRotateXUI>(m_ComponentCount++, 
					reference == nullptr ? CreateRef<FoldRotateX>() : reference);
				m_ComponentEditors.push_back(fold);
			}
			else if (name == FoldRotateY::ToString())
			{
				auto reference = std::dynamic_pointer_cast<FoldRotateY>(convertable);
				Ref<FoldRotateYUI> fold = CreateRef<FoldRotateYUI>(m_ComponentCount++,
					reference == nullptr ? CreateRef<FoldRotateY>() : reference);
				m_ComponentEditors.push_back(fold);
			}
			else if (name == FoldRotateZ::ToString())
			{
				auto reference = std::dynamic_pointer_cast<FoldRotateZ>(convertable);
				Ref<FoldRotateZUI> fold = CreateRef<FoldRotateZUI>(m_ComponentCount++, 
					reference == nullptr ? CreateRef<FoldRotateZ>() : reference);
				m_ComponentEditors.push_back(fold);
			}
			else if (name == FoldScaleTranslate::ToString())
			{
				auto reference = std::dynamic_pointer_cast<FoldScaleTranslate>(convertable);
				Ref<FoldScaleTranslateUI> fold = CreateRef<FoldScaleTranslateUI>(m_ComponentCount++, 
					reference == nullptr ? CreateRef<FoldScaleTranslate>() : reference);
				m_ComponentEditors.push_back(fold);
			}
			else if (name == FoldSphere::ToString())
			{
				auto reference = std::dynamic_pointer_cast<FoldSphere>(convertable);
				Ref<FoldSphereUI> fold = CreateRef<FoldSphereUI>(m_ComponentCount++, 
					reference == nullptr ? CreateRef<FoldSphere>() : reference);
				m_ComponentEditors.push_back(fold);
			}
			else if (name == FoldScaleOrigin::ToString())
			{
				auto reference = std::dynamic_pointer_cast<FoldScaleOrigin>(convertable);
				Ref<FoldScaleOriginUI> fold = CreateRef<FoldScaleOriginUI>(m_ComponentCount++, 
					reference == nullptr ? CreateRef<FoldScaleOrigin>() : reference);
				m_ComponentEditors.push_back(fold);
			}
			else if (name == FoldSierpinski::ToString())
			{
				auto reference = std::dynamic_pointer_cast<FoldSierpinski>(convertable);
				Ref<FoldSierpinskiUI> fold = CreateRef<FoldSierpinskiUI>(m_ComponentCount++,
					reference == nullptr ? CreateRef<FoldSierpinski>() : reference);
				m_ComponentEditors.push_back(fold);
			}

			s_EditorOpen = false;
		}

		void FractalViewerUI::AddGeometry(const std::string& name, const Ref<IGLSLConvertable>& convertable)
		{
			if (name == Box::ToString())
			{
				auto reference = std::dynamic_pointer_cast<Box>(convertable);
				Ref<FractalGeometryBoxUI> geo = CreateRef<FractalGeometryBoxUI>(m_ComponentCount++, 
					reference == nullptr ? CreateRef<Box>() : reference);
				m_ComponentEditors.push_back(geo);
			}
			else if (name == Sphere::ToString())
			{
				auto reference = std::dynamic_pointer_cast<Sphere>(convertable);
				Ref<FractalGeometrySphereUI> geo = CreateRef<FractalGeometrySphereUI>(m_ComponentCount++, 
					reference == nullptr ? CreateRef<Sphere>() : reference);
				m_ComponentEditors.push_back(geo);
			}
			else if (name == Tetrahedron::ToString())
			{
				auto reference = std::dynamic_pointer_cast<Tetrahedron>(convertable);
				Ref<FractalGeometryTetrahedronUI> geo = CreateRef<FractalGeometryTetrahedronUI>(m_ComponentCount++, 
					reference == nullptr ? CreateRef<Tetrahedron>() : reference);
				m_ComponentEditors.push_back(geo);
			}

			s_EditorOpen = false;
		}
	}
}