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
		virtual void setUniformMat4(const std::string& name, const glm::mat4& m) = 0;
		virtual void setUniformMat3(const std::string& name, const glm::mat3& m) = 0;
		virtual void setUniformFloat(const std::string& name, const float m) = 0;
		virtual void setUniformVec2(const std::string& name, const glm::vec2& m) = 0;
		virtual void setUniformVec3(const std::string& name, const glm::vec3& m) = 0;
		virtual void setUniformVec4(const std::string& name, const glm::vec4& m) = 0;
		virtual void setUniformBool(const std::string& name, const bool m) = 0;
		virtual void setUniformInt(const std::string& name, const int m) = 0;
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