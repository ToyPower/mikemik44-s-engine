#include <hzpch.h>
#include "Renderer.h"
#include "RendererContent.h"

namespace ME {
	Renderer::SceneData* Renderer::m_inform = new Renderer::SceneData;
	void Renderer::beginScene(Camera& cam) {
		m_inform->proj = cam.getViewProjection();
	}
	void Renderer::endScene() {

	}
	void Renderer::submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& obj, const glm::mat4& transform, const Material& mat) {
		shader->bind();
		shader->setUniformMat4("u_mesh", transform);
		shader->setUniformMat4("u_proj", m_inform->proj);
		shader->setUniformVec4("u_color", mat.albeto);
		obj->bind();
		RendererContent::drawIndex(obj);
		obj->unbind();
		shader->unbind();
	}

}