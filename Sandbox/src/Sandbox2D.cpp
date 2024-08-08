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
	this->tim.restart();
	ME::Timer tim("update");
	cam->update(step);
	tim.stop(true);
}

void Sandbox2D::onRender() {
	ME::Timer tim("Renderer");
	R::clear();
	R::beginScene(cam->getCamera());
	
	ME::Timer tim2("Rendering Time");
	R::rotate(-45);
	R::drawQuad({ -1.0f, 0 }, { 0.8f, 0.8f }, color);
	R::setRotation(0);
	R::drawQuad({ 0.5f, 0.5f }, { 0.5f, 0.75f }, color2);
	
	R::drawQuad({ 0, 0, 0.1 }, { 10, 10 }, tex, color3, 10);

	R::endScene();
	tim2.stop(true);
	tim.stop(true);
	this->tim.stop();
}

void Sandbox2D::onGUIRender() {
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("color 1", glm::value_ptr(color));
	ImGui::ColorEdit4("color 2", glm::value_ptr(color2));
	ImGui::ColorEdit4("color 3", glm::value_ptr(color3));
	for (ME::TimerResult tr : ME::TimerResult::allResults) {
		char label[50] = {};
		strcpy(label, tr.name);
		strcat(label, " %.3fms");
		ImGui::Text(label, tr.timer);
	}
	ME::TimerResult::clearTimerResult();
	ImGui::End();
}
