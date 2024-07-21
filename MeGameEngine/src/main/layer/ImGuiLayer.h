#pragma once
#include "layer.h"

#include "../entry/Application.h"
namespace ME {

	class ME_API ImGuiLayer : public Layer{

	public:
		ImGuiLayer();
		~ImGuiLayer();
		void onAttach() override;
		void onDetach() override;
		void onUpdate() override;
		void onRender() override;
		bool onEvent(Events& e) override;
	private:
		float m_time = 0.0f;
	};

}