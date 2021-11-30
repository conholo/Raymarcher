#include "rmpch.h"
#include "Fractal/Fractal.h"
#include "Fractal/IGLSLConvertable.h"

namespace RM
{
	Fractal::Fractal(const std::string& name)
		:m_Name(name), m_Defines(name)
	{
	}

	Fractal::~Fractal()
	{

	}

	void Fractal::Save()
	{

	}

	void Fractal::Load(const FractalDefines& defines, const std::vector<Ref<IGLSLConvertable>> transformations)
	{

	}

	CompiledFractalSrc Fractal::CompileProcedural()
	{
		std::stringstream ss;
		ss << "float DE_" << m_Name << "(vec4 position)\n{\n";
		ss << "\tvec4 o = position;\n";
		ss << "\tfloat d = 1e20;\n";

		for (uint32_t i = 0; i < m_Begin; i++)
		{
			Ref<IGLSLConvertable> transformation = m_Transformations[i];

			switch (transformation->GetAttributeType())
			{
			case AttributeType::Geometry:
			{
				ss << "\td = min(d, " << transformation->TransformationToGLSL() + ");\n";
				break;
			}
			case AttributeType::Fold:
			{
				ss << transformation->TransformationToGLSL();
				break;
			}
			case AttributeType::None:
			case AttributeType::ColorMod: { break; }
			}
		}

		for (uint32_t i = 0; i < m_Iterations; i++)
		{
			for (uint32_t j = m_Begin; j <= m_End; j++)
			{
				Ref<IGLSLConvertable> transformation = m_Transformations[j];

				switch (transformation->GetAttributeType())
				{
				case AttributeType::Geometry:
				{
					ss << "\td = min(d, " << transformation->TransformationToGLSL() + ");\n";
					break;
				}
				case AttributeType::Fold:
				{
					ss << transformation->TransformationToGLSL();
					break;
				}
				case AttributeType::None:
				case AttributeType::ColorMod: { break; }
				}

			}
		}

		for (uint32_t i = m_End; i < m_Transformations.size(); i++)
		{
			Ref<IGLSLConvertable> transformation = m_Transformations[i];

			switch (transformation->GetAttributeType())
			{
			case AttributeType::Geometry:
			{
				ss << "\td = min(d, " << transformation->TransformationToGLSL() + ");\n";
				break;
			}
			case AttributeType::Fold:
			{
				ss << transformation->TransformationToGLSL();
				break;
			}
			case AttributeType::None:
			case AttributeType::ColorMod: { break; }
			}
		}

		ss << "\treturn d;\n";
		ss << "}\n";

		ss << "vec4 CE_" << m_Name << "(vec4 position)\n{\n";
		ss << "\tvec4 o = position;\n";
		ss << "\tvec4 color = vec4(1e20);\n";
		ss << "\tvec4 newColor;\n";

		for (uint32_t i = 0; i < m_Begin; i++)
		{
			Ref<IGLSLConvertable> transformation = m_Transformations[i];

			switch (transformation->GetAttributeType())
			{
			case AttributeType::Geometry:
			{
				ss << "\tnewColor = " << transformation->ColorToGLSL() << ";\n";
				ss << "\tif (newColor.w < color.w) { color = newColor; }\n";
				break;
			}
			case AttributeType::Fold:
			{
				ss << transformation->TransformationToGLSL();
				break;
			}
			case AttributeType::ColorMod:
			{
				ss << transformation->ColorModToGLSL();
				break;
			}
			case AttributeType::None: break;
			}
		}

		for (uint32_t i = 0; i < m_Iterations; i++)
		{
			for (uint32_t j = m_Begin; j <= m_End; j++)
			{
				Ref<IGLSLConvertable> transformation = m_Transformations[j];

				switch (transformation->GetAttributeType())
				{
				case AttributeType::Geometry:
				{
					ss << "\tnewColor = " << transformation->ColorToGLSL() << ";\n";
					ss << "\tif (newColor.w < color.w) { color = newColor; }\n";
					break;
				}
				case AttributeType::Fold:
				{
					ss << transformation->TransformationToGLSL();
					break;
				}
				case AttributeType::ColorMod:
				{
					ss << transformation->ColorModToGLSL();
					break;
				}
				case AttributeType::None: break;
				}
			}
		}

		for (uint32_t i = m_End; i < m_Transformations.size(); i++)
		{
			Ref<IGLSLConvertable> transformation = m_Transformations[i];

			switch (transformation->GetAttributeType())
			{
			case AttributeType::Geometry:
			{
				ss << "\tnewColor = " << transformation->ColorToGLSL() << ";\n";
				ss << "\tif (newColor.w < color.w) { color = newColor; }\n";
				break;
			}
			case AttributeType::Fold:
			{
				ss << transformation->TransformationToGLSL();
				break;
			}
			case AttributeType::ColorMod:
			{
				ss << transformation->ColorModToGLSL();
				break;
			}
			case AttributeType::None: break;
			}
		}

		ss << "\treturn color;\n";
		ss << "}";

		m_Begin = m_Begin;
		m_End = m_End;
		m_Iterations = m_Iterations;

		return { m_Defines.Compile(), ss.str() };
	}
}