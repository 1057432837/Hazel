#include "Hazel.h"
#include "Hazel/Core/EntryPoint.h"
#include "EditorLayer.h"
#include "HazelnutApp.h"

namespace Hazel {
	Hazelnut::Hazelnut() : Application("Hazelnut") {
		PushLayer(new EditorLayer());

	}

	Hazelnut::~Hazelnut() {

	}

	Application* CreateApplication() {
		return new Hazelnut();

	}

}