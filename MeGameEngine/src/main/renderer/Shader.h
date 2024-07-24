#pragma once
#include "glad/glad.h"

namespace ME {

	class Shader {

	public:
		Shader(const std::string& vertexSource, const std::string& fragSource);
		~Shader();
		void bind() const;
		void unbind() const;
	private:
		uint32_t genShader(int type, const std::string& source);

	private:
		uint32_t vshader, fshader, program;

	};

}