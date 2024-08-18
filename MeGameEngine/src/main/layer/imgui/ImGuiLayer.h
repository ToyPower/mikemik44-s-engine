#pragma once

#include "main/layer/Layer.h"

namespace ME {

	class ME_API ImGuiLayer : public Layer{

	public:
		ImGuiLayer();
		~ImGuiLayer();
		virtual void onAttach() override;
		virtual void onDetach() override;
		virtual void onGUIRender() override;
		virtual bool onEvent(Events& e) override;
		void begin();
		void end();

		void setBlockEvents(bool block) { blockEvents = block; }
		bool isEventsBlocked() { return blockEvents; };
	private:
		bool blockEvents = true;
		float m_time = 0.0f;
	};

}