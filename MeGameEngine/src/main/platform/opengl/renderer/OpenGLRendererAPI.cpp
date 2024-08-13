#include <hzpch.h>
#include "OpenGLRendererAPI.h"
#include <glad/glad.h>
namespace ME {

	void OpenGLRendererAPI::clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void OpenGLRendererAPI::setClearColor(float r, float g, float b, float a) {
		glClearColor(r, g, b, a);
	}

	void OpenGLRendererAPI::init() {
		if (depthEnable) {
			glEnable(GL_DEPTH_TEST);
		}
		//glDepthFunc(GL_LESS);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
	}

	void OpenGLRendererAPI::setDepthEnabled(const bool& state) {
		this->depthEnable = state;
		if (depthEnable) {
			glEnable(GL_DEPTH_TEST);
		}
		else {
			glDisable(GL_DEPTH_TEST);
		}
	}

	void OpenGLRendererAPI::setClearColor(glm::vec4& color) {
		glClearColor(color.r, color.g, color.b, color.a);
	}
	void OpenGLRendererAPI::drawIndex(const Ref<VertexArray>& obj, uint32_t count) {
		
		if (count == 0) {
			count = obj->getIndexBuffer()->getCount();
		}
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	
	}

}