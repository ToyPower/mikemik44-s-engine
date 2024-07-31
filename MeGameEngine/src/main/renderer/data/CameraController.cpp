#include <hzpch.h>
#include "CameraController.h"
#include "main/Input.h"
#include "main/KeyCodes.h"
namespace ME {

	bool CameraController::onEvent(Events& e) {
		if (e.name() == "windowMouseScroll") {
			return onMouseScrolled(e);
		}
		else if (e.name() == "windowResize") {
			return onWindowResized(e);
		}
		return true;
	}

	bool CameraController::onWindowResized(Events& e) {
		cam->onResize((float)std::any_cast<int>(e.getParam("width")), (float)std::any_cast<int>(e.getParam("height")));
		return true;
	}

	bool CameraController::onMouseScrolled(Events& e) {

		return true;
	}

	void CameraController::update(TimeStep& step) {

		float offset = 1;
		float mov = step  * 8;
		float rot = step * 180;
		if (ME::Input::isKeyPress(ME_KEY_W)) {
			cam->move(cam->getForward(), 0.1 * offset * mov);
		}

		if (ME::Input::isKeyPress(ME_KEY_Q)) {
			cam->rotate({ -1,0,0 }, 2 * offset * rot);
		}

		if (ME::Input::isKeyPress(ME_KEY_E)) {
			cam->rotate({ 1,0,0 }, 2 * offset * rot);
		}
		if (ME::Input::isKeyPress(ME_KEY_S)) {
			cam->move(cam->getBackward(), 0.1 * offset * mov);
		}
		if (ME::Input::isKeyPress(ME_KEY_A)) {
			cam->move(cam->getLeft(), 0.1 * offset * mov);
		}
		if (ME::Input::isKeyPress(ME_KEY_D)) {
			cam->move(cam->getRight(), 0.1 * offset * mov);
		}

	}

}