
#include <MeCore.h>

class ExampleLayer : public ME::Layer {

public:
	ExampleLayer() : Layer("ExampleLayer") {};

	void onUpdate() override {
		//ME_CLIENT_INFO("ExampleLayer::onUpdate");
	}

	void onRender() override {
		//ME_CLIENT_INFO("ExampleLayer::onRender");
	}

	bool onEvent(ME::Events& e) override {
		std::string name = e.ToString();
		
		return true;
	}
};

class Sandbox : public ME::Application {
public:
	
	Sandbox() {
		pushLayer(new ExampleLayer());
		pushOverlay(new ME::ImGuiLayer());
	}
	~Sandbox() {

	}
};

ME::Application* ME::CreateApplication() {
	return new Sandbox();
}