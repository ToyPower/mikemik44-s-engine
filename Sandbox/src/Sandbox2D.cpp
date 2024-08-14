#include <hzpch.h>
#include "Sandbox2D.h"
#include <glm/gtc/type_ptr.hpp>
#define R ME::Renderer2D
#define RC ME::RendererContent

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), cam(new ME::CameraController(new ME::OthrographicCamera((float)ME::Application::getInstance().getWidth() / ME::Application::getInstance().getHeight()), true)) {}

void Sandbox2D::onAttach() {
	ME::Renderer2D::init();
	tex = ME::Ref<ME::Texture>(ME::Texture2D::create("assets/textures/test.png"));

	spriteSheet = ME::Ref<ME::Texture>(ME::Texture2D::create("assets/game/textures/RPGpack_sheet_2X.png"));
	stairs = ME::SubTexture2D::createFromCoords(spriteSheet, {7,6}, { 128,128 });
	barrel = ME::SubTexture2D::createFromCoords(spriteSheet, { 8,2 }, { 128,128 });
	tree = ME::SubTexture2D::createFromCoords(spriteSheet, { 2,1 }, { 128,128 }, {1,2});
	m_Particle.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	m_Particle.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_Particle.SizeBegin = 0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 5.0f;
	m_Particle.Velocity = { 0.0f, 0.0f };
	m_Particle.VelocityVariation = { 3.0f, 1.0f };
	m_Particle.Position = { 0.0f, 0.0f };
}

void Sandbox2D::onDetach() {
	ME::Renderer2D::shutdown();
}
static float rotation = 0.0f;

void Sandbox2D::onUpdate(ME::TimeStep step) {
	rotation += step * 50;
	this->tim.restart();
	ME::Timer tim("update");
	cam->update(step);
	tim.stop(true);

	if (ME::Input::isButtonPress(ME_MOUSE_BUTTON_LEFT))
	{
		auto [x, y] = ME::Input::getMousePos();
		auto width = ME::Application::getInstance().getWidth();
		auto height = ME::Application::getInstance().getHeight();

		auto bounds = cam->getBounds();
		auto pos = cam->getCamera()->getPosition();
		x = (x / width) * bounds.getWidth() - bounds.getWidth() * 0.5f;
		y = bounds.getHeight() * 0.5f - (1-(y / height)) * bounds.getHeight();
		m_Particle.Position = { x + pos.x, y + pos.y };
		for (int i = 0; i < 5; i++)
			m_ParticleSystem.Emit(m_Particle);
	}

	m_ParticleSystem.OnUpdate(step);

}

void Sandbox2D::onRender() {
	ME::Timer tim("Renderer");
	R::clear();
#ifdef ffff 
	R::beginScene(cam->getCamera());
	
	ME::Timer tim2("Rendering Time");

	R::setRotation(-45, false);
	R::drawQuadCentered({ 1.0f, 0, 0.1f }, { 0.8f, 0.8f }, color);
	R::setRotation(0);

	R::drawQuadCentered({ -1.0f, 0.0f, 0.1f }, { 0.8f, 0.8f }, color);


	R::drawQuadCentered({ 0.5f, -0.5f, 0.1f }, { 0.5f, 0.75f }, color2);
	
	R::drawQuadCentered({ 0,0, -0.1f }, { 20, 20 }, tex, color3, 10);

	R::rotate(rotation, false);
	R::drawQuadCentered({ -2.0f, 0.0f, 0.0f }, { 1, 1 }, tex, {1,1,1,1}, 20);
	R::setRotation(0);
	
	for (float x = -5.0f; x < 5.0f; x += 0.5) {
		for (float y = -5.0f; y < 5.0f; y += 0.5) {
			glm::vec4 color = { (x + 5.0) / 10.0f, 0.4f, (y + 5.0) / 10.0f, 0.75f };
			R::drawQuadCentered({ x, y }, { 0.45f, 0.45f }, color);
		}
	}
	R::endScene();
#endif
	m_ParticleSystem.OnRender(cam->getCamera());

	R::beginScene(cam->getCamera());
	R::drawQuadCentered({ 0.0f, 0.0f, 0.5f }, { 1, 1 }, stairs);
	R::drawQuadCentered({ 1.0f, 0.0f, 0.5f }, { 1, 1 }, barrel);
	R::drawQuadCentered({ 0.5f, 1.5f, 0.5f }, { 1, 2 }, tree);
	R::endScene();

	
	
	//tim2.stop(true);
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
