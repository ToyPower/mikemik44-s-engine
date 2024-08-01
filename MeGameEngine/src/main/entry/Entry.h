#pragma once
#include "hzpch.h"
#ifdef ME_PLATFORM_WINDOWS
extern ME::Application* ME::CreateApplication();
	int main(int argc, char** args) {
		ME::Log::init();
		
		auto app = ME::CreateApplication();
		app->run();
		delete app;

	}
#endif
