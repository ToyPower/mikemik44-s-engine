#include <hzpch.h>
#include "Renderer.h"
#include "RendererContent.h"
#include "main/platform/opengl/shaders/OpenGLShader.h"
namespace ME {
	Renderer::SceneData* Renderer::m_inform = new Renderer::SceneData;
	void Renderer::beginScene(Camera& cam) {
		m_inform->proj = cam.getViewProjection();
	}
	void Renderer::endScene() {

	}
	void Renderer::submit(const Ref<Shader>& shader, const Ref<VertexArray>& obj, const glm::mat4& transform, const Ref<Material> mat) {
		shader->bind();
	
		std::dynamic_pointer_cast<OpenGLShader>(shader)->setUniformMat4("u_mesh", transform);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->setUniformMat4("u_proj", m_inform->proj);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->setUniformVec4("u_color", mat->albeto);
		
		obj->bind();
		RendererContent::drawIndex(obj);
		obj->unbind();
		shader->unbind();
	}

}