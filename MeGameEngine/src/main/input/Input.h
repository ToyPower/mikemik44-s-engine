#pragma once
#include <hzpch.h>
namespace ME {

	class ME_API Input {
	public:
		static bool isKeyPress(int keycode) {return s_instance->isKeyPressPoll(keycode);};
		static bool isKeyRelease(int keycode) { return s_instance->isKeyReleasePoll(keycode); };
		static bool isButtonPress(int button) { return s_instance->isButtonPressPoll(button); };
		static bool isButtonRelease(int button) { return s_instance->isButtonReleasePoll(button); };
		static float getMouseX() { return s_instance->getMouseXPoll(); }
		static float getMouseY() { return s_instance->getMouseYPoll(); }
		static std::pair<float,float> getMousePos() { return s_instance->getMousePosPoll(); }
	protected:
		virtual bool isKeyPressPoll(int keycode) = 0;
		virtual bool isKeyReleasePoll(int keycode) = 0;
		virtual bool isButtonPressPoll(int keycode) = 0;
		virtual bool isButtonReleasePoll(int keycode) = 0;
		virtual float getMouseXPoll() = 0;
		virtual float getMouseYPoll() = 0;
		virtual std::pair<float,float> getMousePosPoll() = 0;
	private:
		static Input* s_instance;
	};

}
