#include "rmpch.h"
#include "UI/ColorModsUI/ColorModsUI.h"

#include <imgui/imgui.h>

namespace RM
{
	namespace UI
	{
		static void DrawColorModWindow(const std::string& fractalName, const std::string& title, float* dragFloatA, float* dragFloatB)
		{
			std::string originID = "Origin##" + fractalName + title;
			std::string scaleID = "Scale##" + fractalName + title;
			ImGui::PushID(originID.c_str());
			ImGui::PushID(scaleID.c_str());
			ImGui::DragFloat3(originID.c_str(), dragFloatA);
			ImGui::DragFloat3(scaleID.c_str(), dragFloatB);
			ImGui::PopID();
			ImGui::PopID();
		}

		void ColorModSumUI::DrawEditor(const std::string& fractalName)
		{
			std::string title = "Color Mod Sum " + std::to_string(m_ID);
			DrawColorModWindow(fractalName, title, &m_ColorModSum->GetOrigin().x, &m_ColorModSum->GetScale().x);
		}

		void ColorModSumAbsUI::DrawEditor(const std::string& fractalName)
		{
			std::string title = "Color Mod Sum Abs " + std::to_string(m_ID);
			DrawColorModWindow(fractalName, title, &m_ColorModSumAbs->GetOrigin().x, &m_ColorModSumAbs->GetScale().x);
		}

		void ColorModMinUI::DrawEditor(const std::string& fractalName)
		{
			std::string title = "Color Mod Min " + std::to_string(m_ID);
			DrawColorModWindow(fractalName, title, &m_ColorModMin->GetOrigin().x, &m_ColorModMin->GetScale().x);
		}

		void ColorModMinAbsUI::DrawEditor(const std::string& fractalName)
		{
			std::string title = "Color Mod Min Abs " + std::to_string(m_ID);
			DrawColorModWindow(fractalName, title, &m_ColorModMinAbs->GetOrigin().x, &m_ColorModMinAbs->GetScale().x);
		}

		void ColorModMaxUI::DrawEditor(const std::string& fractalName)
		{
			std::string title = "Color Mod Max " + std::to_string(m_ID);
			DrawColorModWindow(fractalName, title, &m_ColorModMax->GetOrigin().x, &m_ColorModMax->GetScale().x);
		}

		void ColorModMaxAbsUI::DrawEditor(const std::string& fractalName)
		{
			std::string title = "Color Mod Max Abs " + std::to_string(m_ID);
			DrawColorModWindow(fractalName, title, &m_ColorModMaxAbs->GetOrigin().x, &m_ColorModMaxAbs->GetScale().x);
		}
	}
}