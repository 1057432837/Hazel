#pragma once

#include "Hazel/Core/Core.h"
#include "Hazel/Events/Event.h"
#include "Hazel/Core/Timestep.h"

namespace Hazel {
	class HAZEL_API Layer
	{
	public:
		Layer();

		virtual ~Layer();

		Layer(const std::string& name = "Layer");

		inline virtual void OnAttach() { }

		inline virtual void OnDetach() { }

		inline virtual void OnUpdate(Timestep ts) { }

		inline virtual void OnImGuiRender() { }

		inline virtual void OnEvent(Event& event) { }

		inline const std::string& GetName() const { return m_DebugName; }

		static Layer* Create();

	protected:
		std::string m_DebugName;

	};

}