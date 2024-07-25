#pragma once
#include <hzpch.h>
#include "Buffers.h"

namespace ME {

	class VertexArray {

	public:
		virtual ~VertexArray() {}
		virtual void bind() = 0;
		virtual void unbind() = 0;
		virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer) = 0;
		virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer) = 0;
		
		virtual const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const = 0;
		virtual const std::shared_ptr<IndexBuffer>& getIndexBuffer() const = 0;
		static VertexArray* create();
	};

}
