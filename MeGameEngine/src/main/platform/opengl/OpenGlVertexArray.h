#pragma once
#include <hzpch.h>
#include "main/renderer/VertexArray.h"
namespace ME {

	class OpenGLVertexArray : public VertexArray {

	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray() override;
		virtual void bind() override;
		virtual void unbind() override;
		virtual void addVertexBuffer(const std::shared_ptr<VVertexBuffer>& buffer) override;
		virtual void setIndexBuffer(const std::shared_ptr<IIndexBuffer>& buffer) override;
		virtual const std::vector<std::shared_ptr<VVertexBuffer>>& getVertexBuffers() const override{ return m_vbuffers;}
		virtual const std::shared_ptr<IIndexBuffer>& getIndexBuffer() const override {
			return m_ibuffer;
		}
	private:
		uint32_t id;
		std::vector<std::shared_ptr<VVertexBuffer>> m_vbuffers;
		std::shared_ptr<IIndexBuffer> m_ibuffer;
		std::vector<uint32_t> locations = {};
	};

}
