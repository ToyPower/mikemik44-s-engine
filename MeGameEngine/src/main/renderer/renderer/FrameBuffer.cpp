#include <hzpch.h>
#include "FrameBuffer.h"
#include "main/renderer/renderer/main/Renderer.h"
#include "main/platform/opengl/buffers/OpenGLFrameBuffer.h"
namespace ME {

	Ref<FrameBuffer> FrameBuffer::create(const FrameBufferSpecial& spec) {
		switch (Renderer::getAPI()) {
		case RendererAPI::API::none:
			ME_CORE_ASSORT(false, "Render API None is not supported!");
			return nullptr;
		case RendererAPI::API::opengl:
			return Ref<FrameBuffer>(new OpenGLFrameBuffer(spec));
		}
		ME_CORE_ASSORT(false, "Unknown Render API");
		return nullptr;
	}

}