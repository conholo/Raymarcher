#pragma once

#include "Fractal/IGLSLConvertable.h"
#include <glm/glm.hpp>

namespace RM
{
	class Fold : public IGLSLConvertable
	{
	public:
		Fold();
		virtual ~Fold() = default;
		virtual std::string TransformationToGLSL() const = 0;
		virtual std::string ColorToGLSL() const override { return ""; }
		std::string ColorModToGLSL() const override { return ""; }
	};

	class FoldScaleTranslate : public Fold
	{
	public:
		FoldScaleTranslate(float scale = 1.0f, const glm::vec3& translation = glm::vec3(0.0f))
			:m_Scale(scale), m_Translation(translation) { }

		std::string TransformationToGLSL() const override;

	private:
		float m_Scale = 1.0f;
		glm::vec3 m_Translation = glm::vec3(0.0f);
	};

	class FoldPlane : public Fold
	{
	public:

		enum class FoldDirection { None, Right, Up, Forward, Left, Down, Back };

		FoldPlane(FoldDirection direction, float factor)
			:m_Direction(direction), m_Factor(factor) { }

		std::string TransformationToGLSL() const override;

	private:
		FoldDirection m_Direction = FoldDirection::None;
		float m_Factor = 0.0f;
	};


	class FoldMenger : public Fold
	{
	public:
		FoldMenger() { }
		std::string TransformationToGLSL() const override;
	};

	class FoldSierpinski : public Fold
	{
	public:
		FoldSierpinski() {}
		std::string TransformationToGLSL() const override;
	};
	
	class FoldBox : public Fold
	{
	public:
		FoldBox(const glm::vec3& range = glm::vec3(1.0f)) 
			:m_Range(range) { }

		std::string TransformationToGLSL() const override;

	private:
		glm::vec3 m_Range = glm::vec3(1.0f);
	};

	class FoldSphere : public Fold
	{
	public:
		FoldSphere(float minRadius = 0.5f, float maxRadius = 1.0f)
			:m_MinRadius(minRadius), m_MaxRadius(maxRadius) { }

		std::string TransformationToGLSL() const override;

	private:
		float m_MinRadius = 0.5f;
		float m_MaxRadius = 1.0f;
	};

	class FoldAbs : public Fold
	{
	public:
		FoldAbs(const glm::vec3& center = glm::vec3(0.0f))
			:m_Center(center) { }

		std::string TransformationToGLSL() const override;

	private:
		glm::vec3 m_Center = glm::vec3(0.0f);
	};

	class FoldInversion : public Fold
	{
	public:
		FoldInversion(float epsilon = 1e-12)
			:m_Epsilon(epsilon) { }

		std::string TransformationToGLSL() const override;

	private:
		float m_Epsilon = 1e-12;
	};

	class FoldRotateX : public Fold
	{
	public:
		FoldRotateX(float angle)
			:m_Radians(glm::radians(angle)) { }

		std::string TransformationToGLSL() const override;

	private:
		float m_Radians = 0.0f;
	};

	class FoldRotateY : public Fold
	{
	public:
		FoldRotateY(float angle)
			:m_Radians(glm::radians(angle)) { }

		std::string TransformationToGLSL() const override;

	private:
		float m_Radians = 0.0f;
	};

	class FoldRotateZ : public Fold
	{
	public:
		FoldRotateZ(float angle)
			:m_Radians(glm::radians(angle)) { }

		std::string TransformationToGLSL() const override;

	private:
		float m_Radians = 0.0f;
	};

	class FoldRepeatX : public Fold
	{
	public:
		FoldRepeatX(float step = 1.0f)
			:m_Step(step) { }

		std::string TransformationToGLSL() const override;

	private:
		float m_Step = 1.0f;
	};

	class FoldRepeatY : public Fold
	{
	public:
		FoldRepeatY(float step = 1.0f)
			:m_Step(step) { }

		std::string TransformationToGLSL() const override;

	private:
		float m_Step = 1.0f;
	};

	class FoldRepeatZ : public Fold
	{
	public:
		FoldRepeatZ(float step = 1.0f)
			:m_Step(step) { }

		std::string TransformationToGLSL() const override;

	private:
		float m_Step = 1.0f;
	};

	class FoldRepeatXYZ : public Fold
	{
	public:
		FoldRepeatXYZ(float step = 1.0f)
			:m_Step(step) { }

		std::string TransformationToGLSL() const override;

	private:
		float m_Step = 1.0f;
	};
}