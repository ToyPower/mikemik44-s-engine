#pragma once
#include "hzpch.h"
#include <string>
namespace ME {

	class Texture {

	public:
		virtual ~Texture() {}
		virtual uint32_t getWidth() = 0;
		virtual uint32_t getHeight() = 0;

		virtual void bind(uint32_t slot = 0) = 0;
		virtual void unbind(uint32_t slot = 0) = 0;
		virtual void setPixels(void* data, uint32_t size) = 0;
	};

	class Texture2D : public Texture {
	public:
		static Ref<Texture2D> create(const std::string& filePath);
		static Ref<Texture2D> create(const int& width, const int& height);
	};

}


