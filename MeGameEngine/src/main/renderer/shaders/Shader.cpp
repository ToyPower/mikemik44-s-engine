#include <hzpch.h>
#include "Shader.h"
#include "main/renderer/renderer/main/Renderer.h"
#include "main/platform/opengl/shaders/OpenGLShader.h"
namespace ME {
	Ref<Shader> Shader::create(const std::string& name, const std::string& vertexSource, const std::string& fragSource, const bool& isFiles) {
		
		switch (Renderer::getAPI()) {
		case RendererAPI::API::none:
			ME_CORE_ASSORT(false, "Render API None is not supported!");
			return nullptr;
		case RendererAPI::API::opengl:
			return Ref<Shader>(new OpenGLShader(name,vertexSource, fragSource, isFiles));
		
		}
		ME_CORE_ASSORT(false, "Unknown Render API");
		return nullptr;
	}

	Ref<Shader> Shader::create(const std::string& path) {
		
		switch (Renderer::getAPI()) {
		case RendererAPI::API::none:
			ME_CORE_ASSORT(false, "Render API None is not supported!");
			return nullptr;
		case RendererAPI::API::opengl:
			return Ref<Shader>(new OpenGLShader(path));
		}
		ME_CORE_ASSORT(false, "Unknown Render API");
		return nullptr;
	}



	void ShaderLibrary::add(const Ref<Shader>& shader) {
		add(shader->getName(), shader);
	}

	void ShaderLibrary::add(const std::string& name, const Ref<Shader>& shader) {
		
		ME_CORE_ASSORT(!exists(name), "Shader already declared!");
		this->shaders[name] = shader;
	}

	Ref<Shader> ShaderLibrary::load(const std::string& filePath) {
		Ref<Shader> shader = Shader::create(filePath);
		add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::load(const std::string& name, const std::string& filePath) {
		Ref<Shader> shader = Shader::create(filePath);
		
		add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::get(const std::string& name) {
		ME_CORE_ASSORT(exists(name), "Shader doesnt exists!");
		return this->shaders[name];
	}

	bool ShaderLibrary::exists(const std::string& name) {
		return this->shaders.find(name) != this->shaders.end();
	}

}