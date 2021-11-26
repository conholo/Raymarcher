#pragma once

#include <stdint.h>
#include <string>
#include "Fractal/IGLSLConvertable.h"

namespace RM
{
	namespace UI
	{
		class FractalComponentEditorUI
		{
		public:
			FractalComponentEditorUI(const std::string componentName, uint32_t id)
				:m_ComponentName(componentName), m_ID(id) { }

			void SetID(uint32_t newID) { m_ID = newID; }

			virtual void DrawEditor(const std::string& fractalName) = 0;
			uint32_t GetID() const { return m_ID; }
			std::string GetUIID() const { return m_ComponentName + " " + std::to_string(m_ID); }

			virtual Ref<IGLSLConvertable> GetConvertable() = 0;

		protected:
			std::string m_ComponentName;
			uint32_t m_ID;
		};
	}
}
