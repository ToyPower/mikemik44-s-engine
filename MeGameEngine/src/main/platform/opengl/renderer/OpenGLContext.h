#pragma once
#include "main/renderer/renderer/GraphicsContext.h"
struct GLFWwindow;
namespace ME {

	class OpenGLContext : public ME::GraphicsContext{

	public:
		OpenGLContext(GLFWwindow* window);
		void swapBuffers() override;
		void initialize() override;
	private:
		GLFWwindow* m_window;
	};
	
}