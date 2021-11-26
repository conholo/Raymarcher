#pragma once

#include "Fractal/FractalGeometry.h"

namespace RM
{
	class Fractal
	{
	public:
		Fractal(const std::string& name);
		~Fractal();

		const std::vector<Ref<IGLSLConvertable>>& Transformations() const { return m_Transformations; }
		void AddTransformation(const Ref<IGLSLConvertable>& transformation) { m_Transformations.push_back(transformation); }

		void SetTransformations(const std::vector<Ref<IGLSLConvertable>>& transformations) { m_Transformations = transformations; }

		const Ref<IGLSLConvertable>& operator[](uint32_t index) { return m_Transformations[index]; }

		std::string Compile();
		std::string CompileProcedural(uint32_t begin, uint32_t end, uint32_t iterations);
		std::string GetName() const { return m_Name; }

	private:
		std::string m_Name;
		std::vector<Ref<IGLSLConvertable>> m_Transformations;
	};
}