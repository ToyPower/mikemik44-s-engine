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
		static VertexArray* create();
	};

}
