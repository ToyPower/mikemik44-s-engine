#pragma once
#include <hzpch.h>
#include "Buffers.h"

namespace ME {

	class VertexArray {

	public:
		virtual ~VertexArray() {}
		virtual void bind() = 0;
		virtual void unbind() = 0;
		virtual void addVertexBuffer(const std::shared_ptr<VVertexBuffer>& buffer) = 0;
		virtual void setIndexBuffer(const std::shared_ptr<IIndexBuffer>& buffer) = 0;
		
		virtual const std::vector<std::shared_ptr<VVertexBuffer>>& getVertexBuffers() const = 0;
		virtual const std::shared_ptr<IIndexBuffer>& getIndexBuffer() const = 0;
		static VertexArray* create();
	};

}
