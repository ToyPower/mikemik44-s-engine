#include <hzpch.h>
#include "Buffers.h"
#include "main/platform/opengl/OpenGLVertex.h"
#include "main/renderer/Renderer.h"
namespace ME {



	IIndexBuffer* IIndexBuffer::create(uint32_t* vertices, uint32_t size) {
		switch (Renderer::getAPI()) {
		case RENDERAPI::none:
			ME_CORE_ASSORT(false, "Render API None is not supported!");
			return nullptr;
		case RENDERAPI::opengl:
			return new OpenGLIndexBuffer(vertices, size);
		}
		ME_CORE_ASSORT(false, "Unknown Render API");
		return nullptr;
	}

	VVertexBuffer* VVertexBuffer::create(float* vertices, uint32_t size) {
		switch (Renderer::getAPI()) {
		case RENDERAPI::none:
			ME_CORE_ASSORT(false, "Render API None is not supported!");
			return nullptr;
		case RENDERAPI::opengl:
			return new OpenGLVertexBuffer(vertices, size);
		}
		ME_CORE_ASSORT(false, "Unknown Render API");
		return nullptr;
	}

}