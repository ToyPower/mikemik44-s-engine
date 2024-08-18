
#include <MeCore.h>
#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <any>
#include <vector>
#include "main/entry/Entry.h"
#include "EditorLayout.h"
namespace ME {
	class MEEditor : public Application {
	public:

		MEEditor() : Application("ME Editor") {
			pushLayer(new EditorLayout());
		}

		~MEEditor() {

		}
	};

	Application* CreateApplication() {
		return new MEEditor();
	}
}