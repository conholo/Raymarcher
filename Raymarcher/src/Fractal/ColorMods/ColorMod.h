#pragma once

#include "Fractal/IGLSLConvertable.h"

namespace RM
{
	class ColorMod : public IGLSLConvertable
	{
	public:
		ColorMod();
		virtual ~ColorMod() = default;
		std::string TransformationToGLSL() const override { return ""; };
		std::string ColorToGLSL() const override { return ""; };
		virtual std::string ColorModToGLSL() const = 0;
	};

	class ColorModZero : public ColorMod
	{
	public:
		ColorModZero() = default;
		std::string ColorModToGLSL() const override;
	};

	class ColorModInfinity : public ColorMod
	{
	public:
		ColorModInfinity() = default;
		std::string ColorModToGLSL() const override;
	};

	class ColorModNegativeInfinity : public ColorMod
	{
	public:
		ColorModNegativeInfinity() = default;
		std::string ColorModToGLSL() const override;
	};

	class ColorModSum : public ColorMod
	{
	public:
		ColorModSum(const glm::vec3& scale = glm::vec3(1.0f), const glm::vec3& origin = glm::vec3(0.0f))
			:m_Scale(scale), m_Origin(origin) { }
		std::string ColorModToGLSL() const override;

	private:
		glm::vec3 m_Scale = glm::vec3(1.0f);
		glm::vec3 m_Origin = glm::vec3(0.0f);
	};

	class ColorModSumAbs : public ColorMod
	{
	public:
		ColorModSumAbs(const glm::vec3& scale = glm::vec3(1.0f), const glm::vec3& origin = glm::vec3(0.0f))
			:m_Scale(scale), m_Origin(origin) { }
		std::string ColorModToGLSL() const override;

	private:
		glm::vec3 m_Scale = glm::vec3(1.0f);
		glm::vec3 m_Origin = glm::vec3(0.0f);
	};


	class ColorModMin : public ColorMod
	{
	public:
		ColorModMin(const glm::vec3& scale = glm::vec3(1.0f), const glm::vec3& origin = glm::vec3(0.0f))
			:m_Scale(scale), m_Origin(origin) { }
		std::string ColorModToGLSL() const override;

	private:
		glm::vec3 m_Scale = glm::vec3(1.0f);
		glm::vec3 m_Origin = glm::vec3(0.0f);
	};

	class ColorModMinAbs : public ColorMod
	{
	public:
		ColorModMinAbs(const glm::vec3& scale = glm::vec3(1.0f), const glm::vec3& origin = glm::vec3(0.0f))
			:m_Scale(scale), m_Origin(origin) { }
		std::string ColorModToGLSL() const override;

	private:
		glm::vec3 m_Scale = glm::vec3(1.0f);
		glm::vec3 m_Origin = glm::vec3(0.0f);
	};

	class ColorModMax : public ColorMod
	{
	public:
		ColorModMax(const glm::vec3& scale = glm::vec3(1.0f), const glm::vec3& origin = glm::vec3(0.0f))
			:m_Scale(scale), m_Origin(origin) { }
		std::string ColorModToGLSL() const override;

	private:
		glm::vec3 m_Scale = glm::vec3(1.0f);
		glm::vec3 m_Origin = glm::vec3(0.0f);
	};

	class ColorModMaxAbs : public ColorMod
	{
	public:
		ColorModMaxAbs(const glm::vec3& scale = glm::vec3(1.0f), const glm::vec3& origin = glm::vec3(0.0f))
			:m_Scale(scale), m_Origin(origin) { }
		std::string ColorModToGLSL() const override;

	private:
		glm::vec3 m_Scale = glm::vec3(1.0f);
		glm::vec3 m_Origin = glm::vec3(0.0f);
	};

}