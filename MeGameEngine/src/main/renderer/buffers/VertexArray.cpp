#include <hzpch.h>
#include "VertexArray.h"
#include "main/renderer/renderer/Renderer.h"
#include "main/platform/opengl/buffers/OpenGLVertexArray.h"
namespace ME {

	VertexArray* VertexArray::create() {
	switch (Renderer::getAPI()) {
		case RendererAPI::API::none:
			ME_CORE_ASSORT(false, "Render API None is not supported!");
			return nullptr;
		case RendererAPI::API::opengl:
			return new OpenGLVertexArray();
		}
		ME_CORE_ASSORT(false, "Unknown Render API");
		return nullptr;
	}

}