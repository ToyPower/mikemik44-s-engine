#pragma once
#include <hzpch.h>
#include <glm/glm.hpp>

namespace ME {

	struct Material {
		
		glm::vec4 albeto = glm::vec4(1,1,1,1);
		
		
	};
	
	static std::map<const std::string, Material> mats = {};
	static Material getMaterialFromBase(const std::string& mat) {
		std::map<const std::string, Material>::iterator find = mats.find(mat);
		if (find != mats.end()) {
			return mats[find->first];
		}
		return Material();
	}
}