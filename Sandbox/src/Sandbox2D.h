#pragma once
#include <MeCore.h>
#include <main/layer/Layer.h>
#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <any>
#include <vector>

class Sandbox2D : public ME::Layer{

public:
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

	//TEMP
	ME::Ref<ME::Shader> shader;
	std::vector<ME::Mesh> grid;
};
