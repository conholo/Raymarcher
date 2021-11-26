#pragma once

#include "UI/FractalComponentEditorUI.h"
#include "Fractal/FractalGeometry.h"

namespace RM
{
	namespace UI
	{
		class FractalGeometryUI : public FractalComponentEditorUI
		{
		public:
			FractalGeometryUI(const std::string& componentName, uint32_t id)
				:FractalComponentEditorUI(componentName, id) { }
			virtual ~FractalGeometryUI() = default;
			virtual void DrawEditor(const std::string& fractalName) = 0;
			virtual Ref<IGLSLConvertable> GetConvertable() = 0;
		};

		class FractalGeometryBoxUI : public FractalGeometryUI
		{
		public:
			FractalGeometryBoxUI(uint32_t id, const Ref<Box>& box)
				:FractalGeometryUI(Box::ToString(), id), m_Box(box) { }
			virtual ~FractalGeometryBoxUI() = default;
			virtual void DrawEditor(const std::string& fractalName);

			Ref<IGLSLConvertable> GetConvertable() override { return CreateRef<Box>(m_Box->GetColorType(), m_Box->GetScale(), m_Box->GetOffset(), m_Box->GetColor()); }

		private:
			uint32_t m_SelectedColorOption = 0;
			Ref<Box> m_Box;
		};

		class FractalGeometrySphereUI : public FractalGeometryUI
		{
		public:
			FractalGeometrySphereUI(uint32_t id, const Ref<Sphere>& sphere)
				:FractalGeometryUI(Sphere::ToString(), id), m_Sphere(sphere) { }
			virtual ~FractalGeometrySphereUI() = default;
			virtual void DrawEditor(const std::string& fractalName);

			Ref<IGLSLConvertable> GetConvertable() override { return CreateRef<Sphere>(m_Sphere->GetColorType(), m_Sphere->GetRadius(), m_Sphere->GetCenter(), m_Sphere->GetColor()); }

		private:
			uint32_t m_SelectedColorOption = 0;
			Ref<Sphere> m_Sphere;
		};

		class FractalGeometryTetrahedronUI : public FractalGeometryUI
		{
		public:
			FractalGeometryTetrahedronUI(uint32_t id, const Ref<Tetrahedron>& tetrahedron)
				:FractalGeometryUI(Tetrahedron::ToString(), id), m_Tetrahedron(tetrahedron) { }
			virtual ~FractalGeometryTetrahedronUI() = default;
			virtual void DrawEditor(const std::string& fractalName);

			Ref<IGLSLConvertable> GetConvertable() override { return CreateRef<Tetrahedron>(m_Tetrahedron->GetColorType(), m_Tetrahedron->GetRadius(), m_Tetrahedron->GetCenter(), m_Tetrahedron->GetColor()); }

		private:
			uint32_t m_SelectedColorOption = 0;
			Ref<Tetrahedron> m_Tetrahedron;
		};
	}
}