#pragma once
#include "hzpch.h"
#include "main/layer/ImGuiLayer.h"
#include "../macro.h"
#include "../layer/Layer.h"
#include "../layer/LayerStack.h"
#include "../platform/windows/WindowsWindow.h"
#include "main/renderer/Shader.h"
#include "main/renderer/Buffers.h"

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
		uint32_t va;
		static Application* s_instance;
		std::unique_ptr<VVertexBuffer> m_vbuffer;
		
		std::unique_ptr<IIndexBuffer> m_ibuffer;
		std::unique_ptr<Shader> m_shader;
	};
	Application* CreateApplication();
}

