#pragma once
#include "main/renderer/renderer/apistuff/RendererApi.h"
#include "main/renderer/buffers/VertexArray.h"
#include <glm/glm.hpp>
namespace ME {

	class RendererContent {

	public:
		inline static void init() {
			s_api->init();
		}

		inline static void setDepthEnabled(const bool& state) {
			s_api->setDepthEnabled(state);
		}

		inline static void drawIndex(const Ref<VertexArray>& arr) {
			s_api->drawIndex(arr);
		}
		inline static void clear() {
			s_api->clear();
		}

		inline static void setClearColor(float r = 0, float g = 0, float b = 0, float a = 0) {
			s_api->setClearColor(r, g, b, a);
		}

		inline static void setClearColor(glm::vec4& color = glm::vec4(0,0,0,1)) {
			s_api->setClearColor(color);
		}
	
	private:
		static RendererAPI* s_api;
	};
	
}