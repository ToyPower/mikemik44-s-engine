#pragma once
#include "hzpch.h"
#include "../specialincludes.h"

namespace ME {
	struct WindowProps {

		std::string title;
		unsigned int width;
		unsigned int height;
		bool vsync;
		WindowProps(const std::string& title = "My Engine", unsigned int width = 800, unsigned int height = 600, bool sync = false) : title(title), width(width), height(height), vsync(sync) {}

	};
	class Window {

	public:
		virtual ~Window() = default;

		virtual void onUpdate() = 0;

		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;

		virtual void assignEvents() = 0;
		virtual void setVSync(bool enabled) = 0;
		virtual bool isVSync() const = 0;

		static Window* create(const WindowProps& props = WindowProps());

	};

}