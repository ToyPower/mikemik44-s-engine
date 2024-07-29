#pragma once
#include "main/renderer/renderer/Texture.h"
namespace ME {

	class OpenGLTexture : public Texture2D{
	public:
		OpenGLTexture(const std::string& filePath);
		virtual ~OpenGLTexture() override;
		virtual uint32_t getWidth() override { return width; }
		virtual uint32_t getHeight() override { return height; }
		virtual void bind(uint32_t slot = 0) override;
		virtual void unbind(uint32_t slot = 0) override;
	private:
		uint32_t tex;
		uint32_t width, height;
		const std::string& path;
	};

}