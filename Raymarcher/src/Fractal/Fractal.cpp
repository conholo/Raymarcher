#include "rmpch.h"
#include "Fractal/Fractal.h"
#include "Fractal/IGLSLConvertable.h"

namespace RM
{
	Fractal::Fractal(const std::string& name)
		:m_Name(name)
	{

	}

	Fractal::~Fractal()
	{

	}

	std::string Fractal::Compile()
	{
		std::stringstream ss;
		ss << "float DE_" << m_Name << "(vec4 position)\n{\n";
		ss << "\tvec4 o = position;\n";
		ss << "\tfloat d = 1e20;\n";

		for (auto transformation : m_Transformations)
		{
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

		for (auto transformation : m_Transformations)
		{
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

		return ss.str();
	}

	std::string Fractal::CompileProcedural(uint32_t begin, uint32_t end, uint32_t iterations)
	{
		std::stringstream ss;
		ss << "float DE_" << m_Name << "(vec4 position)\n{\n";
		ss << "\tvec4 o = position;\n";
		ss << "\tfloat d = 1e20;\n";

		for (uint32_t i = 0; i < begin; i++)
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

		for (uint32_t i = 0; i < iterations; i++)
		{
			for (uint32_t j = begin; j <= end; j++)
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

		for (uint32_t i = end; i < m_Transformations.size(); i++)
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

		for (uint32_t i = 0; i < begin; i++)
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

		for (uint32_t i = 0; i < iterations; i++)
		{
			for (uint32_t j = begin; j <= end; j++)
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

		for (uint32_t i = end; i < m_Transformations.size(); i++)
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

		return ss.str();
	}
}