#pragma once

#include "Fractal/Fractal.h"

#include "UI/FractalComponentEditorUI.h"
#include "Fractal/ColorMods/ColorMod.h"
#include "UI/ColorModsUI/ColorModsUI.h"

namespace RM
{
	namespace UI
	{
		class FractalViewerUI
		{
		public:
			FractalViewerUI(const Ref<Fractal>& fractal);
			~FractalViewerUI() = default;
				
			void DisplayFractalViewer();

			void AddColorMod(const std::string& name);

			std::string GetName() const { return m_Fractal->GetName(); }

		private:
			Ref<Fractal> m_Fractal;
			uint32_t m_ComponentCount = 0;

			std::vector<Ref<FractalComponentEditorUI>> m_ComponentEditors;

			static Ref<FractalComponentEditorUI> s_ActiveEditor;

			std::vector<std::string> m_ColorModOptions;
		};
	}
}