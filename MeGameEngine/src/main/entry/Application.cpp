#include "hzpch.h"
#include "Application.h"
#include <glad/glad.h>
#include <main/Input.h>
#include "main/renderer/Buffers.h"
#include "main/renderer/VertexArray.h"
namespace ME {
#define FE_BIND(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application* Application::s_instance = nullptr;
	void Application::run() {
		
		while (m_running) {
			if (m_window != nullptr) {
				glClearColor(0.1f, 0.1f , 0.1f, 1);
				glClear(GL_COLOR_BUFFER_BIT);
				
				m_shader->bind();
				m_va->bind();
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
				
				m_va->unbind();
				m_shader->unbind();
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
		float vertices[3 * 3 + 3 * 4] = {
			-0.5f, -0.5f, 0.0f,  1, 0, 0,1, 
			0.0f, 0.5f, 0.0f,    0, 1, 0,1,
			0.5f, -0.5f, 0.0f,    0, 0, 1,1
		};
		BufferLayout layout = {

			{ShaderType::Vec3, "m_Position"},
			{ShaderType::Vec4, "m_color"},

		};
		
		uint32_t indices[3] = {
			0, 1, 2
		};
		
		//new OpenGLVertexBuffer((float*)vertices, 0, 0, 3, sizeof(vertices));
		bool start = false;
		m_va.reset(VertexArray::create());
	
		m_vbuffer.reset(VVertexBuffer::create(vertices, sizeof(vertices)));
		m_vbuffer->setLayout(layout);
		m_ibuffer.reset(IIndexBuffer::create(indices,3, sizeof(indices)));
		
		m_va->addVertexBuffer(m_vbuffer);
		m_va->setIndexBuffer(m_ibuffer);

		const std::string& a = R"(#version 410 core
			layout(location = 0) in vec3 position;
			layout(location = 1) in vec3 color1;
			out vec3 color;

			void main() {
				color = color1;
				gl_Position = vec4(position,1);
			}
		)";
		const std::string& b = R"(#version 410 core
			in vec3 color;
			
			void main() {
			
				gl_FragColor = vec4(color, 1);

			}
		)";

		m_shader.reset(new Shader(a,b));
	}

	Application::~Application() {
	}
}