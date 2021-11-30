#pragma once

#include "UI/FractalComponentEditorUI.h"
#include "Fractal/Folds/Folds.h"
#include "Fractal/IGLSLConvertable.h"

#include <glm/glm.hpp>

namespace RM
{
	namespace UI
	{
		class FoldUI : public FractalComponentEditorUI
		{
		public:
			FoldUI(const std::string& componentName, uint32_t id)
				:FractalComponentEditorUI(componentName, id) { }
			virtual ~FoldUI() = default;

			virtual Ref<IGLSLConvertable> GetConvertable() = 0;
			virtual void DrawEditor(const std::string& fractalName)  = 0;
		};

		class FoldScaleTranslateUI : public FoldUI
		{
		public:
			FoldScaleTranslateUI(uint32_t id, const Ref<FoldScaleTranslate>& fold)
				:FoldUI(FoldScaleTranslate::ToString(), id), m_Fold(fold) { }

			void DrawEditor(const std::string& fractalName) override;

			Ref<IGLSLConvertable> GetConvertable() override { return CreateRef<FoldScaleTranslate>(m_Fold->GetScale(), m_Fold->GetTranslation()); }

		private:
			Ref<FoldScaleTranslate> m_Fold;
		};

		class FoldScaleOriginUI : public FoldUI
		{
		public:
			FoldScaleOriginUI(uint32_t id, const Ref<FoldScaleOrigin>& fold)
				:FoldUI(FoldScaleOrigin::ToString(), id), m_Fold(fold)
			{
			}

			void DrawEditor(const std::string& fractalName) override;

			Ref<IGLSLConvertable> GetConvertable() override { return CreateRef<FoldScaleOrigin>(m_Fold->GetScale(), m_Fold->GetOrigin()); }

		private:
			Ref<FoldScaleOrigin> m_Fold;
		};


		class FoldPlaneUI : public FoldUI
		{
		public:
			FoldPlaneUI(uint32_t id, const Ref<FoldPlane>& fold)
				:FoldUI(FoldPlane::ToString(), id), m_Fold(fold) { }

			void SetSelectedFoldDirection(int direction) { m_SelectedFoldDirection = direction; }
			void DrawEditor(const std::string& fractalName) override;

			Ref<IGLSLConvertable> GetConvertable() override { return CreateRef<FoldPlane>(m_Fold->GetDirection(), m_Fold->GetFactor()); }

		private:
			int m_SelectedFoldDirection = 0;
			Ref<FoldPlane> m_Fold;
		};

		class FoldMengerUI : public FoldUI
		{
		public:
			FoldMengerUI(uint32_t id, const Ref<FoldMenger>& fold)
				:FoldUI(FoldMenger::ToString(), id), m_Fold(fold) { }

			void DrawEditor(const std::string& fractalName) override;

			Ref<IGLSLConvertable> GetConvertable() override { return CreateRef<FoldMenger>(); }

		private:
			Ref<FoldMenger> m_Fold;
		};

		class FoldSierpinskiUI : public FoldUI
		{
		public:
			FoldSierpinskiUI(uint32_t id, const Ref<FoldSierpinski>& fold)
				:FoldUI(FoldSierpinski::ToString(), id), m_Fold(fold) {}

			void DrawEditor(const std::string& fractalName) override;

			Ref<IGLSLConvertable> GetConvertable() override { return CreateRef<FoldSierpinski>(); }

		private:
			Ref<FoldSierpinski> m_Fold;
		};

		class FoldBoxUI : public FoldUI
		{
		public:
			FoldBoxUI(uint32_t id, const Ref<FoldBox>& fold)
				:FoldUI(FoldBox::ToString(), id), m_Fold(fold) { }

			void DrawEditor(const std::string& fractalName) override;

			Ref<IGLSLConvertable> GetConvertable() override { return CreateRef<FoldBox>(m_Fold->GetRange()); }

		private:
			Ref<FoldBox> m_Fold;
		};

		class FoldSphereUI : public FoldUI
		{
		public:
			FoldSphereUI(uint32_t id, const Ref<FoldSphere>& fold)
				:FoldUI(FoldSphere::ToString(), id), m_Fold(fold) { }

			void DrawEditor(const std::string& fractalName) override;

			Ref<IGLSLConvertable> GetConvertable() override { return CreateRef<FoldSphere>(m_Fold->GetMinRadius(), m_Fold->GetMaxRadius()); }

		private:
			Ref<FoldSphere> m_Fold;
		};

		class FoldAbsUI : public FoldUI
		{
		public:
			FoldAbsUI(uint32_t id, const Ref<FoldAbs>& fold)
				:FoldUI(FoldAbs::ToString(), id), m_Fold(fold) { }

			void DrawEditor(const std::string& fractalName) override;

			Ref<IGLSLConvertable> GetConvertable() override { return CreateRef<FoldAbs>(m_Fold->GetCenter()); }

		private:
			Ref<FoldAbs> m_Fold;
		};

		class FoldInversionUI : public FoldUI
		{
		public:
			FoldInversionUI(uint32_t id, const Ref<FoldInversion>& fold)
				:FoldUI(FoldInversion::ToString(), id), m_Fold(fold) { }

			void DrawEditor(const std::string& fractalName) override;

			Ref<IGLSLConvertable> GetConvertable() override { return CreateRef<FoldInversion>(m_Fold->GetEpsilon()); }

		private:
			Ref<FoldInversion> m_Fold;
		};

		class FoldRotateXUI : public FoldUI
		{
		public:
			FoldRotateXUI(uint32_t id, const Ref<FoldRotateX>& fold)
				:FoldUI(FoldRotateX::ToString(), id), m_Fold(fold) { }

			void DrawEditor(const std::string& fractalName) override;

			Ref<IGLSLConvertable> GetConvertable() override { return CreateRef<FoldRotateX>(glm::degrees(m_Fold->GetRadians())); }

		private:
			Ref<FoldRotateX> m_Fold;
		};

		class FoldRotateYUI : public FoldUI
		{
		public:
			FoldRotateYUI(uint32_t id, const Ref<FoldRotateY>& fold)
				:FoldUI(FoldRotateY::ToString(), id), m_Fold(fold) { }

			void DrawEditor(const std::string& fractalName) override;

			Ref<IGLSLConvertable> GetConvertable() override { return CreateRef<FoldRotateY>(glm::degrees(m_Fold->GetRadians())); }

		private:
			Ref<FoldRotateY> m_Fold;
		};

		class FoldRotateZUI : public FoldUI
		{
		public:
			FoldRotateZUI(uint32_t id, const Ref<FoldRotateZ>& fold)
				:FoldUI(FoldRotateZ::ToString(), id), m_Fold(fold) { }

			void DrawEditor(const std::string& fractalName) override;

			Ref<IGLSLConvertable> GetConvertable() override { return CreateRef<FoldRotateZ>(glm::degrees(m_Fold->GetRadians())); }

		private:
			Ref<FoldRotateZ> m_Fold;
		};

		class FoldRepeatXUI : public FoldUI
		{
		public:
			FoldRepeatXUI(uint32_t id, const Ref<FoldRepeatX>& fold)
				:FoldUI(FoldRepeatX::ToString(), id), m_Fold(fold) { }

			void DrawEditor(const std::string& fractalName) override;

			Ref<IGLSLConvertable> GetConvertable() override { return CreateRef<FoldRepeatX>(m_Fold->GetStep()); }

		private:
			Ref<FoldRepeatX> m_Fold;
		};
		
		class FoldRepeatYUI : public FoldUI
		{
		public:
			FoldRepeatYUI(uint32_t id, const Ref<FoldRepeatY>& fold)
				:FoldUI(FoldRepeatY::ToString(), id), m_Fold(fold) { }

			void DrawEditor(const std::string& fractalName) override;

			Ref<IGLSLConvertable> GetConvertable() override { return CreateRef<FoldRepeatY>(m_Fold->GetStep()); }

		private:
			Ref<FoldRepeatY> m_Fold;
		};

		class FoldRepeatZUI : public FoldUI
		{
		public:
			FoldRepeatZUI(uint32_t id, const Ref<FoldRepeatZ>& fold)
				:FoldUI(FoldRepeatZ::ToString(), id), m_Fold(fold) { }

			void DrawEditor(const std::string& fractalName) override;

			Ref<IGLSLConvertable> GetConvertable() override { return CreateRef<FoldRepeatZ>(m_Fold->GetStep()); }

		private:
			Ref<FoldRepeatZ> m_Fold;
		};

		class FoldRepeatXYZUI : public FoldUI
		{
		public:
			FoldRepeatXYZUI(uint32_t id, const Ref<FoldRepeatXYZ>& fold)
				:FoldUI(FoldRepeatXYZ::ToString(), id), m_Fold(fold) { }

			void DrawEditor(const std::string& fractalName) override;

			Ref<IGLSLConvertable> GetConvertable() override { return CreateRef<FoldRepeatXYZ>(m_Fold->GetStep()); }

		private:
			Ref<FoldRepeatXYZ> m_Fold;
		};
	}
}