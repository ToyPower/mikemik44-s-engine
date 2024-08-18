#pragma once
#include "hzpch.h"
#include "main/layer/imgui/ImGuiLayer.h"
#include "main/layer/Layer.h"
#include "main/layer/stack/LayerStack.h"
#include "main/platform/windows/WindowsWindow.h"
#include "main/dataentry/TimeStep.h"
namespace ME {
	
	class ME_API Application
	{
	public:
		Application(const std::string& name = "My App");
		virtual ~Application();
		void run();
		bool onEvent(Events& e);
		void pushLayer(Layer* layer);
		void pushOverlay(Layer* layer);
		void close();
		inline Window& getWindow() { return *m_window;  }
		inline static Application& getInstance() { return *s_instance; }
		uint32_t getWidth() { return m_window->getWidth(); }
		uint32_t getHeight() { return m_window->getHeight(); }
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

