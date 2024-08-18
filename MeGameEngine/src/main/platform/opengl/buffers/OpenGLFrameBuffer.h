#pragma once
#include "main/renderer/renderer/FrameBuffer.h"

namespace ME {

	class OpenGLFrameBuffer : public FrameBuffer {

	public:
		OpenGLFrameBuffer(const FrameBufferSpecial& spec);
		virtual ~OpenGLFrameBuffer();
		virtual const FrameBufferSpecial& getFrameParams() const override { return spec; }
		virtual FrameBufferSpecial& getFrameParams() override { return spec; };
	
		virtual void invalidate() override;
		virtual uint32_t getColorAttach() override { return m_colorTexture; }
		virtual uint32_t getDepthAttach() override { return m_depthBuffer; }

		virtual void bind() override;
		virtual void unbind() override;

	private:
		uint32_t renderID = -1;
		uint32_t m_colorTexture = -1;
		uint32_t m_depthBuffer = -1;
		FrameBufferSpecial spec;
	};

}