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

		const Ref<IGLSLConvertable>& operator[](uint32_t index) { return m_Transformations[index]; }

		std::string Compile();

	private:
		std::string m_Name;
		std::vector<Ref<IGLSLConvertable>> m_Transformations;
	};
}