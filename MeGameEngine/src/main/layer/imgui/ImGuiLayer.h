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
		void begin();
		void end();
	private:
		float m_time = 0.0f;
	};

}