#pragma once

#include <vector>

#include "Hazel/Core/Core.h"
#include "Layer.h"

namespace Hazel {
	class HAZEL_API LayerStack
	{
	public:
		LayerStack();

		~LayerStack();

		void PushLayer(Layer* layer);

		void PushOverlay(Layer* overlay);

		void PopLayer(Layer* layer);

		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin();

		std::vector<Layer*>::iterator end();

	private:
		std::vector<Layer*> m_Layers;

		unsigned int m_LayerInsertIndex = 0;

	};

}