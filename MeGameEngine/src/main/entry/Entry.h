#pragma once

#ifdef ME_PLATFORM_WINDOWS
extern ME::Application* ME::CreateApplication();
	int main(int argc, char** args) {
		auto app = ME::CreateApplication();
		app->run();
		delete app;

	}
#endif
