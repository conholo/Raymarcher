#pragma once

#include "Fractal/Fractal.h"
#include "UI/FractalViewerUI.h"

namespace RM
{
	namespace UI
	{
		class FractalManagerUI
		{
		public:

			static void CreateFractal(const std::string& fractalName = "Fractal");
			static void AddFractal(const Ref<Fractal>& fractal);
			static void DeleteFractal();

			static void DrawFractalUI();

		private:
			static bool s_EditorOpen;
			static std::string s_InputFractalName;
			static std::vector<Ref<FractalViewerUI>> s_Views;
			static Ref<FractalViewerUI> s_ActiveViewer;
		};
	}
}