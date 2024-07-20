#pragma once
#include "../macro.h"
namespace ME {
	class ME_API Application
	{
	public:
		Application();
		virtual ~Application();
		void run();

	};
	Application* CreateApplication();
}

