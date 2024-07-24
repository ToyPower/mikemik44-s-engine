#include <hzpch.h>
#include "OpenGlVertexArray.h"
#include <glad/glad.h>
namespace ME {
	static GLenum convertToGLType(ShaderType type) {
		switch (type) {
		case ShaderType::Int:
			return GL_INT;
		case ShaderType::Int2:
			return GL_INT;
		case ShaderType::Int3:
			return GL_INT;
		case ShaderType::Int4:
			return GL_INT;
		case ShaderType::Bool:
			return GL_BOOL;
		case ShaderType::Float:
			return GL_FLOAT;
		case ShaderType::Float2:
			return GL_FLOAT;
		case ShaderType::Float3:
			return GL_FLOAT;
		case ShaderType::Float4:
			return GL_FLOAT;
		case ShaderType::Vec2:
			return GL_FLOAT;
		case ShaderType::Vec3:
			return GL_FLOAT;
		case ShaderType::Vec4:
			return GL_FLOAT;
		case ShaderType::Mat3:
			return GL_FLOAT;
		case ShaderType::Mat4:
			return GL_FLOAT;
		}
		ME_CORE_ASSORT(false, "Unknown Shader Type!");
		return 0;
	}
	OpenGLVertexArray::OpenGLVertexArray() {
		glGenVertexArrays(1, &id);
	}
	OpenGLVertexArray::~OpenGLVertexArray() {
		glDeleteVertexArrays(1, &id);
	}
	void OpenGLVertexArray::bind() {
		glBindVertexArray(id);
		for (auto id : locations) {
			glEnableVertexAttribArray(id);
		}
		for (auto a : m_vbuffers) {
			a->bind();
		}
		m_ibuffer->bind();
	}

	void OpenGLVertexArray::unbind() {
		m_ibuffer->unbind();
		for (auto a : m_vbuffers) {
			a->unbind();
		}
		for (auto id : locations) {
			glDisableVertexAttribArray(id);
		}
		glBindVertexArray(0);
	}
	void OpenGLVertexArray::addVertexBuffer(const std::shared_ptr<VVertexBuffer>& buffer) {

		glBindVertexArray(id);
		uint32_t count = 0;
		buffer->bind();
		const auto& layout = buffer->getLayout();
		for (auto a : layout) {
			buffer->bind();
			locations.push_back(count);
			glVertexAttribPointer(count, a.getComponentCount(), convertToGLType(a.data), a.normalized ? GL_TRUE : GL_FALSE, ((BufferLayout&)(layout)).getStrife(), (const void*)(a.offset));
			count += 1;
		}
		m_vbuffers.push_back(buffer);

	}
	
	void OpenGLVertexArray::setIndexBuffer(const std::shared_ptr<IIndexBuffer>& buffer) {
		
		m_ibuffer = buffer;
	};

}