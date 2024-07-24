#include <hzpch.h>
#include "OpenGLVertex.h"
#include <glad/glad.h>
namespace ME {

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size) : m_layout(BufferLayout()) {
		
		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
		
	}

	 void OpenGLVertexBuffer::bindData(uint32_t location, uint32_t startPos, uint32_t size, uint32_t totalSize, uint32_t strife) {
		//ME_CORE_INFO("{0} {1}", size, totalSize);
		// glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		 glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		this->locations.push_back(location);
		 glVertexAttribPointer(location, size, GL_FLOAT, false, strife, (const void*)(startPos));
		
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer() {
		glDeleteBuffers(1,&this->vertexBuffer);
	
	}

	void OpenGLVertexBuffer::bind() {
		//glBindVertexArray(va);
		for (uint32_t i : locations) {
			glEnableVertexAttribArray(i);
		}
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		
	}

	void OpenGLVertexBuffer::unbind() {
		for (uint32_t i : locations) {
			glDisableVertexAttribArray(i);
		}
		glBindVertexArray(va);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* pos, uint32_t size, uint32_t totalSize) {
		glGenBuffers(1, &indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(uint32_t), pos, GL_STATIC_DRAW);

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

