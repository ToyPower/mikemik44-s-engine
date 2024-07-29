#pragma once
#include "hzpch.h"
#include "main/layer/ImGuiLayer.h"
#include "../macro.h"
#include "../layer/Layer.h"
#include "../layer/LayerStack.h"
#include "../platform/windows/WindowsWindow.h"
#include "main/dateentry/TimeStep.h"
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
		inline Window& getWindow() { return *m_window;  }
		inline static Application& getInstance() { return *s_instance; }
	private:
		std::unique_ptr<Window> m_window;
		ImGuiLayer* m_imguilayer;
		bool m_running = true;
		LayerStack m_st;
		static Application* s_instance;
	
		float m_lastFrame;

	};
	Application* CreateApplication();
}

