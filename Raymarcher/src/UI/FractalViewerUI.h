#pragma once

#include "Fractal/Fractal.h"

#include "UI/FractalComponentEditorUI.h"
#include "Fractal/ColorMods/ColorMod.h"
#include "UI/ColorModsUI/ColorModsUI.h"
#include "UI/FoldsUI/FoldsUI.h"
#include "UI/GeometryUI/FractalGeometryUI.h"
#include <glm/glm.hpp>

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
			void AddFold(const std::string& name);
			void AddGeometry(const std::string& name);

			bool CanCompile() const { return m_Finalized; }
			std::string GetName() const { return m_Fractal->GetName(); }

			const Ref<Fractal>& GetFractal() const { return m_Fractal; }
			uint32_t GetBegin() const { return m_IterationIndexBegin; }
			uint32_t GetEnd() const { return m_IterationIndexEnd; }
			uint32_t GetIterations() const { return m_IterationCount; }

			std::vector<Ref<FractalComponentEditorUI>> GetComponentEditors() const { return m_ComponentEditors; }

		private:
			bool m_Finalized = false;
			Ref<Fractal> m_Fractal;
			uint32_t m_ComponentCount = 0;
			int m_IterationIndexBegin = 0;
			int m_IterationIndexEnd = 0;
			int m_IterationCount = 1;

			std::vector<Ref<FractalComponentEditorUI>> m_ComponentEditors;

			static bool s_EditorOpen;
			static Ref<FractalComponentEditorUI> s_ActiveEditor;

			std::vector<std::string> m_ColorModOptions;
			std::vector<std::string> m_FoldsOptions;
			std::vector<std::string> m_GeometryOptions;
		};
	}
}