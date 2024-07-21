#pragma once
#include "hzpch.h"
#include "../macro.h"
#include "../platform/windows/WindowsWindow.h"
namespace ME {
	class ME_API Application
	{
	public:
		Application();
		virtual ~Application();
		void run();
	private:
		std::unique_ptr<Window> m_window;
		bool m_running = true;
	};
	Application* CreateApplication();
}

