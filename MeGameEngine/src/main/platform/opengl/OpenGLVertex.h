#pragma once
#include <hzpch.h>
#include "main/renderer/Buffers.h"
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
		}
		ME_CORE_ASSORT(false, "Unknown Shader Type!");
		return 0;
	}
	class OpenGLVertexBuffer : public VVertexBuffer {

	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer() override;
		void bindData(uint32_t location, uint32_t startPos, uint32_t size, uint32_t totalSize, uint32_t strife) override;
		void bind() override;
		void unbind() override;
		virtual void setLayout(BufferLayout& layout) override { 
			m_layout = layout;
			uint32_t count = 0;
			for (auto a : layout) {
				bindData(count, a.offset, a.getComponentCount(), a.size, layout.getStrife());
				count += 1;
			}
		}
		virtual const BufferLayout& getLayout() const override { return m_layout; }
	private:
		std::vector<uint32_t> locations;
		uint32_t vertexBuffer, va;
		BufferLayout& m_layout;
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