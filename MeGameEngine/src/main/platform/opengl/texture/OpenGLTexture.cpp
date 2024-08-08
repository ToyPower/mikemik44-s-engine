#include <hzpch.h>
#include "OpenGLTexture.h"
#include <glad/glad.h>
#include "STBImage.h"
namespace ME {
	OpenGLTexture::OpenGLTexture(const std::string& filePath){
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);
		ME_CORE_ASSORT(data, "Could not load Texture!");
		this->width = width;
		this->height = height;
		
		if (channels == 3) {
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}
		else if (channels == 4) {
			internalFormat= GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		glCreateTextures(GL_TEXTURE_2D, 1, &tex);
		glTextureStorage2D(tex, 1, internalFormat, width, height);
		
		glTextureParameteri(tex, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(tex, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(tex, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(tex, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(tex, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture::OpenGLTexture(const int& width, const int& height) : width(width), height(height){
		internalFormat = GL_RGBA8;
		dataFormat = GL_RGBA;
		glCreateTextures(GL_TEXTURE_2D, 1, &tex);
		
		glTextureStorage2D(tex, 1, internalFormat, width, height);

		glTextureParameteri(tex, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(tex, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(tex, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(tex, GL_TEXTURE_WRAP_T, GL_REPEAT);

	}

	void OpenGLTexture::setPixels(void* data, uint32_t size) {
		glTextureSubImage2D(tex, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);
	}

	OpenGLTexture::~OpenGLTexture() {
		glDeleteTextures(1, &tex);
	}

	void OpenGLTexture::bind(uint32_t slot) {
		glBindTextureUnit(slot, tex);
	}

	void OpenGLTexture::unbind(uint32_t slot) {
		glBindTextureUnit(slot, 0);
	}

}

