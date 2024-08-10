#pragma once
#include <MeCore.h>
#include <main/layer/Layer.h>
#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <any>
#include <vector>
struct Pipe {
	float xpos = 0;
	float ceiling = 0;
	float floor = 0;
	float width = 0;
	float maxHeight = 0;
	float startHeight = 0;
	bool hasCounted = false;
};
struct Bird {
	float ypos = 0;
	float xpos = 0;
	float width = 0, height = 0;
};
class Flappy : public ME::Layer {
public:
	Flappy();
	~Flappy();
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
	Pipe createPipe();
	virtual void onGUIRender() override;

private:
	ME::Ref<ME::Texture> pipeTexture, pipeTopTexture, birdTexture;
	ME::Ref<ME::CameraController> cam;
	std::vector<Pipe> pipes;
	float accel = 0;
	float gravity = 7;
	float timer = 0;
	int counter2 = 0;
	float pipeToAdd = 17;
	float maxHoleSize = 1;
	float score = 0.0f;
	Bird bird;
	int counter = 0;
};
