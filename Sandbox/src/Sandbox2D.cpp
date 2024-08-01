#include <hzpch.h>
#include "Sandbox2D.h"
#include <glm/gtc/type_ptr.hpp>
#define R ME::Renderer
#define RC ME::RendererContent
ME::Vertex create1(glm::vec3 pos, glm::vec4 color) {
	ME::Vertex v(pos);
	v.putData("color", color);
	return v;
}

ME::Vertex create1(glm::vec3 pos, glm::vec4 color, glm::vec2 texCoord) {
	ME::Vertex v(pos);
	v.putData("color", color);
	v.putData("texCoord", texCoord);
	return v;
}

ME::Vertex create1(glm::vec3 pos) {
	ME::Vertex v(pos);
	return v;
}
void Sandbox2D::onAttach() {
	
	cam.reset(new ME::CameraController(new ME::OthrographicCamera((float)ME::Application::getInstance().getWidth()/ ME::Application::getInstance().getHeight()), true));
	cam->getCamera()->setPosition({ 0,0,0.5 });
	for (uint32_t i = 0; i < 1; i++) {

		for (uint32_t j = 0; j < 1; j++) {
			ME::Mesh m2 = ME::Mesh();

			m2.addVertex(create1({ -0.5,-0.5f,0.0f }, { 1,1,1,1 }));
			m2.addVertex(create1({ -0.5,0.5f,0.0f }, { 1,1,1,1 }));
			m2.addVertex(create1({ 0.5,0.5f,0.0f }, { 1,1,1,1 }));
			m2.addVertex(create1({ 0.5,-0.5f,0.0f }, { 1,1,1,1 }));


			m2.addSquare(0,1,2,3);

			//m2.getTransform().setPos({ i * 0.11f,0,(1 - j) * -1.1f });
			m2.getMaterial()->albeto.a = 1;
			m2.getMaterial()->albeto.b = 1;
			m2.getMaterial()->albeto.g = 1;
			m2.getMaterial()->albeto.r = 1;
			
			grid.push_back(m2);
		}
	}

	shader = (ME::Shader::create("assets/shaders/color_shader.shader"));
}

void Sandbox2D::onDetach() {

}

void Sandbox2D::onUpdate(ME::TimeStep step) {
	cam->update(step);
}

void Sandbox2D::onRender() {
	RC::setClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	RC::clear();
	R::beginScene(cam->getCamera());

	for (int i = 0; i < grid.size(); i++) {
		ME::Mesh m = grid[i];
		R::submit(shader, m);
	}
	
	R::endScene();
}

void Sandbox2D::onGUIRender() {
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Sphere color", mptr(grid[0].getMaterial()->albeto));
	ImGui::End();
}
