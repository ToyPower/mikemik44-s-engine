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
	void Renderer::submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& obj) {
		shader->bind();
		shader->setUniformMat4("u_proj", m_inform->proj);
		obj->bind();
		RendererContent::drawIndex(obj);
		obj->unbind();
		shader->unbind();
	}

}