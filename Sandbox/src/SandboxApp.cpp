#include "imgui/imgui.h"

#include "Hazel.h"

class ExampleLayer : public Hazel::Layer
{
public:
	ExampleLayer() : Layer("Example") {
		//auto cam = camera(5.0f, { 0.5f, 0.5f });

	}

	void OnUpdate() override {
		if (Hazel::Input::IsKeyPressed(HZ_KEY_TAB))
		{
			HZ_CLIENT_TRACE("Tab key is pressed! (poll)");

		}

	}

	virtual void OnImGuiRender() override {
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();

	}

	void OnEvent(Hazel::Event& event) override {
		if (event.GetEventType() == Hazel::EventType::KeyPressed)
		{
			Hazel::KeyPressedEvent& e = (Hazel::KeyPressedEvent&)event;
			if (e.GetKeyCode() == HZ_KEY_TAB)
			{
				HZ_CLIENT_TRACE("Tab key is pressed (event)!");

			}
			HZ_CLIENT_TRACE("{0}", (char)e.GetKeyCode());

		}

	}

};

class Sandbox : public Hazel::Application
{
public:
	Sandbox() {
		PushLayer(new ExampleLayer());

	}

	~Sandbox() { }

private:

};

//调用Application.h的CreateApplication()实例化并返回到入口函数
Hazel::Application* Hazel::CreateApplication() {
	return new Sandbox();

}