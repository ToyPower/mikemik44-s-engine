#include <hzpch.h>
#include "Texture.h"

#include "main/renderer/renderer/main/Renderer.h";
#include "main/platform/opengl/texture/OpenGLTexture.h"
namespace ME {

	Ref<Texture2D> Texture2D::create(const std::string& filePath) {
		switch (Renderer::getAPI()) {
		case RendererAPI::API::none:
			ME_CORE_ASSORT(false, "Render API None is not supported!");
			return nullptr;
		case RendererAPI::API::opengl:
			return std::make_shared<OpenGLTexture>(filePath);
		}
		ME_CORE_ASSORT(false, "Unknown Render API");
		return nullptr;
	}

}

