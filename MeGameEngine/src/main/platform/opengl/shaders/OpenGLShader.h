#pragma once
#include "glad/glad.h"
#include <glm/glm.hpp>
#include "main/renderer/shaders/Shader.h"
namespace ME {

	class OpenGLShader : public Shader {

	public:
		OpenGLShader(const std::string& vertexSource, const std::string& fragSource);
		~OpenGLShader() override;
		virtual void bind() const override;
		virtual void unbind() const override;
		
		void setUniformMat4(const std::string& name, const glm::mat4& m);
		void setUniformMat3(const std::string& name, const glm::mat3& m);
		void setUniformFloat(const std::string& name, const float m);
		void setUniformVec2(const std::string& name, const glm::vec2& m);
		void setUniformVec3(const std::string& name, const glm::vec3& m);
		void setUniformVec4(const std::string& name, const glm::vec4& m);
		void setUniformBool(const std::string& name, const bool m);
		void setUniformInt(const std::string& name, const int m);

	
	private:
		uint32_t genShader(int type, const std::string& source);

	private:
		uint32_t vshader, fshader, program;

	};

}