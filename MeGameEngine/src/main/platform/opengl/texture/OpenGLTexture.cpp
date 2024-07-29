#include <hzpch.h>
#include "OpenGLTexture.h"
#include <glad/glad.h>
#include "STBImage.h"
namespace ME {
	OpenGLTexture::OpenGLTexture(const std::string& filePath) : path(filePath) {
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);
		ME_CORE_ASSORT(data, "Could not load Texture!");
		this->width = width;
		this->height = height;
		int format = 0;
		int format2 = 0;
		if (channels == 3) {
			format = GL_RGB8;
			format2 = GL_RGB;
		}
		else if (channels == 4) {
			format = GL_RGBA8;
			format2 = GL_RGBA;
		}
		glCreateTextures(GL_TEXTURE_2D, 1, &tex);
		glTextureStorage2D(tex, 1, format, width, height);
		
		glTextureParameteri(tex, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(tex, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(tex, 0, 0, 0, width, height, format2, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
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

