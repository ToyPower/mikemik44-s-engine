#pragma once

namespace ME {

	class GraphicsContext {
	public:
		virtual void swapBuffers() = 0;
		virtual void initialize() = 0;
	
	};

}
