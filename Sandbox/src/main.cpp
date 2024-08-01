
#include <MeCore.h>
#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <any>
#include <vector>
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

	ME::Ref<ME::CameraController> cam;
	ME::Ref<ME::Material> mat = ME::Ref<ME::Material>(new ME::Material({ {1,1,1,1} })), mat2 = ME::Ref<ME::Material>(new ME::Material({ {1,1,1,1} }));
	ME::Ref<ME::Shader> shader;
	std::vector<ME::Mesh> grid;
	ME::ShaderLibrary lib;
	ExampleLayer() : Layer("ExampleLayer"), cam(ME::Ref<ME::CameraController>(new ME::CameraController(new ME::PerspectiveCamera(90.0, ME::Application::getInstance().getWidth(),  ME::Application::getInstance().getHeight())))) {
		mat->tex = ME::Texture2D::create("assets/textures/ChernoLogo.png");
		mat2->tex = ME::Texture2D::create("assets/textures/test.png");
		mat2->albeto.g = 0;
		cam->getCamera()->setPosition({ 0,0,0.5 });
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
				m2.addSquare(5, 6, 2, 1);
				m2.addSquare(0, 3, 7, 4);
				
				//m2.getTransform().setScale({ 0.1,0.1,0.1 });
				m2.getTransform().setPos({ i * 0.11f,0,(1-j) * -1.1f });
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
		cam->update(step);
	}
	float* calcW(std::vector<glm::vec3>& vertices, ME::Mesh& m2) {
		float w = 0, x = 0, y = 0;
		
		for (int i = 0; i < vertices.size(); i++) {
			glm::vec4 v2 = glm::vec4(vertices[i].x, vertices[i].y, vertices[i].z, 1);
			glm::vec4 v = (cam->getCamera()->getViewProjection() * m2.getTransform().getMeshMatrix()) * v2;
			
			w += (float)floor(v.w * 100);
			x += (float)floor(v.x * 100);
			y += (float)floor(v.y * 100);
		}
		
		w /= (float)vertices.size();
		x /= (float)vertices.size();
		y /= (float)vertices.size();

		return new float[3] {w, x, y};
	}
	bool contains(const std::vector<int> data, const int find) {
		return std::find(data.begin(), data.end(), find) != data.end();
	}
	bool init = false;
	void onRender() override {
		
		RC::setClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		RC::clear();
		R::beginScene(cam->getCamera());
		std::vector<int> used;
		for (int i = 0; i < grid.size(); i++) {
			ME::Mesh m = grid[i];
			float* w = calcW(m.getActPos(), m);
			int id = i;
			bool s = std::find(used.begin(), used.end(), id) != used.end();
			for (int j = 0; j < grid.size(); j++) {
				
				ME::Mesh m2 = grid[j];
				
				bool s = contains(used, id);
				bool s2 = contains(used, j);
				float* w2 = calcW(m2.getActPos(), m2);
				
				if (s) {
					
					
					w = w2;
					m = m2;
					id = j;
					
				}
				else if (!s2) {
					if (w[0] < w2[0]) {
						w = w2;
						m = m2;
						id = j;
					}
					else if (w[0] == w2[0]) {
						if (w[1] > w2[1]) {
							w = w2;
							m = m2;
							id = j;
						}
						else if (w[1] == w2[1]) {
							if (w[2] > w2[2]) {
								w = w2;
								m = m2;
								id = j;
							}
						}
					}
				}
				
			}

			used.push_back(id);
			R::submit(lib.get("main"), grid[id]);
		}
		//ME_CORE_INFO("");
		R::endScene();
	}

	bool onEvent(ME::Events& e) override {
		if (!cam->onEvent(e)) {
			return false;
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