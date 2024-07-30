#include <hzpch.h>
#include "OpenGLShader.h"

#include <glm/gtc/type_ptr.hpp>
#include <fstream>

namespace ME {

	static GLenum convertToGLType(const std::string& type) {
		
		if (type == "frag" || type == "pixel") {
			return GL_FRAGMENT_SHADER;
		}
		else if (type == "vertex") {
			return GL_VERTEX_SHADER;
		}
		else if (type == "geometry") {
			return GL_GEOMETRY_SHADER;
		}
		ME_CORE_ASSORT(false, "Unknown Shader Type {0}", type);
	}

	OpenGLShader::OpenGLShader(const std::string& path){		
		
		std::string source = readFile(path);
		std::unordered_map<GLenum, std::string> data = preProcess(source);
		compile(data);
		auto last = path.find_last_of("/\\");
		last = last == std::string::npos ? 0 : last + 1;
		auto ld = path.rfind('.');
		auto count = ld == std::string::npos ? path.size() - last : ld - last;
		m_name = path.substr(last, count);
	}

	void OpenGLShader::applyProgram(GLuint program) {
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
			ME_CORE_INFO("ERROR");
			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength+1);
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
	}

	void OpenGLShader::compile(const std::unordered_map<GLenum, std::string>& data) {
		GLuint pro = glCreateProgram();
		
		ME_CORE_INFO("{0}", data.size());
		//ME_CORE_ASSORT(data.size() <= 3, "We only support up to 3 shaders!")
		std::array<GLuint,3> allShaders;
		int shaderIndex = 0;
		for (auto& kv : data) {
			GLenum shaderType = kv.first;
			const std::string& source = kv.second;
			
			GLuint shader = glCreateShader(shaderType);
			const GLchar* sourcestr = source.c_str();
			glShaderSource(shader, 1, &sourcestr, 0);

			glCompileShader(shader);
			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> errorLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
				glDeleteShader(shader); // Don't leak the shader.
				ME_CORE_ERROR("{0}", errorLog.data());
				ME_CORE_ASSORT(false, "Shader ({0}) error: Shader Failed to build!", shaderType);
				break;
			}
			
			glAttachShader(pro, shader);
			allShaders[shaderIndex++] = shader;
		}

		
		applyProgram(pro);
		for (int i = 0; i < shaderIndex;i++) {
			glDetachShader(pro, allShaders[i]);
			glDeleteShader(allShaders[i]);
		}

		program = pro;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::preProcess(const std::string& data) {
		std::unordered_map<GLenum, std::string> ans;

		const char* tokenType = "#type";
		size_t tokenLength = strlen(tokenType);
		size_t pos = data.find(tokenType, 0);
		while (pos != std::string::npos) {

			size_t eol = data.find_first_of("\r\n", pos);
			ME_CORE_ASSORT(eol, "Syntex Error");
			size_t b = pos + tokenLength + 1;
			std::string t = data.substr(b, eol - b);
			ME_CORE_ASSORT(convertToGLType(t), "Invalid Type format {0}", t);

			size_t nextLinePos = data.find_first_not_of("\r\n", eol);
			
			pos = data.find(tokenType, nextLinePos);
			//ME_CORE_INFO("{0}", (pos == std::string::npos) ? data.substr(nextLinePos) : data.substr(nextLinePos, pos - nextLinePos));
			//ME_CORE_INFO("{0}", data.substr(col, nl - (nl == std::string::npos ? data.size() - 1 : nl)));
			ans[convertToGLType(t)] = (pos == std::string::npos) ? data.substr(nextLinePos) : data.substr(nextLinePos, pos - nextLinePos);
		}

		return ans;
	}

	std::string OpenGLShader::readFile(const std::string& filePath) {
		std::string res;
		std::ifstream in(filePath, std::ios::in | std::ios::binary);
		if (in) {
			in.seekg(0, std::ios::end);
			res.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&res[0], res.size());
			in.close();
		}
		else {
			ME_CORE_ERROR("Could not open file {0}", filePath);
		}
		return res;
	}

	
	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragSource, const bool& isFiles) : m_name(name) {
		if (isFiles) {
			std::unordered_map<GLenum, std::string> map;
			map[GL_VERTEX_SHADER] = readFile(vertexSource);
			map[GL_FRAGMENT_SHADER] = readFile(fragSource);
			compile(map);
		}
		else {
			std::unordered_map<GLenum, std::string> map;
			map[GL_VERTEX_SHADER] = vertexSource;
			map[GL_FRAGMENT_SHADER] = fragSource;
			compile(map);
		}
	}

	OpenGLShader::~OpenGLShader() {
		glDeleteProgram(program);
	}

	void OpenGLShader::bind() const {
		glUseProgram(program);
	}

	void OpenGLShader::unbind() const {
		glUseProgram(0);
	}

	void OpenGLShader::setUniformMat4(const std::string& name, const glm::mat4& m) {
		GLint loc = glGetUniformLocation(program, name.c_str());
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(m));
	}
	void OpenGLShader::setUniformMat3(const std::string& name, const glm::mat3& m) {
		GLint loc = glGetUniformLocation(program, name.c_str());
		glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(m));
	}
	void OpenGLShader::setUniformFloat(const std::string& name, const float m) {
		GLint loc = glGetUniformLocation(program, name.c_str());
		glUniform1f(loc, m);
	}
	void OpenGLShader::setUniformVec2(const std::string& name, const glm::vec2& m) {
		GLint loc = glGetUniformLocation(program, name.c_str());
		glUniform2f(loc, m.x, m.y);
	}
	void OpenGLShader::setUniformVec3(const std::string& name, const glm::vec3& m) {
		GLint loc = glGetUniformLocation(program, name.c_str());
		glUniform3f(loc, m.x, m.y, m.z);
	}
	void OpenGLShader::setUniformVec4(const std::string& name, const glm::vec4& m) {
		GLint loc = glGetUniformLocation(program, name.c_str());
		glUniform4f(loc,m.x, m.y,m.z, m.w);
	}
	void OpenGLShader::setUniformBool(const std::string& name, const bool m) {
		GLint loc = glGetUniformLocation(program, name.c_str());
		glUniform1i (loc, m ? 1 : 0);
	}
	void OpenGLShader::setUniformInt(const std::string& name, const int m) {
		GLint loc = glGetUniformLocation(program, name.c_str());
		glUniform1i(loc,m);
	}

}