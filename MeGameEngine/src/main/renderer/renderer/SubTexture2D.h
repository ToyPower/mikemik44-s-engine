#pragma once
#include "Texture.h"
#include <glm/glm.hpp>
namespace ME {

	class SubTexture2D {

	public:
		SubTexture2D(const Ref<Texture>& texture, const glm::vec2& min, const glm::vec2& max);

		Ref<Texture> getTexture() { return m_texture; }
		glm::vec2* getTexCoords() { return m_texCoords; }
		glm::vec2 getTexCoord(uint32_t index) { return m_texCoords[index]; }
	
		static Ref<SubTexture2D> createFromCoords(const Ref<Texture>& tex, const glm::vec2& coords, const glm::vec2& spriteSize, const glm::vec2& sizeOfObject = glm::vec2(1, 1));
	private:
		Ref<Texture> m_texture;

		glm::vec2 m_texCoords[4];
	};

}
