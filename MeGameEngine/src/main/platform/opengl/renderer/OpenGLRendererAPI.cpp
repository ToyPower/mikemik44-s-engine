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
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glEnable(GL_CULL_FACE);
	}

	void OpenGLRendererAPI::setClearColor(glm::vec4& color) {
		glClearColor(color.r, color.g, color.b, color.a);
	}
	void OpenGLRendererAPI::drawIndex(const Ref<VertexArray>& obj) {

		glDrawElements(GL_TRIANGLES, obj->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);

	}

}