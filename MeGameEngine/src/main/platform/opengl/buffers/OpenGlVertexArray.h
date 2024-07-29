#pragma once
#include <hzpch.h>
#include "main/renderer/buffers/VertexArray.h"
namespace ME {

	class OpenGLVertexArray : public VertexArray {

	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray() override;
		virtual void bind() override;
		virtual void unbind() override;
		virtual void addVertexBuffer(const Ref<VertexBuffer>& buffer) override;
		virtual void setIndexBuffer(const Ref<IndexBuffer>& buffer) override;
		virtual const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const override{ return m_vbuffers;}
		virtual const Ref<IndexBuffer>& getIndexBuffer() const override {
			return m_ibuffer;
		}
	private:
		uint32_t id;
		std::vector<Ref<VertexBuffer>> m_vbuffers;
		Ref<IndexBuffer> m_ibuffer;
		std::vector<uint32_t> locations = {};
	};

}
