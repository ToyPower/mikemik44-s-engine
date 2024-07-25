#include <hzpch.h>
#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>
namespace ME {
	uint32_t Shader::genShader(int type, const std::string& source) {
		uint32_t shader = glCreateShader(type);

		// Get strings for glShaderSource.
		const GLchar* source1 = (const GLchar*)source.c_str();
		glShaderSource(shader, 1, &source1, 0);

		glCompileShader(shader);

		GLint isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

			// Provide the infolog in whatever manor you deem best.
			// Exit with failure.
			glDeleteShader(shader); // Don't leak the shader.
			ME_CORE_ERROR("{0}", errorLog.data());
			ME_CORE_ASSORT(false, "Shader ({0}) error: Shader Failed to build!", type);
			return shader;
		}
		return shader;
	}
	Shader::Shader(const std::string& vertexSource, const std::string& fragSource) {
		vshader = genShader(GL_VERTEX_SHADER, vertexSource);
		fshader = genShader(GL_FRAGMENT_SHADER, fragSource);
		program = glCreateProgram();
		glAttachShader(program, vshader);
		glAttachShader(program, fshader);
		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			glDeleteShader(vshader);
			glDeleteShader(fshader);

			// Use the infoLog as you see fit.
			ME_CORE_ERROR("{0}", infoLog.data());
			ME_CORE_ASSORT(false, "Could not build program!");
			// In this simple program, we'll just leave
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(program, vshader);
		glDetachShader(program, fshader);

	}

	Shader::~Shader() {
		glDeleteProgram(program);
	}

	void Shader::bind() const {
		glUseProgram(program);
	}

	void Shader::unbind() const {
		glUseProgram(0);
	}

	void Shader::setUniformMat4(const std::string& name, const glm::mat4& m) {
		GLint loc = glGetUniformLocation(program, name.c_str());
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(m));
	}
	void Shader::setUniformMat3(const std::string& name, const glm::mat3& m) {
		GLint loc = glGetUniformLocation(program, name.c_str());
		glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(m));
	}
	void Shader::setUniformFloat(const std::string& name, const float m) {
		GLint loc = glGetUniformLocation(program, name.c_str());
		glUniform1f(loc, m);
	}
	void Shader::setUniformVec2(const std::string& name, const glm::vec2& m) {
		GLint loc = glGetUniformLocation(program, name.c_str());
		glUniform2f(loc, m.x, m.y);
	}
	void Shader::setUniformVec3(const std::string& name, const glm::vec3& m) {
		GLint loc = glGetUniformLocation(program, name.c_str());
		glUniform3f(loc, m.x, m.y, m.z);
	}
	void Shader::setUniformVec4(const std::string& name, const glm::vec4& m) {
		GLint loc = glGetUniformLocation(program, name.c_str());
		glUniform4f(loc,m.x, m.y,m.z, m.w);
	}
	void Shader::setUniformBool(const std::string& name, const bool m) {
		GLint loc = glGetUniformLocation(program, name.c_str());
		glUniform1i (loc, m ? 1 : 0);
	}
	void Shader::setUniformInt(const std::string& name, const int m) {
		GLint loc = glGetUniformLocation(program, name.c_str());
		glUniform1i(loc,m);
	}

}