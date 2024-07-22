#include <hzpch.h>
#include "WindowsInput.h"
#include <GLFW/glfw3.h>
#include "main/entry/Application.h"
namespace ME {
	Input* Input::s_instance = new WindowsInput();
	bool WindowsInput::isKeyPressPoll(int keycode) {

		auto window = static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNativeWindow());
		auto state = glfwGetKey(window, keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::isKeyReleasePoll(int keycode) {

		auto window = static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNativeWindow());
		auto state = glfwGetKey(window, keycode);

		return state == GLFW_RELEASE;
	}

	bool WindowsInput::isButtonPressPoll(int keycode) {

		auto window = static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNativeWindow());
		auto state = glfwGetMouseButton(window, keycode);

		return state == GLFW_PRESS;
	}

	bool WindowsInput::isButtonReleasePoll(int keycode) {

		auto window = static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNativeWindow());
		auto state = glfwGetMouseButton(window, keycode);

		return state == GLFW_RELEASE;
	}

	float WindowsInput::getMouseXPoll() {
		auto [x, y] = getMousePosPoll();
		return x;
	}
	
	std::pair<float,float> WindowsInput::getMousePosPoll() {
		auto window = static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNativeWindow());
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return  { (float)x, (float)y };
	}

	float WindowsInput::getMouseYPoll() {
		auto [x, y] = getMousePosPoll();
		return y;
	}
}