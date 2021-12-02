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

			void AddColorMod(const std::string& name, const Ref<IGLSLConvertable>& convertable = nullptr);
			void AddFold(const std::string& name, const Ref<IGLSLConvertable>& convertable = nullptr);
			void AddGeometry(const std::string& name, const Ref<IGLSLConvertable>& convertable = nullptr);

			bool CanCompile() const { return m_Finalized; }
			std::string GetName() const { return m_Fractal->GetName(); }

			const Ref<Fractal>& GetFractal() const { return m_Fractal; }
			uint32_t GetBegin() const { return m_IterationIndexBegin; }
			uint32_t GetEnd() const { return m_IterationIndexEnd; }
			uint32_t GetIterations() const { return m_IterationCount; }

			void SetBegin(uint32_t begin) { m_IterationIndexBegin = begin; }
			void SetEnd(uint32_t end) { m_IterationIndexEnd = end; }
			void SetIterationCount(uint32_t iterations) { m_IterationCount = iterations; }

			std::vector<Ref<FractalComponentEditorUI>> GetComponentEditors() const { return m_ComponentEditors; }

		private:
			bool m_Finalized = false;
			Ref<Fractal> m_Fractal;
			uint32_t m_ComponentCount = 0;
			int m_IterationIndexBegin = 0;
			int m_IterationIndexEnd = 0;
			int m_IterationCount = 1;

			bool m_HasRotationX = false;
			bool m_HasRotationY = false;
			bool m_HasRotationZ = false;

			glm::vec3 m_IntializedRadians;
			glm::vec3 m_RotationSpeedValues = glm::vec3(0.0);

			Ref<FoldRotateX> m_XRotator;
			Ref<FoldRotateY> m_YRotator;
			Ref<FoldRotateZ> m_ZRotator;

			bool m_DoRotationX = false;
			bool m_DoRotationY = false;
			bool m_DoRotationZ = false;

			bool m_XUpdated = false;
			bool m_YUpdated = false;
			bool m_ZUpdated = false;

			std::vector<Ref<FractalComponentEditorUI>> m_ComponentEditors;

			static bool s_EditorOpen;
			static Ref<FractalComponentEditorUI> s_ActiveEditor;

			std::vector<std::string> m_ColorModOptions;
			std::vector<std::string> m_FoldsOptions;
			std::vector<std::string> m_GeometryOptions;
		};
	}
}