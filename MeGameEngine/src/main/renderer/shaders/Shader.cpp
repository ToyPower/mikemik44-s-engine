#include <hzpch.h>
#include "Shader.h"
#include "main/renderer/renderer/Renderer.h"
#include "main/platform/opengl/shaders/OpenGLShader.h"
namespace ME {
	Shader* Shader::create(const std::string& vertexSource, const std::string& fragSource) {
		switch (Renderer::getAPI()) {
		case RendererAPI::API::none:
			ME_CORE_ASSORT(false, "Render API None is not supported!");
			return nullptr;
		case RendererAPI::API::opengl:
			return new OpenGLShader(vertexSource, fragSource);
		}
		ME_CORE_ASSORT(false, "Unknown Render API");
		return nullptr;
	}

}