#pragma once

#include "Fractal/FractalGeometry.h"
#include "Fractal/FractalDefines.h"

namespace RM
{
	struct CompiledFractalSrc
	{
		std::string DefineSrc;
		std::string ProceduralSrc;
	};

	class Fractal
	{
	public:
		Fractal() = default;
		Fractal(const std::string& name);
		~Fractal();

		const std::vector<Ref<IGLSLConvertable>>& Transformations() const { return m_Transformations; }
		void AddTransformation(const Ref<IGLSLConvertable>& transformation) { m_Transformations.push_back(transformation); }

		void SetTransformations(const std::vector<Ref<IGLSLConvertable>>& transformations) { m_Transformations = transformations; }

		const Ref<IGLSLConvertable>& operator[](uint32_t index) { return m_Transformations[index]; }

		void Save();
		void Load(const FractalDefines& defines, const std::vector<Ref<IGLSLConvertable>> transformations);

		CompiledFractalSrc Compile();
		CompiledFractalSrc CompileProcedural();
		std::string GetName() const { return m_Name; }

		void SetBegin(uint32_t begin) { m_Begin = begin; }
		void SetEnd(uint32_t end) { m_End = end; }
		void SetIterations(uint32_t iterations) { m_Iterations = iterations; }

		uint32_t GetBegin() const { return m_Begin; }
		uint32_t GetEnd() const { return m_End; }
		uint32_t GetIterations() const { return m_Iterations; }

		FractalDefines& GetDefines() { return m_Defines; }
	private:
		uint32_t m_Begin = 0;
		uint32_t m_End = 0;
		uint32_t m_Iterations = 0;

		FractalDefines m_Defines;
		std::string m_Name;
		std::vector<Ref<IGLSLConvertable>> m_Transformations;
	};
}