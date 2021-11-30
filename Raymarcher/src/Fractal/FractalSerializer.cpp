#include "rmpch.h"
#include "Fractal/FractalSerializer.h"

#include "Fractal/Folds/Folds.h"
#include "Fractal/ColorMods/ColorMod.h"
#include "Fractal/FractalGeometry.h"

#include <glm/glm.hpp>
#include <yaml-cpp/yaml.h>



namespace YAML
{
	template<>
	struct convert<glm::vec3>
	{
		static Node encode(const glm::vec3& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec3& rhs)
		{
			if (!node.IsSequence() || node.size() != 3)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};
}



namespace RM
{
	static void DeserializeFolds(const std::string& type, YAML::Node& node, std::vector<Ref<IGLSLConvertable>>& deserializedTransformations)
	{
		if (type == FoldScaleTranslate::ToString())
		{
			float scale = node["Fields"]["Scale"].as<float>();
			glm::vec3 translation = node["Fields"]["Translation"].as<glm::vec3>();
			Ref<FoldScaleTranslate> fold = CreateRef<FoldScaleTranslate>(scale, translation);
			deserializedTransformations.push_back(fold);
		}
		else if (type == FoldScaleOrigin::ToString())
		{
			float scale = node["Fields"]["Scale"].as<float>();
			glm::vec3 origin = node["Fields"]["Origin"].as<glm::vec3>();
			Ref<FoldScaleOrigin> fold = CreateRef<FoldScaleOrigin>(scale, origin);
			deserializedTransformations.push_back(fold);
		}
		else if (type == FoldPlane::ToString())
		{
			float factor = node["Fields"]["Factor"].as<float>();
			int direction = node["Fields"]["Direction"].as<int>();

			Ref<FoldPlane> fold = CreateRef<FoldPlane>((FoldPlane::FoldDirection)direction, factor);
			deserializedTransformations.push_back(fold);
		}
		else if (type == FoldMenger::ToString())
		{
			Ref<FoldMenger> fold = CreateRef<FoldMenger>();
			deserializedTransformations.push_back(fold);
		}
		else if (type == FoldSierpinski::ToString())
		{
			Ref<FoldSierpinski> fold = CreateRef<FoldSierpinski>();
			deserializedTransformations.push_back(fold);
		}
		else if (type == FoldBox::ToString())
		{
			glm::vec3 range = node["Fields"]["Range"].as<glm::vec3>();
			Ref<FoldBox> fold = CreateRef<FoldBox>(range);
			deserializedTransformations.push_back(fold);
		}
		else if (type == FoldSphere::ToString())
		{
			float minRadius = node["Fields"]["Min Radius"].as<float>();
			float maxRadius = node["Fields"]["Max Radius"].as<float>();
			Ref<FoldSphere> fold = CreateRef<FoldSphere>(minRadius, maxRadius);
			deserializedTransformations.push_back(fold);
		}
		else if (type == FoldAbs::ToString())
		{
			glm::vec3 center = node["Fields"]["Center"] .as<glm::vec3>();
			Ref<FoldAbs> fold = CreateRef<FoldAbs>(center);
			deserializedTransformations.push_back(fold);
		}
		else if (type == FoldInversion::ToString())
		{
			float epsilon = node["Fields"]["Epsilon"].as<float>();
			Ref<FoldInversion> fold = CreateRef<FoldInversion>(epsilon);
			deserializedTransformations.push_back(fold);
		}
		else if (type == FoldRotateX::ToString())
		{
			float radians = node["Fields"]["Radians"].as<float>();
			Ref<FoldRotateX> fold = CreateRef<FoldRotateX>(glm::degrees(radians));
			deserializedTransformations.push_back(fold);
		}
		else if (type == FoldRotateY::ToString())
		{
			float radians = node["Fields"]["Radians"].as<float>();
			Ref<FoldRotateY> fold = CreateRef<FoldRotateY>(glm::degrees(radians));
			deserializedTransformations.push_back(fold);
		}
		else if (type == FoldRotateZ::ToString())
		{
			float radians = node["Fields"]["Radians"].as<float>();
			Ref<FoldRotateZ> fold = CreateRef<FoldRotateZ>(glm::degrees(radians));
			deserializedTransformations.push_back(fold);
		}
		else if (type == FoldRepeatX::ToString())
		{
			float step = node["Fields"]["Step"].as<float>();
			Ref<FoldRepeatX> fold = CreateRef<FoldRepeatX>(step);
			deserializedTransformations.push_back(fold);
		}
		else if (type == FoldRepeatY::ToString())
		{
			float step = node["Fields"]["Step"].as<float>();
			Ref<FoldRepeatY> fold = CreateRef<FoldRepeatY>(step);
			deserializedTransformations.push_back(fold);
		}
		else if (type == FoldRepeatZ::ToString())
		{
			float step = node["Fields"]["Step"].as<float>();
			Ref<FoldRepeatZ> fold = CreateRef<FoldRepeatZ>(step);
			deserializedTransformations.push_back(fold);
		}
		else if (type == FoldRepeatXYZ::ToString())
		{
			float step = node["Fields"]["Step"].as<float>();
			Ref<FoldRepeatXYZ> fold = CreateRef<FoldRepeatXYZ>(step);
			deserializedTransformations.push_back(fold);
		}
	}
	static void DeserializeColorMods(const std::string& type, YAML::Node& node, std::vector<Ref<IGLSLConvertable>>& deserializedTransformations)
	{
		if (type == ColorModZero::ToString())
		{
			Ref<ColorModZero> colorMod = CreateRef<ColorModZero>();
			deserializedTransformations.push_back(colorMod);
		}
		else if (type == ColorModInfinity::ToString())
		{
			Ref<ColorModInfinity> colorMod = CreateRef<ColorModInfinity>();
			deserializedTransformations.push_back(colorMod);
		}
		else if (type == ColorModNegativeInfinity::ToString())
		{
			Ref<ColorModNegativeInfinity> colorMod = CreateRef<ColorModNegativeInfinity>();
			deserializedTransformations.push_back(colorMod);
		}
		else if (type == ColorModSum::ToString())
		{
			glm::vec3 scale = node["Fields"]["Scale"].as<glm::vec3>();
			glm::vec3 origin = node["Fields"]["Origin"].as<glm::vec3>();

			Ref<ColorModSum> colorMod = CreateRef<ColorModSum>(scale, origin);
			deserializedTransformations.push_back(colorMod);
		}
		else if (type == ColorModSumAbs::ToString())
		{
			glm::vec3 scale = node["Fields"]["Scale"].as<glm::vec3>();
			glm::vec3 origin = node["Fields"]["Origin"].as<glm::vec3>();

			Ref<ColorModSumAbs> colorMod = CreateRef<ColorModSumAbs>(scale, origin);
			deserializedTransformations.push_back(colorMod);
		}
		else if (type == ColorModMinAbs::ToString())
		{
			glm::vec3 scale = node["Fields"]["Scale"].as<glm::vec3>();
			glm::vec3 origin = node["Fields"]["Origin"].as<glm::vec3>();

			Ref<ColorModMinAbs> colorMod = CreateRef<ColorModMinAbs>(scale, origin);
			deserializedTransformations.push_back(colorMod);
		}
		else if (type == ColorModMaxAbs::ToString())
		{
			glm::vec3 scale = node["Fields"]["Scale"].as<glm::vec3>();
			glm::vec3 origin = node["Fields"]["Origin"].as<glm::vec3>();

			Ref<ColorModMaxAbs> colorMod = CreateRef<ColorModMaxAbs>(scale, origin);
			deserializedTransformations.push_back(colorMod);
		}
		else if (type == ColorModMin::ToString())
		{
			glm::vec3 scale = node["Fields"]["Scale"].as<glm::vec3>();
			glm::vec3 origin = node["Fields"]["Origin"].as<glm::vec3>();

			Ref<ColorModMin> colorMod = CreateRef<ColorModMin>(scale, origin);
			deserializedTransformations.push_back(colorMod);
		}
		else if (type == ColorModMax::ToString())
		{
			glm::vec3 scale = node["Fields"]["Scale"].as<glm::vec3>();
			glm::vec3 origin = node["Fields"]["Origin"].as<glm::vec3>();

			Ref<ColorModMax> colorMod = CreateRef<ColorModMax>(scale, origin);
			deserializedTransformations.push_back(colorMod);
		}
	}
	static void DeserializeGeometry(const std::string& type, YAML::Node& node, std::vector<Ref<IGLSLConvertable>>& deserializedTransformations)
	{
		if (type == Box::ToString())
		{
			glm::vec3 scale = node["Fields"]["Scale"].as<glm::vec3>();
			glm::vec3 offset = node["Fields"]["Offset"].as<glm::vec3>();
			glm::vec3 color = node["Fields"]["Color"].as<glm::vec3>();
			int colorType = node["Fields"]["ColorType"].as<int>();

			Ref<Box> geo = CreateRef<Box>((ColorType)colorType, scale, offset, color);
			deserializedTransformations.push_back(geo);
		}
		else if (type == Sphere::ToString())
		{
			float radius = node["Fields"]["Radius"].as<float>();
			glm::vec3 center = node["Fields"]["Center"].as<glm::vec3>();
			glm::vec3 color = node["Fields"]["Color"].as<glm::vec3>();
			int colorType = node["Fields"]["ColorType"].as<int>();

			Ref<Sphere> geo = CreateRef<Sphere>((ColorType)colorType, radius, center, color);
			deserializedTransformations.push_back(geo);
		}
		else if (type == Tetrahedron::ToString())
		{
			float radius = node["Fields"]["Radius"].as<float>();
			glm::vec3 center = node["Fields"]["Center"].as<glm::vec3>();
			glm::vec3 color = node["Fields"]["Color"].as<glm::vec3>();
			int colorType = node["Fields"]["ColorType"].as<int>();

			Ref<Sphere> geo = CreateRef<Sphere>((ColorType)colorType, radius, center, color);
			deserializedTransformations.push_back(geo);
		}
	}

	void FractalSerializer::Serialize(const Ref<Fractal>& fractal)
	{
		std::string filePath = "assets/fractals/" + fractal->GetName();

		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Fractal" << YAML::Value << fractal->GetName();
		out << YAML::Key << "Iteration Data" << YAML::Value << YAML::BeginMap;
		out << YAML::Key << "Begin" << YAML::Value << fractal->GetBegin();
		out << YAML::Key << "End" << YAML::Value << fractal->GetEnd();
		out << YAML::Key << "Iterations" << YAML::Value << fractal->GetIterations();
		out << YAML::EndMap;
		out << YAML::Key << "Transformations" << YAML::Value << YAML::BeginSeq;

		for (auto transformation : fractal->Transformations())
			transformation->Serialize(out);

		out << YAML::EndSeq;
		out << YAML::EndMap;
		std::ofstream fout(filePath);
		fout << out.c_str();
	}

	Ref<Fractal> FractalSerializer::Deserialize(const std::string& filePath)
	{
		YAML::Node data;

		try
		{
			data = YAML::LoadFile(filePath);
		}
		catch (YAML::ParserException e)
		{
			return nullptr;
		}

		if (!data["Fractal"])
			return nullptr;

		std::string fractalName = data["Fractal"].as<std::string>();

		auto transformations = data["Transformations"];
		
		std::vector<Ref<IGLSLConvertable>> deserializedTransformations;

		if (transformations)
		{
			for (auto transformation : transformations)
			{
				std::string type = transformation["Type"].as<std::string>();

				DeserializeColorMods(type, transformation, deserializedTransformations);
				DeserializeFolds(type, transformation, deserializedTransformations);
				DeserializeGeometry(type, transformation, deserializedTransformations);
			}
		}

		auto iterationData = data["Iteration Data"];
		uint32_t begin = iterationData["Begin"].as<uint32_t>();
		uint32_t end = iterationData["End"].as<uint32_t>();
		uint32_t iterationCount = iterationData["Iterations"].as<uint32_t>();

		Ref<Fractal> fractal = CreateRef<Fractal>(fractalName);
		fractal->SetBegin(begin);
		fractal->SetEnd(end);
		fractal->SetIterations(iterationCount);
		fractal->SetTransformations(deserializedTransformations);

		return fractal;
	}
}