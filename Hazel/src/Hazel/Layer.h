#pragma once

#include "Hazel/Core.h"
#include "Hazel/Events/Event.h"

namespace Hazel {
	class HAZEL_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");

		virtual ~Layer();

		inline virtual void OnAttach();

		inline virtual void OnDetach();

		inline virtual void OnUpdate();

		inline virtual void OnImGuiRender();

		inline virtual void OnEvent(Event& event);

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;

	};

}