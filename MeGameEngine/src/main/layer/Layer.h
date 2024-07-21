#pragma once
#include "../specialincludes.h"
#include "../events/Event.h"
namespace ME {

	class ME_API Layer {

	public:
		Layer(const std::string& layer = "Layer");
		virtual ~Layer();

		virtual void onAttach() {};
		virtual void onDetach() {};
		virtual void onUpdate() {};
		virtual void onRender() {};
		virtual bool onEvent(Events& e) { return true; };

		inline const std::string& getName() const { return m_name; }
	protected:
		std::string m_name;
	};
	

}