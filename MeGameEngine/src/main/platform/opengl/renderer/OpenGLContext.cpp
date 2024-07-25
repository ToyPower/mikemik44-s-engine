#include <hzpch.h>
#include "OpenGLContext.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
namespace ME {

	OpenGLContext::OpenGLContext(GLFWwindow* window)  : m_window(window){
		
	}

	void OpenGLContext::initialize() {
		glfwMakeContextCurrent(m_window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ME_CORE_ASSORT(status, "Could not load glad!");
	}

	void OpenGLContext::swapBuffers() {
		
		glfwSwapBuffers(m_window);
	}

}