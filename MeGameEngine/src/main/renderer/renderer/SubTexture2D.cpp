#include <hzpch.h>
#include "SubTexture2D.h"

namespace ME {

	SubTexture2D::SubTexture2D(const Ref<Texture>& texture, const glm::vec2& min, const glm::vec2& max) : m_texture(texture){
		m_texCoords[0] = { min.x, min.y };
		m_texCoords[1] = { min.x, max.y };
		m_texCoords[2] = { max.x, max.y };
		m_texCoords[3] = { max.x, min.y };
	}

	Ref<SubTexture2D> SubTexture2D::createFromCoords(const Ref<Texture>& tex, const glm::vec2& coords, const glm::vec2& spriteSize, const glm::vec2& sizeOfObject) {

		glm::vec2 ts(tex->getWidth(), tex->getHeight());
		glm::vec2 min = (coords * spriteSize) / ts;
		glm::vec2 max = (coords * spriteSize + spriteSize * sizeOfObject) / ts;

		return Ref<SubTexture2D>(new SubTexture2D(tex, min, max));

	}

}