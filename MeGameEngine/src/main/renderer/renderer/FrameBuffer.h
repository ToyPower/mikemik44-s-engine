#pragma once
#include "main/corefiles/specialincludes.h"
namespace ME {

	struct FrameBufferSpecial {
		uint32_t width, height;
		
		uint32_t samples = 1;

		bool swapChainTarget = false;
	};

	class FrameBuffer {

	public:
		virtual const FrameBufferSpecial& getFrameParams() const = 0;
		virtual FrameBufferSpecial& getFrameParams() = 0;
		virtual ~FrameBuffer() = default;
		virtual void bind() = 0;
		virtual void resize(uint32_t width, uint32_t height) = 0;
		virtual void unbind() = 0;
		virtual void invalidate() = 0;
		virtual uint32_t getColorAttach() = 0;
		virtual uint32_t getDepthAttach() = 0;
		static Ref<FrameBuffer> create(const FrameBufferSpecial& spec);

	};

}