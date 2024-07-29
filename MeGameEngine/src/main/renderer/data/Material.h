#pragma once
#include <hzpch.h>
#include <glm/glm.hpp>
#include "main/renderer/renderer/Texture.h"
namespace ME {

	struct Material {
		
		glm::vec4 albeto = glm::vec4(1,1,1,1);
		Ref<Texture> tex;

	};
	
	static std::map<const std::string, Ref<Material>> mats = {};
	static Ref<Material> getMaterialFromBase(const std::string& mat) {
		auto find = mats.find(mat);
		if (find != mats.end()) {
			return mats[find->first];
		}
		
		return Ref<Material>(new Material());
	}
}