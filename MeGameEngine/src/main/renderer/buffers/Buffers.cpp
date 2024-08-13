#include <hzpch.h>
#include "Buffers.h"
#include "main/platform/opengl/buffers/OpenGLVertex.h"
#include "main/renderer/renderer/main/Renderer.h"
#include "main/renderer/renderer/main/RendererContent.h"
namespace ME {



	Ref<IndexBuffer> IndexBuffer::create(uint32_t* vertices, uint32_t size) {
		switch (Renderer::getAPI()) {
		case RendererAPI::API::none:
			ME_CORE_ASSORT(false, "Render API None is not supported!");
			return nullptr;
		case RendererAPI::API::opengl:
			return Ref<IndexBuffer>(new OpenGLIndexBuffer(vertices, size));
		}
		ME_CORE_ASSORT(false, "Unknown Render API");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::create(float* vertices, uint32_t size) {
		switch (Renderer::getAPI()) {
		case RendererAPI::API::none:
			ME_CORE_ASSORT(false, "Render API None is not supported!");
			return nullptr;
		case RendererAPI::API::opengl:
			return Ref<VertexBuffer>(new OpenGLVertexBuffer(vertices, size));
		}
		ME_CORE_ASSORT(false, "Unknown Render API");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::create(uint32_t size) {
		switch (Renderer::getAPI()) {
		case RendererAPI::API::none:
			ME_CORE_ASSORT(false, "Render API None is not supported!");
			return nullptr;
		case RendererAPI::API::opengl:
			return Ref<VertexBuffer>(new OpenGLVertexBuffer(size));
		}
		ME_CORE_ASSORT(false, "Unknown Render API");
		return nullptr;
	}

}