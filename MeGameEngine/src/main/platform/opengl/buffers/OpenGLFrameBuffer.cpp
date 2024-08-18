#include <hzpch.h>
#include "OpenGLFrameBuffer.h"
#include <glad/glad.h>
namespace ME {

	OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferSpecial& spec) : spec(spec){
		invalidate();
	}

	OpenGLFrameBuffer::~OpenGLFrameBuffer() {
		glDeleteFramebuffers(1, &this->renderID);
	}

	void OpenGLFrameBuffer::invalidate() {
		if (this->renderID == -1) {
			glCreateFramebuffers(1, &this->renderID);
		}
		glBindFramebuffer(GL_FRAMEBUFFER, this->renderID);
		if (this->m_colorTexture != -1) {
			glDeleteTextures(1, &this->m_colorTexture);
			glDeleteTextures(1, &this->m_depthBuffer);
		}
		glCreateTextures(GL_TEXTURE_2D, 1, &this->m_colorTexture);
		
		glBindTexture(GL_TEXTURE_2D, this->m_colorTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, spec.width, spec.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->m_colorTexture, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
		
		
		glCreateTextures(GL_TEXTURE_2D, 1, &m_depthBuffer);
		
		glBindTexture(GL_TEXTURE_2D, m_depthBuffer);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, spec.width, spec.height);
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, spec.width, spec.height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, this->m_depthBuffer, 0);
		glBindTexture(GL_TEXTURE_2D, 0);

		ME_CORE_ASSORT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "FrameBuffer is incomplete!");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFrameBuffer::bind() {
		glBindFramebuffer(GL_FRAMEBUFFER, this->renderID);
	
	}

	void OpenGLFrameBuffer::unbind() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}

}