#pragma once
#include "main/renderer/renderer/Texture.h"
#include <glad/glad.h>
namespace ME {

	class OpenGLTexture : public Texture2D{
	public:
		OpenGLTexture(const std::string& filePath);
		OpenGLTexture(const int& width, const int& height);
		virtual void setPixels(void* data, uint32_t size) override;
		virtual ~OpenGLTexture() override;
		virtual uint32_t getWidth() override { return width; }
		virtual uint32_t getHeight() override { return height; }
		virtual void bind(uint32_t slot = 0) override;
		virtual void unbind(uint32_t slot = 0) override;
	private:
		GLenum internalFormat = 0, dataFormat = 0;
		uint32_t tex;
		uint32_t width, height;
		
	};

}