#pragma once

#include "Fractal/IGLSLConvertable.h"
#include <yaml-cpp/yaml.h>

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
		virtual std::string Name() const = 0;
	};

	class ColorModZero : public ColorMod
	{
	public:
		ColorModZero() = default;
		std::string ColorModToGLSL() const override;
		static std::string ToString() { return "ColorModZero"; }
		std::string Name() const override { return ToString(); }

		void Serialize(YAML::Emitter& out) override;
	};

	class ColorModInfinity : public ColorMod
	{
	public:
		ColorModInfinity() = default;
		std::string ColorModToGLSL() const override;
		static std::string ToString() { return "ColorModInfinity"; }
		std::string Name() const override { return ToString(); }

		void Serialize(YAML::Emitter& out) override;
	};

	class ColorModNegativeInfinity : public ColorMod
	{
	public:
		ColorModNegativeInfinity() = default;
		std::string ColorModToGLSL() const override;
		static std::string ToString() { return "ColorModNegativeInfinity"; }
		std::string Name() const override { return ToString(); }

		void Serialize(YAML::Emitter& out) override;
	};

	class ColorModSum : public ColorMod
	{
	public:
		ColorModSum(const glm::vec3& scale = glm::vec3(1.0f), const glm::vec3& origin = glm::vec3(0.0f))
			:m_Scale(scale), m_Origin(origin) { }
		std::string ColorModToGLSL() const override;

		glm::vec3& GetScale() { return m_Scale; }
		glm::vec3& GetOrigin() { return m_Origin; }
		static std::string ToString() { return "ColorModSum"; }
		std::string Name() const override { return ToString(); }

		void Serialize(YAML::Emitter& out) override;

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

		glm::vec3& GetScale() { return m_Scale; }
		glm::vec3& GetOrigin() { return m_Origin; }
		static std::string ToString() { return "ColorModSumAbs"; }
		std::string Name() const override { return ToString(); }

		void Serialize(YAML::Emitter& out) override;

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

		glm::vec3& GetScale() { return m_Scale; }
		glm::vec3& GetOrigin() { return m_Origin; }
		static std::string ToString() { return "ColorModMin"; }
		std::string Name() const override { return ToString(); }

		void Serialize(YAML::Emitter& out) override;

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

		glm::vec3& GetScale() { return m_Scale; }
		glm::vec3& GetOrigin() { return m_Origin; }
		static std::string ToString() { return "ColorModMinAbs"; }
		std::string Name() const override { return ToString(); }

		void Serialize(YAML::Emitter& out) override;

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

		glm::vec3& GetScale() { return m_Scale; }
		glm::vec3& GetOrigin() { return m_Origin; }
		static std::string ToString() { return "ColorModMax"; }
		std::string Name() const override { return ToString(); }

		void Serialize(YAML::Emitter& out) override;

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

		glm::vec3& GetScale() { return m_Scale; }
		glm::vec3& GetOrigin() { return m_Origin; }
		static std::string ToString() { return "ColorModMaxAbs"; }
		std::string Name() const override { return ToString(); }

		void Serialize(YAML::Emitter& out) override;

	private:
		glm::vec3 m_Scale = glm::vec3(1.0f);
		glm::vec3 m_Origin = glm::vec3(0.0f);
	};

}