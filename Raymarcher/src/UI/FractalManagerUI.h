#pragma once

#include "Fractal/Fractal.h"
#include "UI/FractalViewerUI.h"

namespace RM
{
	namespace UI
	{
		struct FractalCompileData
		{
			Ref<Fractal> Fractal;
			uint32_t Begin;
			uint32_t End;
			uint32_t Iterations;
		};

		class FractalManagerUI
		{
		public:
			static void LoadFromDisk();
			static void CreateFractal(const std::string& fractalName = "Fractal");
			static void AddFractal(const Ref<Fractal>& fractal);
			static void DeleteFractal();
			static void DrawFractalUI();
			static void RequestReload(const Ref<Fractal>& fractal);

		private:
			static bool s_EditorOpen;
			static std::string s_InputFractalName;
			static std::vector<Ref<FractalViewerUI>> s_Views;
			static Ref<FractalViewerUI> s_ActiveViewer;
		};
	}
}