#pragma once
#include <hzpch.h>
#include "camera.h"
#include "main/macro.h"
#include "main/dateentry/TimeStep.h"
#include "main/events/EventCaller.h"
namespace ME {

	class CameraController {

	public:
		CameraController(Ref<Camera>& cam, bool is2D = false, bool doRotation = true, bool allowYMovement = true) : cam(cam), is2D(is2D), allowYMovement(allowYMovement), doRotation(doRotation){}
		CameraController(Camera* cam, bool is2D = false, bool doRotation = true, bool allowYMovement = true) : cam(Ref<Camera>(cam)), is2D(is2D), allowYMovement(allowYMovement), doRotation(doRotation) {}

		Ref<Camera>& getCamera() {
			return cam;
		}
		void disableRotation() { this->doRotation = false; }
		void enableRotation() { this->doRotation = true; }
		void enableYMovement() { this->allowYMovement = true; }
		void disableYMovement() { this->allowYMovement = false; }
		void setMovementSpeed(float speed) { this->movementSpeed = speed; }
		void setRotationSpeed(float speed) { this->rotationSpeed = speed; }
		void update(TimeStep& timeStep);

		bool onEvent(Events& e);
		bool onMouseScrolled(Events& e);
		bool onWindowResized(Events& e);
	private:
		float zoom = 1;
		Ref<Camera> cam;
		bool is2D;
		float camSpeed = 1;
		float movementSpeed = 64;
		float rotationSpeed = 180;
		bool allowYMovement;
		bool doRotation;
	};

}
