#pragma once
#include "main/input/Input.h"

namespace ME {

	class WindowsInput : public Input {

	protected:
		virtual bool isKeyPressPoll(int keycode) override;
		virtual bool isKeyReleasePoll(int keycode) override;
		virtual bool isButtonPressPoll(int keycode) override;
		virtual bool isButtonReleasePoll(int keycode) override;
		virtual float getMouseXPoll() override;
		virtual float getMouseYPoll() override;
		virtual std::pair<float, float> getMousePosPoll() override;

	};

}