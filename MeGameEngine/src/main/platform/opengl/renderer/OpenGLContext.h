#pragma once
#include "main/renderer/renderer/GraphicsContext.h"
struct GLFWwindow;
namespace ME {

	class OpenGLContext : public ME::GraphicsContext{

	public:
		OpenGLContext(GLFWwindow* window);
	
		virtual void swapBuffers() override;
		virtual void initialize() override;
	private:
		GLFWwindow* m_window;
	};
	
}