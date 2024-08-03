#pragma once
#include "glad/glad.h"
#include <glm/glm.hpp>
#include "main/renderer/shaders/Shader.h"
namespace ME {

	class OpenGLShader : public Shader {

	public:
		OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragSource, const bool& isFiles = false);
		OpenGLShader(const std::string& path);
		~OpenGLShader() override;
		virtual void bind() const override;
		virtual void unbind() const override;
		virtual const std::string& getName() { return m_name; }
		void setUniformMat4(const std::string& name, const glm::mat4& m) override;
		void setUniformMat3(const std::string& name, const glm::mat3& m) override;
		void setUniformFloat(const std::string& name, const float m) override;
		void setUniformVec2(const std::string& name, const glm::vec2& m) override;
		void setUniformVec3(const std::string& name, const glm::vec3& m) override;
		void setUniformVec4(const std::string& name, const glm::vec4& m) override;
		void setUniformBool(const std::string& name, const bool m) override;
		void setUniformInt(const std::string& name, const int m) override;

	private:
		std::unordered_map<GLenum, std::string> preProcess(const std::string& source);
		std::string readFile(const std::string& filePath);
		void compile(const std::unordered_map<GLenum, std::string>& sources);
		void applyProgram(GLuint program);

	private:
		uint32_t vshader, fshader, program;
		std::string m_name;
	};

}