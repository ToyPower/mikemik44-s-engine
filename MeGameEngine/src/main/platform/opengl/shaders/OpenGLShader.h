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
		
		virtual void setUniformMat4(const std::string& name, const glm::mat4& m) override;
		virtual void setUniformMat3(const std::string& name, const glm::mat3& m) override;
		virtual void setUniformFloat(const std::string& name, const float m) override;
		virtual void setUniformVec2(const std::string& name, const glm::vec2& m) override;
		virtual void setUniformVec3(const std::string& name, const glm::vec3& m) override;
		virtual void setUniformVec4(const std::string& name, const glm::vec4& m) override;
		virtual void setUniformBool(const std::string& name, const bool m) override;
		virtual void setUniformInt(const std::string& name, const int m) override;

	
	private:
		uint32_t genShader(int type, const std::string& source);

	private:
		uint32_t vshader, fshader, program;

	};

}