#pragma once
#include "RendererApi.h"
#include "main/renderer/buffers/VertexArray.h"
#include "main/renderer/data/Camera.h"
#include "main/renderer/shaders/Shader.h"
#include "main/renderer/data/Material.h"
#include "main/renderer/data/Mesh.h"
namespace ME {

	class Renderer {

	public:
		static void beginScene(Camera& cam);
		static void endScene();
		static void submit(const Ref<Shader>& shader, const Ref<VertexArray>& obj, const glm::mat4& transform = glm::mat4(1.0f), const Ref<Material> mat = Ref<Material>());
		static void submit(const Ref<Shader>& shader, Mesh& obj) {

			Renderer::submit(shader, obj.getVertexArray(), obj.getTransform().getMeshMatrix(), obj.getMaterial());

		}

		static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }
	private:
		struct SceneData {
			glm::mat4 proj;
		};

		static SceneData* m_inform;
	};

}