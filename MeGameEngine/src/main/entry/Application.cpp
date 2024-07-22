#include "hzpch.h"
#include "Application.h"
#include <glad/glad.h>
#include <main/Input.h>

namespace ME {
#define FE_BIND(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application* Application::s_instance = nullptr;
	void Application::run() {
		
		while (m_running) {
			if (m_window != nullptr) {
				glClearColor(1, 0, 1, 1);
				glClear(GL_COLOR_BUFFER_BIT);
				for (auto layer : m_st) {
					layer->onUpdate();
					layer->onRender();
				}
				m_imguilayer->begin();
				for (auto layer : m_st) {
					layer->onGUIRender();
				}
				m_imguilayer->end();
				m_window->onUpdate();
			}
			
		}

	}

	void Application::pushLayer(Layer* layer) {
		m_st.pushLayer(layer);
		layer->onAttach();
	}

	void Application::pushOverlay(Layer* layer) {
		m_st.pushOverlay(layer);
		layer->onAttach();
	}

	bool Application::onEvent(Events& ee) {
		
		if (strcmp(ee.name(), "windowShutdown") == 0) {
			bool suc = true;
			for (auto it = m_st.end(); it != m_st.begin();) {

				if (!(*--it)->onEvent(ee)) {
					suc = false;
				}
				if (ee.handled) {
					break;
				}

			}
			this->m_running = false;
			return true;
		}
		else {
			bool suc = true;
			for (auto it = m_st.end(); it != m_st.begin();) {
				if (!(*--it)->onEvent(ee)) {
					suc = false;
				}
				if (ee.handled) {
					break;
				}
			}
			return suc;
		}
		
	}

	Application::Application() {
		s_instance = this;
		m_window = std::unique_ptr<Window>(Window::create());
		EventCaller::addEventListener(FE_BIND(onEvent), "window*");
		m_imguilayer = new ImGuiLayer();
		pushOverlay(m_imguilayer);
	}

	Application::~Application() {
	}
}