
#include <MeCore.h>
#include <glm/glm.hpp>

#include <imgui/imgui.h>
#include <any>
#define R ME::Renderer
#define RC ME::RendererContent
ME::Vertex create(glm::vec3 pos, glm::vec4 color) {
	ME::Vertex v(pos);
	v.putData("color", color);
	return v;
}

ME::Vertex create(glm::vec3 pos, glm::vec4 color, glm::vec2 texCoord) {
	ME::Vertex v(pos);
	v.putData("color", color);
	v.putData("texCoord", texCoord);
	return v;
}

ME::Vertex create(glm::vec3 pos) {
	ME::Vertex v(pos);
	return v;
}

class ExampleLayer : public ME::Layer {

public:

	ME::PerspectiveCamera cam = ME::PerspectiveCamera(90.0f, 800, 600, 0.001);
	ME::Ref<ME::Material> mat = ME::Ref<ME::Material>(new ME::Material({ {1,1,1,1} })), mat2 = ME::Ref<ME::Material>(new ME::Material({ {1,1,1,1} }));
	ME::Ref<ME::Shader> shader;
	std::vector<ME::Mesh> grid;
	ME::ShaderLibrary lib;
	ExampleLayer() : Layer("ExampleLayer") {
		mat->tex = ME::Texture2D::create("assets/textures/ChernoLogo.png");
		mat2->tex = ME::Texture2D::create("assets/textures/test.png");
		mat2->albeto.g = 0;
		cam.setPosition({ 0,0,0.5 });
		for (uint32_t i = 0; i < 1; i++) {
		
			for (uint32_t j = 0; j < 2; j++) {
				ME::Mesh m2 = ME::Mesh();
				
				m2.addVertex(create({ -0.5,-0.5f,0.0f }, { 1,1,1,1 }, { 0,0 }));
				m2.addVertex(create({ -0.5,0.5f,0.0f }, { 1,1,1,1 }, { 0,1 }));
				m2.addVertex(create({ 0.5,0.5f,0.0f }, { 1,1,1,1 }, { 1,1 }));
				m2.addVertex(create({ 0.5,-0.5f,0.0f }, { 1,1,1,1 }, { 1,0 }));

				m2.addVertex(create({ -0.5,-0.5f,-1.0f }, { 1,1,1,1 }, { 1,0 }));
				m2.addVertex(create({ -0.5,0.5f,-1.0f }, { 1,1,1,1 }, { 1,1 }));
				m2.addVertex(create({ 0.5,0.5f,-1.0f }, { 1,1,1,1 }, { 0,1 }));
				m2.addVertex(create({ 0.5,-0.5f,-1.0f }, { 1,1,1,1 }, { 0,0 }));
				
				
				m2.addSquare(7, 6, 5, 4);
				m2.addSquare(4, 0, 1, 5);
				m2.addSquare(3, 7, 6, 2);
				m2.addSquare(0, 1, 2, 3);
				
				m2.getTransform().setScale({ 0.1,0.1,0.1 });
				m2.getTransform().setPos({ i * 0.11f,0,(1-j) * -0.101f });
				if (j == 1) {
					m2.setMaterial(mat);
				}
				else {
					m2.setMaterial(mat2);
				}
				grid.push_back(m2);
			}
		}
		
		
		lib.load("main", ("assets/shaders/data.shader"));
	
	};

	virtual void onGUIRender() override {
		
		ImGui::Begin("Control");
		ImGui::ColorEdit3("Color", (float*)&grid[0].getMaterial()->albeto, 0.01F);
		
		ImGui::End();
		
	}

	void onUpdate(ME::TimeStep step) override {
		
		float offset = (1.0f / 144.0f) * 60.0f;
		float mov = step * 10* 8;
		float rot = step *180;
		if (ME::Input::isKeyPress(ME_KEY_W)) {
			cam.move(cam.getForward(), 0.1 * offset * mov);
		}

		if (ME::Input::isKeyPress(ME_KEY_Q)) {
			cam.rotate({ -1,0,0 }, 2 * offset * rot);
		}

		if (ME::Input::isKeyPress(ME_KEY_E)) {
			cam.rotate({ 1,0,0 }, 2 * offset * rot);
		}
		if (ME::Input::isKeyPress(ME_KEY_S)) {
			cam.move(cam.getBackward(), 0.1 * offset * mov);
		}
		if (ME::Input::isKeyPress(ME_KEY_A)) {
			cam.move(cam.getLeft(), 0.1 * offset * mov);
		}
		if (ME::Input::isKeyPress(ME_KEY_D)) {
			cam.move(cam.getRight(), 0.1 * offset * mov);
		}

		
	}
	
	bool init = false;
	void onRender() override {
		
		RC::setClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		RC::clear();
		R::beginScene(cam);
		for (ME::Mesh m : grid) {
			R::submit(lib.get("main"), m);
		}
		
		R::endScene();
	}

	bool onEvent(ME::Events& e) override {
		
		if (e.name() == "windowResize") {
			
			cam.onResize(std::any_cast<int>(e.getParam("width")), std::any_cast<int>(e.getParam("height")));
		}
		return true;
	}
};

class Sandbox : public ME::Application {
public:
	
	Sandbox() {
		pushLayer(new ExampleLayer());
	
	}
	~Sandbox() {

	}
};

ME::Application* ME::CreateApplication() {
	return new Sandbox();
}