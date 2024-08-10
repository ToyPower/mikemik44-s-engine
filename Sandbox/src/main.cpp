
#include <MeCore.h>
#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <any>
#include <vector>
#include "main/entry/Entry.h"
//#include "Sandbox.h"
#include "Sandbox2D.h"
//#include "Flappy.h"

class Sandbox : public ME::Application {
public:
	
	Sandbox() {
		
		//pushLayer(new ExampleLayer());
		pushLayer(new Sandbox2D());
		//pushLayer(new Flappy());
	}
	~Sandbox() {

	}
};

ME::Application* ME::CreateApplication() {
	return new Sandbox();
}