#include <hzpch.h>
#include "Flappy.h"

Flappy::Flappy() : Layer("Flappy Bird"), cam(new ME::CameraController(new ME::OthrographicCamera((float)ME::Application::getInstance().getWidth() / ME::Application::getInstance().getHeight()), true)) {

}

Flappy::~Flappy() {

}

Pipe Flappy::createPipe() {
	float width = (float)ME::Application::getInstance().getWidth();
	float height = (float)ME::Application::getInstance().getHeight();
	Pipe pipe;
	pipe.xpos = 1;
	float hole = ME::Rand::Float(0.185, maxHoleSize);
	pipe.ceiling = ME::Rand::Float(0.02f,2-hole);
	
	
	pipe.startHeight = -1;
	
	pipe.floor = pipe.startHeight+pipe.ceiling+hole;
	pipe.maxHeight = 1 - pipe.floor;
	pipe.width = 50/width;
	return pipe;
}

void Flappy::onAttach() {
	float width = (float)ME::Application::getInstance().getWidth();
	float height = (float)ME::Application::getInstance().getHeight();
	bird = Bird();
	bird.xpos = -1+10/width;
	bird.ypos = 0;
	bird.width = 0.06f;
	bird.height = 0.06f;
	pipes.push_back(createPipe());
	ME::Renderer2D::init();
	pipeTexture = ME::Texture2D::create("assets/textures/pipe.png");
	birdTexture = ME::Texture2D::create("assets/textures/flappy.png");
	pipeTopTexture = ME::Texture2D::create("assets/textures/pipe_Top.png");
	
}

void Flappy::onDetach() {
	ME::Renderer2D::shutdown();
}

bool collide(float x, float width, float chk, float chkSize) {
	if (x <= chk && x + width >= chk) {
		return true;
	}
	else if (chk <= x && chk + chkSize >= x) {
		return true;
	}
	return false;
}

void Flappy::onUpdate(ME::TimeStep step) {

	for (int i = pipes.size()-1; i >= 0;i--) {
		Pipe& p = pipes[i];
		p.xpos -= step.getTime() / 4;
		if (p.xpos < -1.5f) {
			pipes.erase(std::next(pipes.begin(), i));
		}

	}
	accel = accel + gravity * step.getTime();
	if (ME::Input::isKeyPress(ME_KEY_SPACE)) {
	
		accel = accel - 14*step.getTime();
		
	}
	
	accel = std::clamp(accel, -1.0f, 1.0f);
	
	bird.ypos += accel * step.getTime();
	accel *= 0.95f;
	counter++;
	if (counter > pipeToAdd * 60) {
		pipes.push_back(createPipe());
		counter = 0;
	}
	if (counter2 > 60 * 30) {
		counter2 = 0;
		pipeToAdd = std::max(6.0f, pipeToAdd - step.getTime());
		maxHoleSize = std::max(0.25f, maxHoleSize / 1.25f);
	}

	for (Pipe& p : pipes) {
		if (collide(p.xpos, p.width, bird.xpos, bird.width)) {
			if (collide(p.startHeight, p.ceiling, bird.ypos, bird.height)) {
				bird.ypos = 0;
				pipes.clear();
				pipes.push_back(createPipe());
				pipeToAdd = 30;
				maxHoleSize = 0.75;
				counter = 0;
				counter2 = 0;
				score = 0;
				p.hasCounted = false;
				return;
			}
			else if (collide(p.floor, 2, bird.ypos, bird.height)) {
				bird.ypos = 0;
				pipes.clear();
				pipes.push_back(createPipe());
				pipeToAdd = 30;
				maxHoleSize = 0.75;
				counter = 0;
				counter2 = 0;
				score = 0;
				p.hasCounted = false;
				return;
			}
			
			p.hasCounted = true;
		} 
		else {
			if (p.hasCounted) {
				p.hasCounted = false;
				score++;
			}
		}
	}

}

void Flappy::onRender() {
	ME::Renderer2D::clear({0.2f, 0.12f, 0.6f, 1});
	ME::Renderer2D::beginScene(this->cam->getCamera());
	
	for (Pipe& p : pipes) {
		
		ME::Renderer2D::drawQuad({ p.xpos, p.floor}, { p.width, p.maxHeight }, pipeTexture);
		ME::Renderer2D::drawQuad({ p.xpos, p.startHeight }, { p.width, p.ceiling }, pipeTopTexture);
		
	}
	ME::Renderer2D::drawQuad({ bird.xpos, bird.ypos }, { bird.width, bird.height }, birdTexture);
	ME::Renderer2D::endScene();

}

void Flappy::onGUIRender() {
	ImGui::Begin("Game Score");
	
	ImGui::Text("Score: %.0f", (float)score);
	ImGui::End();
}
