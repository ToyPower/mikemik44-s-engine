#include <hzpch.h>
#include "OpenGLVertex.h"
#include <glad/glad.h>
namespace ME {

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size) : m_layout(BufferLayout()) {

		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::setData(const void* data, uint32_t size) {
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size) : m_layout(BufferLayout()) {
		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}



	OpenGLVertexBuffer::~OpenGLVertexBuffer() {
		glDeleteBuffers(1,&this->vertexBuffer);
	
	}

	void OpenGLVertexBuffer::bind() {

		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		
	}

	void OpenGLVertexBuffer::unbind() {
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* pos, uint32_t size) {
		glGenBuffers(1, &indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(uint32_t), pos, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		this->count = size;
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer() {
		glDeleteBuffers(1, &indexBuffer);
	}

	void OpenGLIndexBuffer::bind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	}

	void OpenGLIndexBuffer::unbind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}


	
}

