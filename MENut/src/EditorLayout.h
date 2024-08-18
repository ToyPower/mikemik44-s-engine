#pragma once
#include <MeCore.h>
#include <main/layer/Layer.h>
#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <any>
#include <vector>
namespace ME {
	class EditorLayout : public Layer {

	public:
		EditorLayout();
		virtual ~EditorLayout() = default;
		virtual void onAttach() override;
		virtual void onDetach() override;
		virtual void onUpdate(TimeStep step) override;
		virtual void onRender() override;
		virtual bool onEvent(Events& e) override {
			if (!cam->onEvent(e)) {
				return false;
			}
			if (e.name() == "windowResize") {
				auto& h = m_frameBuffer->getFrameParams();
				h.width = std::any_cast<int>(e.getParam("width"));
				h.height = std::any_cast<int>(e.getParam("height"));
				m_frameBuffer->invalidate();
			}
			return true;
		}

		virtual void onGUIRender() override;
	private:
		Ref<CameraController> cam;
		glm::vec4 color = { 1,0,0,1 }, color2 = { 0.2, 0.3, 0.8, 1 }, color3 = { 1,1,1,1 };
		//TEMP
		Ref<Texture> tex;
		Ref<Texture> spriteSheet;
		Ref<SubTexture2D> stairs, barrel, tree;
		Ref<Shader> shader;
		std::vector<Mesh> grid;
		Timer tim =Timer("Overall");

		Ref<FrameBuffer> m_frameBuffer;
	};
}