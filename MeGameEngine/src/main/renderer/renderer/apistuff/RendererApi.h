#pragma once
#include <hzpch.h>
#include <glm/glm.hpp>
#include "main/renderer/buffers/VertexArray.h"
namespace ME {

	class RendererAPI {

	public:
		enum class API {

			none = 0, opengl = 1

		};
	public:
		virtual void init() = 0;
		virtual void clear() = 0;
		virtual void setClearColor(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f) = 0;
		virtual void setClearColor(glm::vec4& clearColor  = glm::vec4(0,0,0,1)) = 0;
		virtual void drawIndex(const Ref<VertexArray>& arr) = 0;
		inline static API getAPI() { return m_api; }
	private:
		static API m_api;
	};
}