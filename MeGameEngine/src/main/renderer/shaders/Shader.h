#pragma once
#include <glm/glm.hpp>
namespace ME {

	class Shader {

	public:
		virtual ~Shader() {}
		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		
		static Shader* create(const std::string& vertexSource, const std::string& fragSource);
	};

}