#pragma once
#include <glm/glm.hpp>
#include <unordered_map>
namespace ME {

	class Shader {

	public:
		virtual ~Shader() {}
		virtual void bind() const = 0;
		virtual void unbind() const = 0;
		virtual const std::string& getName() = 0;
		
		static Ref<Shader> create(const std::string& name, const std::string& vertexSource, const std::string& fragSource, const bool& isFiles = false);
		static Ref<Shader> create(const std::string& path);
	};

	class ShaderLibrary {
	public:
		void add(const Ref<Shader>& shader);
		void add(const std::string& name, const Ref<Shader>& shader);
		Ref<Shader> load(const std::string& filePath);
		Ref<Shader> load(const std::string& name, const std::string& filePath);
		Ref<Shader> get(const std::string& name);
		bool exists(const std::string& name);
	private:
		std::unordered_map<std::string, Ref<Shader>> shaders;
	};

}