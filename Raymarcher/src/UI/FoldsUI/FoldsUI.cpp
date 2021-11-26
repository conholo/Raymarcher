#include "rmpch.h"
#include "UI/FoldsUI/FoldsUI.h"
#include <imgui/imgui.h>

namespace RM
{
	namespace UI
	{
		void FoldScaleTranslateUI::DrawEditor(const std::string& fractalName) 
		{
			ImGui::DragFloat("Scale", &m_Fold->GetScale(), 0.01f);
			ImGui::DragFloat3("Translation", &m_Fold->GetTranslation().x, 0.01f);
		}

		void FoldPlaneUI::DrawEditor(const std::string& fractalName) 
		{
			std::vector<std::string> foldDirectionOptions = { "None", "Right", "Up", "Forward", "Left", "Down", "Back" };

			std::string preview = foldDirectionOptions[(int)m_Fold->GetDirection()];

			if (ImGui::BeginCombo("Fold Direction", preview.c_str()))
			{
				for (int n = 0; n < foldDirectionOptions.size(); n++)
					if (ImGui::Selectable(foldDirectionOptions[n].c_str(), m_SelectedFoldDirection == n))
						m_SelectedFoldDirection = n;

				ImGui::EndCombo();
			}

			if (m_SelectedFoldDirection != (int)m_Fold->GetDirection())
				m_Fold->GetDirection() = (FoldPlane::FoldDirection)m_SelectedFoldDirection;


			ImGui::DragFloat("Factor", &m_Fold->GetFactor(), 0.01f);
		}

		void FoldMengerUI::DrawEditor(const std::string& fractalName) 
		{
		}

		void FoldSierpinskiUI::DrawEditor(const std::string& fractalName) 
		{
		}

		void FoldBoxUI::DrawEditor(const std::string& fractalName) 
		{
			ImGui::DragFloat3("Range", &m_Fold->GetRange().x, 0.01f);
		}

		void FoldSphereUI::DrawEditor(const std::string& fractalName) 
		{
			ImGui::DragFloat("Min Radius", &m_Fold->GetMinRadius(), 0.01f);
			ImGui::DragFloat("Max Radius", &m_Fold->GetMaxRadius(), 0.01f);
		}

		void FoldAbsUI::DrawEditor(const std::string& fractalName) 
		{
			ImGui::DragFloat3("Center", &m_Fold->GetCenter().x, 0.01f);
		}

		void FoldInversionUI::DrawEditor(const std::string& fractalName) 
		{
			ImGui::DragFloat("Epsilon", &m_Fold->GetEpsilon(), 0.01f);
		}

		void FoldRotateXUI::DrawEditor(const std::string& fractalName) 
		{
			float degrees = glm::degrees(m_Fold->GetRadians());
			if (ImGui::DragFloat("Degrees", &degrees, 0.01f))
			{
				if (glm::radians(degrees) != m_Fold->GetRadians())
					m_Fold->GetRadians() = glm::radians(degrees);
			}
		}

		void FoldRotateYUI::DrawEditor(const std::string& fractalName) 
		{
			float degrees = glm::degrees(m_Fold->GetRadians());
			ImGui::DragFloat("Degrees", &degrees, 0.01f);
			if (glm::radians(degrees) != m_Fold->GetRadians())
				m_Fold->GetRadians() = glm::radians(degrees);
		}

		void FoldRotateZUI::DrawEditor(const std::string& fractalName) 
		{
			float degrees = glm::degrees(m_Fold->GetRadians());
			ImGui::DragFloat("Degrees", &degrees, 0.01f);
			if (glm::radians(degrees) != m_Fold->GetRadians())
				m_Fold->GetRadians() = glm::radians(degrees);
		}

		void FoldRepeatXUI::DrawEditor(const std::string& fractalName) 
		{
			ImGui::DragFloat("Step", &m_Fold->GetStep(), 0.01f);
		}

		void FoldRepeatYUI::DrawEditor(const std::string& fractalName) 
		{
			ImGui::DragFloat("Step", &m_Fold->GetStep(), 0.01f);
		}

		void FoldRepeatZUI::DrawEditor(const std::string& fractalName) 
		{
			ImGui::DragFloat("Step", &m_Fold->GetStep(), 0.01f);
		}

		void FoldRepeatXYZUI::DrawEditor(const std::string& fractalName) 
		{
			ImGui::DragFloat("Step", &m_Fold->GetStep(), 0.01f);
		}
	}
}