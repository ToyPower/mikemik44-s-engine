#include <hzpch.h>
#include "Renderer.h"
#include "RendererContent.h"
#include "main/platform/opengl/shaders/OpenGLShader.h"
namespace ME {
	Renderer::SceneData* Renderer::m_inform = new Renderer::SceneData;
	void Renderer::beginScene(Ref<Camera> cam) {
		m_inform->proj = cam->getViewProjection();
	}
	void Renderer::endScene() {

	}

	void Renderer::init() {
		RendererContent::init();
	}
	void Renderer::submit(const Ref<Shader>& shader, const Ref<VertexArray>& obj, Ref<Material>& mat, const bool& hasBindedAlready) {
		if (!hasBindedAlready) {
			shader->bind();
		}

		std::dynamic_pointer_cast<OpenGLShader>(shader)->setUniformMat4("u_mesh", glm::mat4(1.0f));
		std::dynamic_pointer_cast<OpenGLShader>(shader)->setUniformMat4("u_proj", m_inform->proj);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->setUniformVec4("u_color", mat->albeto);

		obj->bind();
		RendererContent::drawIndex(obj);
		obj->unbind();
		if (!hasBindedAlready) {
			shader->unbind();
		}
	}
	void Renderer::submit(const Ref<Shader>& shader, const Ref<VertexArray>& obj, const glm::mat4& transform, const Ref<Material> mat, const bool& hasBindedAlready) {
		if (!hasBindedAlready) {
			shader->bind();
		}
		
		std::dynamic_pointer_cast<OpenGLShader>(shader)->setUniformMat4("u_mesh", transform);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->setUniformMat4("u_proj", m_inform->proj);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->setUniformVec4("u_color", mat->albeto);
		
		obj->bind();
		RendererContent::drawIndex(obj);
		obj->unbind();
		if (!hasBindedAlready) {
			shader->unbind();
		}
	}

}