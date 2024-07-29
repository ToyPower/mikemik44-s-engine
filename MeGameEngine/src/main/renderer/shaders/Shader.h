#pragma once
#include <glm/glm.hpp>
namespace ME {

	class Shader {

	public:
		virtual ~Shader() {}
		virtual void bind() const = 0;
		virtual void unbind() const = 0;
		
		virtual void setUniformMat4(const std::string& name, const glm::mat4& m) = 0;
		virtual void setUniformMat3(const std::string& name, const glm::mat3& m) = 0;
		virtual void setUniformFloat(const std::string& name, const float m) = 0;
		virtual void setUniformVec2(const std::string& name, const glm::vec2& m) = 0;
		virtual void setUniformVec3(const std::string& name, const glm::vec3& m) = 0;
		virtual void setUniformVec4(const std::string& name, const glm::vec4& m) = 0;
		virtual void setUniformBool(const std::string& name, const bool m) = 0;
		virtual void setUniformInt(const std::string& name, const int m) = 0;
		
		static Shader* create(const std::string& vertexSource, const std::string& fragSource);
	};

}