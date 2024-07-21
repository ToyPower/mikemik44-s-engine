#pragma once
#include "hzpch.h"
#include "../macro.h"
#include "../layer/Layer.h"
#include "../layer/LayerStack.h"
#include "../platform/windows/WindowsWindow.h"
namespace ME {
	class ME_API Application
	{
	public:
		Application();
		virtual ~Application();
		void run();
		bool onEvent(Events& e);
		void pushLayer(Layer* layer);
		void pushOverlay(Layer* layer);
	private:
		std::unique_ptr<Window> m_window;
		bool m_running = true;
		LayerStack m_st;
	};
	Application* CreateApplication();
}

