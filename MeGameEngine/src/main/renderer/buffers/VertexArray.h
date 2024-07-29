#pragma once
#include <hzpch.h>
#include "Buffers.h"

namespace ME {

	class VertexArray {

	public:
		virtual ~VertexArray() {}
		virtual void bind() = 0;
		virtual void unbind() = 0;
		virtual void addVertexBuffer(const Ref<VertexBuffer>& buffer) = 0;
		virtual void setIndexBuffer(const Ref<IndexBuffer>& buffer) = 0;
		
		virtual const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer>& getIndexBuffer() const = 0;
		static VertexArray* create();
	};

}
