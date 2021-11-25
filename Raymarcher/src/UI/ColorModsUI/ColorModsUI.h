#pragma once

#include "UI/FractalComponentEditorUI.h"
#include "Fractal/ColorMods/ColorMod.h"

#include <glm/glm.hpp>s

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
			std::unordered_map<std::string, float*> GetVector3Fields() { return m_Vector3Fields; }
			bool IsInitializer() const { return  m_Vector3Fields.size() <= 0; }
			virtual void DrawEditor(const std::string& fractalName) = 0;

		protected:
			std::unordered_map<std::string, float*> m_Vector3Fields;
		};

		class ColorModZeroUI : public ColorModUI
		{
		public:
			ColorModZeroUI(uint32_t id)
				:ColorModUI(ColorModZero::ToString(), id) {}
			void DrawEditor(const std::string& fractalName) override {}
		};

		class ColorModInfinityUI : public ColorModUI
		{
		public:
			ColorModInfinityUI(uint32_t id)
				:ColorModUI(ColorModInfinity::ToString(), id) { }
			void DrawEditor(const std::string& fractalName) override {}
		};

		class ColorModNegativeInfinityUI : public ColorModUI
		{
		public:
			ColorModNegativeInfinityUI(uint32_t id)
				:ColorModUI(ColorModNegativeInfinity::ToString(), id) { }
			void DrawEditor(const std::string& fractalName) override {}
		};

		class ColorModSumUI : public ColorModUI
		{
		public:
			ColorModSumUI(uint32_t id, const Ref<ColorModSum>& colorModSum)
				:ColorModUI(ColorModSum::ToString(), id), m_ColorModSum(colorModSum)
			{
				m_Vector3Fields["Scale"] = &m_ColorModSum->GetScale().x;
				m_Vector3Fields["Origin"] = &m_ColorModSum->GetOrigin().x;
			}

			void DrawEditor(const std::string& fractalName) override;

		private:
			Ref<ColorModSum> m_ColorModSum;
		};

		class ColorModSumAbsUI : public ColorModUI
		{
		public:
			ColorModSumAbsUI(uint32_t id, const Ref<ColorModSumAbs> colorModSumAbs)
				:ColorModUI(ColorModSumAbs::ToString(), id), m_ColorModSumAbs(colorModSumAbs)
			{
				m_Vector3Fields["Scale"] = &m_ColorModSumAbs->GetScale().x;
				m_Vector3Fields["Origin"] = &m_ColorModSumAbs->GetOrigin().x;
			}

			void DrawEditor(const std::string& fractalName) override;

		private:
			Ref<ColorModSumAbs> m_ColorModSumAbs;
		};


		class ColorModMinUI : public ColorModUI
		{
		public:
			ColorModMinUI(uint32_t id, const Ref<ColorModMin>& colorModMin)
				:ColorModUI(ColorModMin::ToString(), id), m_ColorModMin(colorModMin)
			{
				m_Vector3Fields["Scale"] = &m_ColorModMin->GetScale().x;
				m_Vector3Fields["Origin"] = &m_ColorModMin->GetOrigin().x;
			}

			void DrawEditor(const std::string& fractalName) override;

		private:
			Ref<ColorModMin> m_ColorModMin;
		};

		class ColorModMinAbsUI : public ColorModUI
		{
		public:
			ColorModMinAbsUI(uint32_t id, const Ref<ColorModMinAbs>& colorModMinAbs)
				:ColorModUI(ColorModMinAbs::ToString(), id), m_ColorModMinAbs(colorModMinAbs)
			{
				m_Vector3Fields["Scale"] = &m_ColorModMinAbs->GetScale().x;
				m_Vector3Fields["Origin"] = &m_ColorModMinAbs->GetOrigin().x;
			}

			void DrawEditor(const std::string& fractalName) override;

		private:
			Ref<ColorModMinAbs> m_ColorModMinAbs;
		};

		class ColorModMaxUI : public ColorModUI
		{
		public:
			ColorModMaxUI(uint32_t id, const Ref<ColorModMax>& colorModMax)
				:ColorModUI(ColorModMax::ToString(), id), m_ColorModMax(colorModMax)
			{
				m_Vector3Fields["Scale"] = &m_ColorModMax->GetScale().x;
				m_Vector3Fields["Origin"] = &m_ColorModMax->GetOrigin().x;
			}

			void DrawEditor(const std::string& fractalName) override;

		private:
			Ref<ColorModMax> m_ColorModMax;
		};

		class ColorModMaxAbsUI : public ColorModUI
		{
		public:
			ColorModMaxAbsUI(uint32_t id, const Ref<ColorModMaxAbs>& colorModMaxAbs)
				:ColorModUI(ColorModMaxAbs::ToString(), id), m_ColorModMaxAbs(colorModMaxAbs)
			{
				m_Vector3Fields["Scale"] = &m_ColorModMaxAbs->GetScale().x;
				m_Vector3Fields["Origin"] = &m_ColorModMaxAbs->GetOrigin().x;
			}

			void DrawEditor(const std::string& fractalName) override;

		private:
			Ref<ColorModMaxAbs> m_ColorModMaxAbs;
		};
	}
}