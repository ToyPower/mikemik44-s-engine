#include "hzpch.h"
#include "Application.h"

namespace ME {

	void Application::run() {

		while (m_running) {
			m_window->onUpdate();
		}

	}

	Application::Application() {
		m_window = std::unique_ptr<Window>(Window::create());
	}

	Application::~Application() {

	}

}