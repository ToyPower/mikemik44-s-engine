#pragma once
#include "RendererApi.h"
#include "main/renderer/buffers/VertexArray.h"
#include "main/renderer/data/Camera.h"
#include "main/renderer/shaders/Shader.h"
namespace ME {

	class Renderer {

	public:
		static void beginScene(Camera& cam);
		static void endScene();
		static void submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& obj);

		static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }
	private:
		struct SceneData {
			glm::mat4 proj;
		};

		static SceneData* m_inform;
	};

}