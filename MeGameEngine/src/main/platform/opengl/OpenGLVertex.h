#pragma once
#include <hzpch.h>
#include "main/renderer/Buffers.h"
#include <glad/glad.h>
namespace ME {
	
	class OpenGLVertexBuffer : public VVertexBuffer {

	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer() override;
	
		void bind() override;
		void unbind() override;
		virtual void setLayout(BufferLayout& layout) override { 
			m_layout = layout;
			
		}
		virtual const BufferLayout& getLayout() const override { return m_layout; }
	private:
		
		uint32_t vertexBuffer, va;
		BufferLayout m_layout;
	};

	class OpenGLIndexBuffer : public IIndexBuffer {

	public:
		OpenGLIndexBuffer(uint32_t* pos, uint32_t size, uint32_t totalSize);
		virtual ~OpenGLIndexBuffer() override;
		void virtual bind() override;
		void virtual unbind() override;
	private:
		uint32_t indexBuffer;
	};
	
}