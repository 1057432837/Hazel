#include "Hazel.h"
#include "Hazel/Core/EntryPoint.h"
#include "EditorLayer.h"
#include "HazelEditorApp.h"

namespace Hazel {
	HazelEditor::HazelEditor() : Application("Hazel Editor") {
		PushLayer(new EditorLayer());

	}

	HazelEditor::~HazelEditor() {

	}

	Application* CreateApplication() {
		return new HazelEditor();

	}

}