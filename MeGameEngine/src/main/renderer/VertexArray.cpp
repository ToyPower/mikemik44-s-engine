#include <hzpch.h>
#include "VertexArray.h"
#include "Renderer.h"
#include "main/platform/opengl/OpenGLVertexArray.h"
namespace ME {

	VertexArray* VertexArray::create() {
	switch (Renderer::getAPI()) {
		case RENDERAPI::none:
			ME_CORE_ASSORT(false, "Render API None is not supported!");
			return nullptr;
		case RENDERAPI::opengl:
			return new OpenGLVertexArray();
		}
		ME_CORE_ASSORT(false, "Unknown Render API");
		return nullptr;
	}

}