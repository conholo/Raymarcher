#include "rmpch.h"'
#include "UI/GeometryUI/FractalGeometryUI.h"

#include <imgui/imgui.h>

namespace RM
{
	namespace UI
	{
		void FractalGeometryBoxUI::DrawEditor(const std::string& fractalName)
		{
			std::vector<std::string> colorOptions = { "Auto", "Manual"};

			std::string preview = (int)m_Box->GetColorType() == 1 ? colorOptions[0] : colorOptions[1];

			if (ImGui::BeginCombo("Color Options", preview.c_str()))
			{
				for (int n = 0; n < colorOptions.size(); n++)
					if (ImGui::Selectable(colorOptions[n].c_str(), m_SelectedColorOption == n))
						m_SelectedColorOption = n;

				ImGui::EndCombo();
			}

			if ((int)m_Box->GetColorType() != m_SelectedColorOption + 1)
				m_Box->GetColorType() = (ColorType)(m_SelectedColorOption + 1);

			if (m_SelectedColorOption == 1)
				ImGui::DragFloat3("Color", &m_Box->GetColor().x, 0.01f);
			ImGui::DragFloat3("Scale", &m_Box->GetScale().x, 0.01f);
			ImGui::DragFloat3("Offset", &m_Box->GetOffset().x, 0.01f);
		}

		void FractalGeometrySphereUI::DrawEditor(const std::string& fractalName)
		{
			std::vector<std::string> colorOptions = { "Auto", "Manual" };

			std::string preview = (int)m_Sphere->GetColorType() == 1 ? colorOptions[0] : colorOptions[1];

			if (ImGui::BeginCombo("Color Options", preview.c_str()))
			{
				for (int n = 0; n < colorOptions.size(); n++)
					if (ImGui::Selectable(colorOptions[n].c_str(), m_SelectedColorOption == n))
						m_SelectedColorOption = n;

				ImGui::EndCombo();
			}

			if ((int)m_Sphere->GetColorType() != m_SelectedColorOption + 1)
				m_Sphere->GetColorType() = (ColorType)(m_SelectedColorOption + 1);

			if (m_SelectedColorOption == 1)
				ImGui::DragFloat3("Color", &m_Sphere->GetColor().x, 0.01f);
			ImGui::DragFloat("Radius", &m_Sphere->GetRadius(), 0.01f);
			ImGui::DragFloat3("Offset", &m_Sphere->GetCenter().x, 0.01f);
		}

		void FractalGeometryTetrahedronUI::DrawEditor(const std::string& fractalName)
		{
			std::vector<std::string> colorOptions = { "Auto", "Manual" };

			std::string preview = (int)m_Tetrahedron->GetColorType() == 1 ? colorOptions[0] : colorOptions[1];

			if (ImGui::BeginCombo("Color Options", preview.c_str()))
			{
				for (int n = 0; n < colorOptions.size(); n++)
					if (ImGui::Selectable(colorOptions[n].c_str(), m_SelectedColorOption == n))
						m_SelectedColorOption = n;

				ImGui::EndCombo();
			}

			if ((int)m_Tetrahedron->GetColorType() != m_SelectedColorOption + 1)
				m_Tetrahedron->GetColorType() = (ColorType)(m_SelectedColorOption + 1);

			if (m_SelectedColorOption == 1)
				ImGui::DragFloat3("Color", &m_Tetrahedron->GetColor().x, 0.01f);
			ImGui::DragFloat("Radius", &m_Tetrahedron->GetRadius(), 0.01f);
			ImGui::DragFloat3("Center", &m_Tetrahedron->GetCenter().x, 0.01f);
		}
	}
}