#include "hzpch.h"
#include "WindowsWindow.h"
#include "WindowsInput.h"
#include "main/input/Input.h"
#include "main/platform/opengl/renderer/OpenGLContext.h"
#include "glfw/glfw3.h"
namespace ME {

	void errorcallback(int error, const char* desc) {
		ME_CORE_ERROR("GLFW Error [{0}]: {1}", error, desc);
	}
	static bool s_glfwinit = false;
	Window* Window::create(const WindowProps& props) {
		return new WindowsWindow(props);
	}

	void WindowsWindow::assignEvents() {

	}

	WindowsWindow::WindowsWindow(const WindowProps& props) {
		init(props);
	}

	WindowsWindow::~WindowsWindow() {
		shutdown();
	}
	static WindowsWindow* inst;
	void WindowsWindow::init(const WindowProps& props) {
	
		m_data.title = props.title;
		m_data.width = props.width;	
		m_data.height = props.height;
		
		
		glfwSetErrorCallback(&errorcallback);
		ME_CORE_INFO("Creating Window of size {0}x{1} with name {2}", m_data.width, m_data.height, m_data.title.c_str());
		if (!s_glfwinit) {
			
			int sucess = glfwInit();
			ME_CORE_ASSORT(sucess, "Could not initialize GLFW!")
			s_glfwinit = true;
		}

		m_window = glfwCreateWindow((int)m_data.width, (int)m_data.height, m_data.title.c_str(), nullptr, nullptr);
		m_context = new OpenGLContext(m_window);
		m_context->initialize();
		
		glfwSetWindowUserPointer(m_window, &m_data);
		setVSync(true);
		inst = this;
		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* win, int width, int height) {
			WindowsWindow* in1 = inst;
			if (width == 0 || height == 0) {
				in1->minimized = true;
				return;
			}
			else {
				in1->minimized = false;

			}
			Events& e1 = Events("windowResize");
			
			e1.putParam("Window", win);
				e1.putParam("width", width);
				e1.putParam("height", height);
				WindowProps& props = *(WindowProps*)glfwGetWindowUserPointer(win);
				e1.putParam("oldWidth", props.width);
				e1.putParam("oldHeight", props.height);
				ME_CORE_INFO("{0}, {1}", width, height);
				if (!EventCaller::callEvent(e1)) {
					glfwSetWindowSize(win, props.width, props.height);
				}
				else {
					
					glViewport(0, 0, width, height);
					props.width = width;
					props.height = height;
				}
			});
		glfwSetWindowCloseCallback(m_window, [](GLFWwindow * win) {
			Events& e1 = Events("windowShutdown");
			e1.putParam("window", win);
			EventCaller::callEvent(e1);
		});
		
		glfwSetCharCallback(m_window, [](GLFWwindow* window, unsigned int key) {
			Events& e1 = Events("windowKeyTyped");
			e1.putParam("window", window);
			e1.putParam("character", (int)key);
			EventCaller::callEvent(e1);
		});
		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mod) {
			const char* name = nullptr;
			switch (action) {
				case GLFW_PRESS: {
					name = "windowKeyPress";
					break;
				}
				case GLFW_RELEASE: {
					name = "windowKeyRelease";
					break;
				}
				case GLFW_REPEAT: {
					name = "windowKeyDown";
					break;
				default:
					name = "windowKeyChange";
					break;
				}
			}
			Events& e1 = Events(name);
				e1.putParam("window", window);
				e1.putParam("key", key);
				e1.putParam("keycode", scancode);
				e1.putParam("mod", mod);
				EventCaller::callEvent(e1);
		});

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* win, int button, int action, int mod) {
			const char* name = nullptr;
			switch (action) {
				case GLFW_PRESS: {
					name = "windowButtonPress";
					break;
				}
				case GLFW_RELEASE: {
					name = "windowButtonRelease";
					break;
				}
				default: {
					name = "WindowButton";
				}
			}
			Events& e1 = Events(name);
			e1.putParam("window", win);
			e1.putParam("button", button);
			e1.putParam("mod", mod);
			EventCaller::callEvent(e1);
		});

		glfwSetScrollCallback(m_window, [](GLFWwindow* win, double xoff, double yoff) {
			Events& e1 = Events("windowMouseScroll");
			e1.putParam("window", win);
			e1.putParam("xoff", xoff);
			e1.putParam("yoff", yoff);
			EventCaller::callEvent(e1);
			});

		glfwSetCursorPosCallback(m_window, [](GLFWwindow* win, double x, double y) {
			Events& e1 = Events("windowMouseMove");
			e1.putParam("window", win);
			e1.putParam("x", x);
			e1.putParam("y", y);
			EventCaller::callEvent(e1);
			});
	}

	void WindowsWindow::shutdown() {
		
		glfwDestroyWindow(m_window);
		m_window = nullptr;
		glfwTerminate();
		s_glfwinit = false;
	
		
	}

	void WindowsWindow::setVSync(bool enabled) {
		if (enabled) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}
		m_data.vsync = enabled;
	}

	void WindowsWindow::onUpdate() {
		if (m_window != nullptr) {
			glfwPollEvents();
		}
		if (m_window != nullptr && !minimized) {
			m_context->swapBuffers();
		}
	}

	bool WindowsWindow::isVSync() const {
		return m_data.vsync;
	}

}