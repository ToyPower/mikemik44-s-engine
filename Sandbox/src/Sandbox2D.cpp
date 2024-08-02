#include <hzpch.h>
#include "Sandbox2D.h"
#include <glm/gtc/type_ptr.hpp>
#define R ME::Renderer2D
#define RC ME::RendererContent

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), cam(new ME::CameraController(new ME::OthrographicCamera((float)ME::Application::getInstance().getWidth() / ME::Application::getInstance().getHeight()), true)) {}

void Sandbox2D::onAttach() {
	ME::Renderer2D::init();
	tex = ME::Ref<ME::Texture>(ME::Texture2D::create("assets/textures/test.png"));
}

void Sandbox2D::onDetach() {
	ME::Renderer2D::shutdown();
}

void Sandbox2D::onUpdate(ME::TimeStep step) {
	cam->update(step);
}

void Sandbox2D::onRender() {
	R::clear();
	R::beginScene(cam->getCamera());
	
	R::drawQuad({ -1.0f, 0 }, { 0.8f, 0.8f }, color);
	R::drawQuad({ 0.5f, 0.5f }, { 0.5f, 0.75f }, color2);
	R::drawQuad({ 0, 0, 0.1 }, { 10, 10 }, tex, color3);
	
	R::endScene();
}

void Sandbox2D::onGUIRender() {
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("color 1", glm::value_ptr(color));
	ImGui::ColorEdit4("color 2", glm::value_ptr(color2));
	ImGui::ColorEdit4("color 3", glm::value_ptr(color3));
	ImGui::End();
}
