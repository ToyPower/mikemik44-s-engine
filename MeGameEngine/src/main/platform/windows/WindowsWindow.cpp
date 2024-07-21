#include "hzpch.h"
#include "WindowsWindow.h"

namespace ME {

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

	void WindowsWindow::init(const WindowProps& props) {
		m_data.title = props.title;
		m_data.width = props.width;	
		m_data.height = props.height;

		ME_CORE_INFO("Creating Window of size {0}x{1} with name {2}", m_data.width, m_data.height, m_data.title.c_str());
		if (!s_glfwinit) {
			
			int sucess = glfwInit();
			ME_CORE_ASSORT(sucess, "Could not initialize GLFW!")
			s_glfwinit = true;
		}

		m_window = glfwCreateWindow((int)m_data.width, (int)m_data.height, m_data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, &m_data);
		setVSync(true);
	}

	void WindowsWindow::shutdown() {
		glfwDestroyWindow(m_window);
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
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}

	bool WindowsWindow::isVSync() const {
		return m_data.vsync;
	}
}