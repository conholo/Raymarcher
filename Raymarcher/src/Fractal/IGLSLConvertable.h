#pragma once
#include <string>
#include <glm/glm.hpp>

namespace RM
{
	enum class ColorType { None = 0, ColorMod, FromVec3Color};
	enum class AttributeType { None = 0, Geometry, ColorMod, Fold };

	class IGLSLConvertable
	{
	public:
		IGLSLConvertable() { }
		IGLSLConvertable(ColorType colorType, AttributeType attributeType, const glm::vec3& color = glm::vec3(1.0f, 1.0f, 1.0f))
			:m_ColorType(colorType), m_AttributeType(attributeType), m_Color(color) { }
		virtual ~IGLSLConvertable() = default;

		virtual std::string TransformationToGLSL() const = 0;
		virtual std::string ColorToGLSL() const = 0;
		virtual std::string ColorModToGLSL() const = 0;

		ColorType& GetColorType() { return m_ColorType; }
		glm::vec3& GetColor() { return m_Color; }

		ColorType GetColorType() const { return m_ColorType; }
		AttributeType GetAttributeType() const { return m_AttributeType; }
		const glm::vec3& GetColor() const { return m_Color; }

	protected:
		ColorType m_ColorType = ColorType::ColorMod;
		AttributeType m_AttributeType = AttributeType::None;
		glm::vec3 m_Color = glm::vec3(1.0f);
	};
}