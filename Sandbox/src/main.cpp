#include <MeCore.h>

class Sandbox : public ME::Application {
public:
	Sandbox() {

	}
	~Sandbox() {

	}
};

int main() {
	Sandbox* sandbox = new Sandbox();
	sandbox->run();
	delete sandbox;
	
}