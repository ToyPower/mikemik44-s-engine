#pragma once
#include <hzpch.h>
#include "camera.h"
#include "main/macro.h"
#include "main/dateentry/TimeStep.h"
#include "main/events/EventCaller.h"
namespace ME {

	class CameraController {

	public:
		CameraController(Ref<Camera>& cam) : cam(cam) {}
		CameraController(Camera* cam) : cam(Ref<Camera>(cam)) {}

		Ref<Camera>& getCamera() {
			return cam;
		}

		void update(TimeStep& timeStep);

		bool onEvent(Events& e);
		bool onMouseScrolled(Events& e);
		bool onWindowResized(Events& e);
	private:
		Ref<Camera> cam;

	};

}
