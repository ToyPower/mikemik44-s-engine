
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

	ME::PerspectiveCamera cam = ME::PerspectiveCamera(90.0f, 800, 600);
	ME::Ref<ME::Material> mat = ME::Ref<ME::Material>(new ME::Material({ {1,0,1,1} }));
	ME::Ref<ME::Shader> shader, shader2;
	std::vector<ME::Mesh> grid;
	ExampleLayer() : Layer("ExampleLayer") {
		
		cam.setPosition({ 0,0,0.5 });
		
		for (uint32_t i = 0; i < 20; i++) {
			for (uint32_t j = 0; j < 20; j++) {
				ME::Mesh m2;
				m2.addVertex(create({ -0.5,-0.5f,0.0f }));
				m2.addVertex(create({ -0.5,0.5f,0.0f }));
				m2.addVertex(create({ 0.5,0.5f,0.0f }));
				m2.addVertex(create({ 0.5,-0.5f,0.0f }));
				m2.addSquare(0, 1, 2, 3);
				m2.getTransform().setScale({ 0.1,0.1,0.1 });
				m2.getTransform().setPos({ i * 0.11f,j * 0.11f,0 });
				m2.setMaterial(mat);
				grid.push_back(m2);
			}
		}
		

		const std::string& a = R"(#version 410 core
			layout(location = 0) in vec3 position;
			layout(location = 1) in vec4 color1;
			layout(location = 2) in vec2 texCoord;
			uniform mat4 u_proj;
			uniform mat4 u_mesh;
			uniform vec4 u_color;
			out vec4 color; 

			void main() {
				color = color1 * u_color;
				color.x = color.x + texCoord.x;
				color.y = color.y + texCoord.y;
				
				gl_Position = u_proj * u_mesh * vec4(position,1);
			}
		)";
		const std::string& b = R"(#version 410 core
			in vec4 color;
			
			void main() {
			
				gl_FragColor = color;

			}
		)";
		shader.reset(ME::Shader::create(a, b));

		const std::string& a2 = R"(#version 410 core
			layout(location = 0) in vec3 position;
			out vec4 color;
			uniform mat4 u_proj;
			uniform mat4 u_mesh;
			uniform vec4 u_color;
			void main() {
				color = vec4(1,1,1,1.0f) * u_color;
				gl_Position = u_proj * u_mesh * vec4(position,1);
			}
		)";
		const std::string& b2 = R"(#version 410 core
			in vec4 color;
			
			void main() {
			
				gl_FragColor = color;

			}
		)";
		shader2.reset(ME::Shader::create(a2, b2));
	
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
			R::submit(shader2, m);
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