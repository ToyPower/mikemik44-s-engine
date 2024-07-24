#pragma once
#include "hzpch.h"
#include "main/layer/ImGuiLayer.h"
#include "../macro.h"
#include "../layer/Layer.h"
#include "../layer/LayerStack.h"
#include "../platform/windows/WindowsWindow.h"
#include "main/renderer/Shader.h"
#include "main/renderer/Buffers.h"
#include "main/renderer/VertexArray.h"
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
		std::shared_ptr<VVertexBuffer> m_vbuffer;
		
		std::shared_ptr<IIndexBuffer> m_ibuffer;
		std::shared_ptr<Shader> m_shader, m_shader2;
		std::shared_ptr<VertexArray> m_va;

		std::shared_ptr<VertexArray> m_square;
	};
	Application* CreateApplication();
}

