#pragma once

#include "UI/FractalComponentEditorUI.h"
#include "Fractal/ColorMods/ColorMod.h"
#include "Fractal/IGLSLConvertable.h"

#include <glm/glm.hpp>

namespace RM
{
	namespace UI
	{
		class ColorModUI : public FractalComponentEditorUI
		{
		public:
			ColorModUI(const std::string& componentName, uint32_t id)
				:FractalComponentEditorUI(componentName, id) { }
			virtual ~ColorModUI() = default;

			virtual Ref<IGLSLConvertable> GetConvertable() = 0;
			virtual void DrawEditor(const std::string& fractalName) = 0;
		};

		class ColorModZeroUI : public ColorModUI
		{
		public:
			ColorModZeroUI(uint32_t id, const Ref<ColorModZero>& colorModZero)
				:ColorModUI(ColorModZero::ToString(), id), m_ColorModZero(colorModZero) {}

			Ref<IGLSLConvertable> GetConvertable() override { return CreateRef<ColorModZero>(); }

			void DrawEditor(const std::string& fractalName) override {}

		private:
			Ref<ColorModZero> m_ColorModZero;
		};

		class ColorModInfinityUI : public ColorModUI
		{
		public:
			ColorModInfinityUI(uint32_t id, const Ref<ColorModInfinity>& colorModInfinity)
				:ColorModUI(ColorModInfinity::ToString(), id), m_ColorModInfinity(colorModInfinity) { }

			Ref<IGLSLConvertable> GetConvertable() override { return CreateRef<ColorModInfinity>(); }

			void DrawEditor(const std::string& fractalName) override {}

		private:
			Ref<ColorModInfinity> m_ColorModInfinity;
		};

		class ColorModNegativeInfinityUI : public ColorModUI
		{
		public:
			ColorModNegativeInfinityUI(uint32_t id, const Ref<ColorModNegativeInfinity>& negativeInfinity)
				:ColorModUI(ColorModNegativeInfinity::ToString(), id), m_ColorModNegativeInfinity(negativeInfinity) { }

			Ref<IGLSLConvertable> GetConvertable() override { return CreateRef<ColorModNegativeInfinity>(); }

			void DrawEditor(const std::string& fractalName) override {}

		private:
			Ref<ColorModNegativeInfinity> m_ColorModNegativeInfinity;
		};

		class ColorModSumUI : public ColorModUI
		{
		public:
			ColorModSumUI(uint32_t id, const Ref<ColorModSum>& colorModSum)
				:ColorModUI(ColorModSum::ToString(), id), m_ColorModSum(colorModSum) { }

			Ref<IGLSLConvertable> GetConvertable() override { return CreateRef<ColorModSum>(m_ColorModSum->GetScale(), m_ColorModSum->GetOrigin()); }

			void DrawEditor(const std::string& fractalName) override;

		private:
			Ref<ColorModSum> m_ColorModSum;
		};

		class ColorModSumAbsUI : public ColorModUI
		{
		public:
			ColorModSumAbsUI(uint32_t id, const Ref<ColorModSumAbs> colorModSumAbs)
				:ColorModUI(ColorModSumAbs::ToString(), id), m_ColorModSumAbs(colorModSumAbs) { }

			Ref<IGLSLConvertable> GetConvertable() override { return CreateRef<ColorModSumAbs>(m_ColorModSumAbs->GetScale(), m_ColorModSumAbs->GetOrigin()); }

			void DrawEditor(const std::string& fractalName) override;

		private:
			Ref<ColorModSumAbs> m_ColorModSumAbs;
		};


		class ColorModMinUI : public ColorModUI
		{
		public:
			ColorModMinUI(uint32_t id, const Ref<ColorModMin>& colorModMin)
				:ColorModUI(ColorModMin::ToString(), id), m_ColorModMin(colorModMin) { }

			Ref<IGLSLConvertable> GetConvertable() override { return CreateRef<ColorModMin>(m_ColorModMin->GetScale(), m_ColorModMin->GetOrigin()); }

			void DrawEditor(const std::string& fractalName) override;

		private:
			Ref<ColorModMin> m_ColorModMin;
		};

		class ColorModMinAbsUI : public ColorModUI
		{
		public:
			ColorModMinAbsUI(uint32_t id, const Ref<ColorModMinAbs>& colorModMinAbs)
				:ColorModUI(ColorModMinAbs::ToString(), id), m_ColorModMinAbs(colorModMinAbs) { }

			Ref<IGLSLConvertable> GetConvertable() override { return CreateRef<ColorModMinAbs>(m_ColorModMinAbs->GetScale(), m_ColorModMinAbs->GetOrigin());; }

			void DrawEditor(const std::string& fractalName) override;

		private:
			Ref<ColorModMinAbs> m_ColorModMinAbs;
		};

		class ColorModMaxUI : public ColorModUI
		{
		public:
			ColorModMaxUI(uint32_t id, const Ref<ColorModMax>& colorModMax)
				:ColorModUI(ColorModMax::ToString(), id), m_ColorModMax(colorModMax) { }

			Ref<IGLSLConvertable> GetConvertable() override { return CreateRef<ColorModMax>(m_ColorModMax->GetScale(), m_ColorModMax->GetOrigin());; }

			void DrawEditor(const std::string& fractalName) override;

		private:
			Ref<ColorModMax> m_ColorModMax;
		};

		class ColorModMaxAbsUI : public ColorModUI
		{
		public:
			ColorModMaxAbsUI(uint32_t id, const Ref<ColorModMaxAbs>& colorModMaxAbs)
				:ColorModUI(ColorModMaxAbs::ToString(), id), m_ColorModMaxAbs(colorModMaxAbs) { }

			Ref<IGLSLConvertable> GetConvertable() override { return CreateRef<ColorModMaxAbs>(m_ColorModMaxAbs->GetScale(), m_ColorModMaxAbs->GetOrigin());; }

			void DrawEditor(const std::string& fractalName) override;

		private:
			Ref<ColorModMaxAbs> m_ColorModMaxAbs;
		};
	}
}