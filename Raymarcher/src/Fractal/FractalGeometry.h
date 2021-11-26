#pragma once
#include "Fractal/IGLSLConvertable.h"
#include <glm/glm.hpp>

namespace RM
{
	class FractalGeometry : public IGLSLConvertable
	{
	public:
		FractalGeometry(ColorType colorType = ColorType::ColorMod, const glm::vec3& color = glm::vec3(1.0f));
		virtual ~FractalGeometry() = default;

		virtual std::string TransformationToGLSL() const = 0;
		virtual std::string ColorToGLSL() const = 0;
		std::string ColorModToGLSL() const override { return ""; }
	};

	class Box : public FractalGeometry
	{
	public:
		Box(ColorType colorType = ColorType::ColorMod,
			const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f), 
			const glm::vec3& offset = glm::vec3(0.0f, 0.0f, 0.0f), 
			const glm::vec3& color = glm::vec3(1.0f, 1.0f, 1.0f));

		std::string TransformationToGLSL() const override;
		std::string ColorToGLSL() const override;

		glm::vec3& GetScale() { return m_Scale; }
		glm::vec3& GetOffset() { return m_Offset; }

		static std::string ToString() { return "Box"; }

	private:
		glm::vec3 m_Scale = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec3 m_Offset = glm::vec3(0.0f, 0.0f, 0.0f);
	};

	class Sphere : public FractalGeometry
	{
	public:
		Sphere(ColorType colorType = ColorType::ColorMod,
			float radius = 1.0f,
			const glm::vec3& center = glm::vec3(0.0f, 0.0f, 0.0f),
			const glm::vec3& color = glm::vec3(1.0f, 1.0f, 1.0f));

		std::string TransformationToGLSL() const override;
		std::string ColorToGLSL() const override;

		glm::vec3& GetCenter() { return m_Center; }
		float& GetRadius() { return m_Radius; }

		static std::string ToString() { return "Sphere"; }

	private:
		float m_Radius = 1.0f;
		glm::vec3 m_Center = glm::vec3(0.0f, 0.0f, 0.0f);
	};

	class Tetrahedron : public FractalGeometry
	{
	public:
		Tetrahedron(ColorType colorType = ColorType::ColorMod,
			float radius = 1.0f,
			const glm::vec3& center = glm::vec3(0.0f, 0.0f, 0.0f),
			const glm::vec3& color = glm::vec3(1.0f, 1.0f, 1.0f));

		std::string TransformationToGLSL() const override;
		std::string ColorToGLSL() const override;

		glm::vec3& GetCenter() { return m_Center; }
		float& GetRadius() { return m_Radius; }

		static std::string ToString() { return "Tetrahedron"; }

	private:
		float m_Radius = 1.0f;
		glm::vec3 m_Center = glm::vec3(0.0f, 0.0f, 0.0f);
	};

}