#include <hzpch.h>
#include "Buffers.h"
#include "main/platform/opengl/buffers/OpenGLVertex.h"
#include "main/renderer/renderer/Renderer.h"
#include "main/renderer/renderer/RendererApi.h"
namespace ME {



	IndexBuffer* IndexBuffer::create(uint32_t* vertices, uint32_t size) {
		switch (Renderer::getAPI()) {
		case RendererAPI::API::none:
			ME_CORE_ASSORT(false, "Render API None is not supported!");
			return nullptr;
		case RendererAPI::API::opengl:
			return new OpenGLIndexBuffer(vertices, size);
		}
		ME_CORE_ASSORT(false, "Unknown Render API");
		return nullptr;
	}

	VertexBuffer* VertexBuffer::create(float* vertices, uint32_t size) {
		switch (Renderer::getAPI()) {
		case RendererAPI::API::none:
			ME_CORE_ASSORT(false, "Render API None is not supported!");
			return nullptr;
		case RendererAPI::API::opengl:
			return new OpenGLVertexBuffer(vertices, size);
		}
		ME_CORE_ASSORT(false, "Unknown Render API");
		return nullptr;
	}

}