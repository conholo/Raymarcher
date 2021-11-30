#pragma once

#include "Fractal/Fractal.h"

namespace RM
{
	class FractalSerializer
	{
	public:
		static void Serialize(const Ref<Fractal>& fractal);
		static Ref<Fractal> Deserialize(const std::string& filePath);
	};
}