#pragma once
#include "hzpch.h"
#include "../../window/window.h"

#include <GLFW/glfw3.h>
namespace ME {

	class WindowsWindow : public Window {

	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void onUpdate() override;

		inline unsigned int getWidth() const override { return m_data.width; }
		inline unsigned int getHeight() const override { return m_data.height; }

		inline void assignEvents() override;

		void setVSync(bool enabled) override;
		bool isVSync() const override;
	private:
		virtual void init(const WindowProps& props);
		virtual void shutdown();
	private:
		GLFWwindow* m_window;
		WindowProps m_data;
	};

}