
#include <MeCore.h>
#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <any>
#include <vector>
#include "main/entry/Entry.h"
#include "EditorLayout.h"
#include "main/util/StrUtil.h"
namespace ME {
	class MENut : public Application {
	public:

		MENut() : Application("ME Editor") {
			pushLayer(new EditorLayout());
		}

		~MENut() {

		}
	};

	Application* CreateApplication() {

		return new MENut();
	}
}