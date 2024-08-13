#pragma once
#include <hzpch.h>
#include "main/renderer/buffers/Buffers.h"
#include <glad/glad.h>
namespace ME {
	
	class OpenGLVertexBuffer : public VertexBuffer {

	public:
		OpenGLVertexBuffer(uint32_t size);
		OpenGLVertexBuffer(float* vertices, uint32_t size);

		virtual ~OpenGLVertexBuffer() override;
	
		void bind() override;
		void unbind() override;
		virtual void setData(const void* data, uint32_t size) override;
		virtual const void setLayout(BufferLayout& layout) override { 
			m_layout = layout;
		}
		virtual const BufferLayout& getLayout() const override { return m_layout; }
	private:
		
		uint32_t vertexBuffer;
		BufferLayout m_layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer {

	public:
		OpenGLIndexBuffer(uint32_t* pos, uint32_t size);
		virtual ~OpenGLIndexBuffer() override;
		virtual void bind() override;
		virtual	void unbind() override;
		virtual uint32_t getCount() const override { return count; }
	private:
		uint32_t indexBuffer;
		uint32_t count;
	};
	
}