#pragma once
#include <MeCore.h>
#include <main/layer/Layer.h>
#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <any>
#include <vector>
#include "Particle.h"

class Sandbox2D : public ME::Layer{

public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;
	virtual void onAttach() override;
	virtual void onDetach() override;
	virtual void onUpdate(ME::TimeStep step) override;
	virtual void onRender() override;
	virtual bool onEvent(ME::Events& e) override {
		if (!cam->onEvent(e)) {
			return false;
		}

		return true;
	}
	
	virtual void onGUIRender() override;
private:
	ME::Ref<ME::CameraController> cam;
	glm::vec4 color = { 1,0,0,1 }, color2 = { 0.2, 0.3, 0.8, 1 }, color3 = { 1,1,1,1 };
	//TEMP
	ME::Ref<ME::Texture> tex;
	ME::Ref<ME::Texture> spriteSheet;
	ME::Ref<ME::SubTexture2D> stairs, barrel, tree;
	ME::Ref<ME::Shader> shader;
	std::vector<ME::Mesh> grid;
	ME::Timer tim = ME::Timer("Overall");
	ParticleSystem m_ParticleSystem;
	ParticleProps m_Particle;
	
};
