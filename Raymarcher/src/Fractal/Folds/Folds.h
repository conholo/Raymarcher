#pragma once

#include "Fractal/IGLSLConvertable.h"
#include <glm/glm.hpp>

#include <yaml-cpp/yaml.h>

namespace RM
{
	class Fold : public IGLSLConvertable
	{
	public:
		Fold();
		virtual ~Fold() = default;
		virtual std::string TransformationToGLSL() const = 0;
		virtual std::string ColorToGLSL() const override { return ""; }
		virtual std::string Name() const = 0;

		virtual void Serialize(YAML::Emitter& out) = 0;

		std::string ColorModToGLSL() const override { return ""; }
	};

	class FoldScaleTranslate : public Fold
	{
	public:
		FoldScaleTranslate(float scale = 1.0f, const glm::vec3& translation = glm::vec3(0.0f))
			:m_Scale(scale), m_Translation(translation) { }

		std::string TransformationToGLSL() const override;
		static std::string ToString() { return "FoldScaleTranslate"; }
		std::string Name() const override { return ToString(); }

		float& GetScale() { return m_Scale; }
		glm::vec3& GetTranslation() { return m_Translation; }

		void Serialize(YAML::Emitter& out) override;

	private:
		float m_Scale = 1.0f;
		glm::vec3 m_Translation = glm::vec3(0.0f);
	};


	class FoldScaleOrigin : public Fold
	{
	public:
		FoldScaleOrigin(float scale = 1.0f, const glm::vec3& origin = glm::vec3(0.0f))
			:m_Scale(scale), m_Origin(origin)
		{
		}

		std::string TransformationToGLSL() const override;
		static std::string ToString() { return "FoldScaleOrigin"; }
		std::string Name() const override { return ToString(); }

		float& GetScale() { return m_Scale; }
		glm::vec3& GetOrigin() { return m_Origin; }

		void Serialize(YAML::Emitter& out) override;

	private:
		float m_Scale = 1.0f;
		glm::vec3 m_Origin = glm::vec3(0.0f);
	};


	class FoldPlane : public Fold
	{
	public:

		enum class FoldDirection { None, Right, Up, Forward, Left, Down, Back };

		FoldPlane(FoldDirection direction = FoldDirection::None, float factor = 0.0f)
			:m_Direction(direction), m_Factor(factor) { }

		std::string TransformationToGLSL() const override;
		static std::string ToString() { return "FoldPlane"; }
		std::string Name() const override { return ToString(); }

		FoldDirection& GetDirection() { return m_Direction; }
		float& GetFactor() { return m_Factor; }

		void Serialize(YAML::Emitter& out) override;

	private:
		FoldDirection m_Direction = FoldDirection::None;
		float m_Factor = 0.0f;
	};


	class FoldMenger : public Fold
	{
	public:
		FoldMenger() { }
		std::string TransformationToGLSL() const override;
		static std::string ToString() { return "FoldMenger"; }
		std::string Name() const override { return ToString(); }

		void Serialize(YAML::Emitter& out) override;
	};

	class FoldSierpinski : public Fold
	{
	public:
		FoldSierpinski() {}
		std::string TransformationToGLSL() const override;
		static std::string ToString() { return "FoldSierpinski"; }
		std::string Name() const override { return ToString(); }

		void Serialize(YAML::Emitter& out) override;
	};
	
	class FoldBox : public Fold
	{
	public:
		FoldBox(const glm::vec3& range = glm::vec3(1.0f)) 
			:m_Range(range) { }

		std::string TransformationToGLSL() const override;
		static std::string ToString() { return "FoldBox"; }
		std::string Name() const override { return ToString(); }

		glm::vec3& GetRange() { return m_Range; }

		void Serialize(YAML::Emitter& out) override;

	private:
		glm::vec3 m_Range = glm::vec3(1.0f);
	};

	class FoldSphere : public Fold
	{
	public:
		FoldSphere(float minRadius = 0.5f, float maxRadius = 1.0f)
			:m_MinRadius(minRadius), m_MaxRadius(maxRadius) { }

		std::string TransformationToGLSL() const override;
		static std::string ToString() { return "FoldSphere"; }
		std::string Name() const override { return ToString(); }

		float& GetMinRadius() { return m_MinRadius; }
		float& GetMaxRadius() { return m_MaxRadius; }

		void Serialize(YAML::Emitter& out) override;

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
		static std::string ToString() { return "FoldAbs"; }
		std::string Name() const override { return ToString(); }

		glm::vec3& GetCenter() { return m_Center; }

		void Serialize(YAML::Emitter& out) override;

	private:
		glm::vec3 m_Center = glm::vec3(0.0f);
	};

	class FoldInversion : public Fold
	{
	public:
		FoldInversion(float epsilon = 1e-12)
			:m_Epsilon(epsilon) { }

		std::string TransformationToGLSL() const override;
		static std::string ToString() { return "FoldInversion"; }
		std::string Name() const override { return ToString(); }

		float& GetEpsilon() { return m_Epsilon; }

		void Serialize(YAML::Emitter& out) override;

	private:
		float m_Epsilon = 1e-12;
	};

	class FoldRotateX : public Fold
	{
	public:
		FoldRotateX(float angle = 0.0f)
			:m_Radians(glm::radians(angle)) { }

		std::string TransformationToGLSL() const override;
		static std::string ToString() { return "FoldRotateX"; }
		std::string Name() const override { return ToString(); }

		float& GetRadians() { return m_Radians; }

		void Serialize(YAML::Emitter& out) override;

	private:
		float m_Radians = 0.0f;
	};

	class FoldRotateY : public Fold
	{
	public:
		FoldRotateY(float angle = 0.0f)
			:m_Radians(glm::radians(angle)) { }

		std::string TransformationToGLSL() const override;
		static std::string ToString() { return "FoldRotateY"; }
		std::string Name() const override { return ToString(); }

		float& GetRadians() { return m_Radians; }

		void Serialize(YAML::Emitter& out) override;

	private:
		float m_Radians = 0.0f;
	};

	class FoldRotateZ : public Fold
	{
	public:
		FoldRotateZ(float angle = 0.0f)
			:m_Radians(glm::radians(angle)) { }

		std::string TransformationToGLSL() const override;
		static std::string ToString() { return "FoldRotateZ"; }
		std::string Name() const override { return ToString(); }

		float& GetRadians() { return m_Radians; }

		void Serialize(YAML::Emitter& out) override;

	private:
		float m_Radians = 0.0f;
	};

	class FoldRepeatX : public Fold
	{
	public:
		FoldRepeatX(float step = 1.0f)
			:m_Step(step) { }

		std::string TransformationToGLSL() const override;
		static std::string ToString() { return "FoldRepeatX"; }
		std::string Name() const override { return ToString(); }

		float& GetStep() { return m_Step; }

		void Serialize(YAML::Emitter& out) override;

	private:
		float m_Step = 1.0f;
	};

	class FoldRepeatY : public Fold
	{
	public:
		FoldRepeatY(float step = 1.0f)
			:m_Step(step) { }

		std::string TransformationToGLSL() const override;
		static std::string ToString() { return "FoldRepeatY"; }
		std::string Name() const override { return ToString(); }

		float& GetStep() { return m_Step; }

		void Serialize(YAML::Emitter& out) override;

	private:
		float m_Step = 1.0f;
	};

	class FoldRepeatZ : public Fold
	{
	public:
		FoldRepeatZ(float step = 1.0f)
			:m_Step(step) { }

		std::string TransformationToGLSL() const override;
		static std::string ToString() { return "FoldRepeatZ"; }
		std::string Name() const override { return ToString(); }

		float& GetStep() { return m_Step; }

		void Serialize(YAML::Emitter& out) override;

	private:
		float m_Step = 1.0f;
	};

	class FoldRepeatXYZ : public Fold
	{
	public:
		FoldRepeatXYZ(float step = 1.0f)
			:m_Step(step) { }

		std::string TransformationToGLSL() const override;
		static std::string ToString() { return "FoldRepeatXYZ"; }
		std::string Name() const override { return ToString(); }

		float& GetStep() { return m_Step; }

		void Serialize(YAML::Emitter& out) override;

	private:
		float m_Step = 1.0f;
	};
}