#pragma once
#include "main/renderer/renderer/apistuff/RendererApi.h"
#include "main/renderer/buffers/VertexArray.h"
#include "main/renderer/data/camera/Camera.h"
#include "main/renderer/shaders/Shader.h"
#include "main/renderer/data/meshdata/Material.h"
#include "main/renderer/data/meshdata/Mesh.h"
namespace ME {

	class Renderer {

	public:
		static void beginScene(Ref<Camera> cam);
		static void endScene();
		static void submit(const Ref<Shader>& shader, const Ref<VertexArray>& obj, const glm::mat4& transform = glm::mat4(1.0f), const Ref<Material> mat = Ref<Material>(), const bool& hasBindedAlready = false);
		static void init();
		static void submit(const Ref<Shader>& shader, const Ref<Mesh>& obj, const bool& hasBindedAlready = false) {
			if (!hasBindedAlready) {
				shader->bind();
			}
			if (obj->getMaterial()->tex != nullptr) {
				obj->getMaterial()->tex->bind();
			}
			Renderer::submit(shader, obj->getVertexArray(), obj->getTransform().getMeshMatrix(), obj->getMaterial(), true);
			if (obj->getMaterial()->tex != nullptr) {
				obj->getMaterial()->tex->unbind();
			}
			if (!hasBindedAlready) {
				shader->unbind();
			}
		}

		static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }
	private:
		struct SceneData {
			glm::mat4 proj;
		};

		static SceneData* m_inform;
	};

}