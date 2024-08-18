#include <hzpch.h>
#include "EditorLayout.h"
#include <glm/gtc/type_ptr.hpp>
#define R ME::Renderer2D
#define RC ME::RendererContent

namespace ME {
	EditorLayout::EditorLayout() : Layer("Sandbox2D"), cam(new ME::CameraController(new ME::OthrographicCamera((float)ME::Application::getInstance().getWidth() / ME::Application::getInstance().getHeight()), true)) {}

	void EditorLayout::onAttach() {
		ME::Renderer2D::init();
		tex = ME::Ref<ME::Texture>(ME::Texture2D::create("assets/textures/test.png"));
		cam->setZoom(5.0f);


		ME::FrameBufferSpecial spec;
		spec.width = 800;
		spec.height = 600;

		m_frameBuffer = ME::FrameBuffer::create(spec);

	}

	void EditorLayout::onDetach() {
		ME::Renderer2D::shutdown();
	}
	static float rotation = 0.0f;

	void EditorLayout::onUpdate(ME::TimeStep step) {
		rotation += step * 50;
		this->tim.restart();
		ME::Timer tim("update");
		cam->update(step);
		tim.stop(true);

		if (ME::Input::isButtonPress(ME_MOUSE_BUTTON_LEFT))
		{
			auto [x, y] = ME::Input::getMousePos();
			auto width = ME::Application::getInstance().getWidth();
			auto height = ME::Application::getInstance().getHeight();

			auto bounds = cam->getBounds();
			auto pos = cam->getCamera()->getPosition();
			x = (x / width) * bounds.getWidth() - bounds.getWidth() * 0.5f;
			y = bounds.getHeight() * 0.5f - (1 - (y / height)) * bounds.getHeight();

		}


	}

	void EditorLayout::onRender() {
		m_frameBuffer->bind();
		ME::Timer tim("Renderer");
		R::clear();
#
		R::beginScene(cam->getCamera());

		ME::Timer tim2("Rendering Time");

		R::setRotation(-45, false);
		R::drawQuadCentered({ 1.0f, 0, 0.1f }, { 0.8f, 0.8f }, color);
		R::setRotation(0);

		R::drawQuadCentered({ -1.0f, 0.0f, 0.1f }, { 0.8f, 0.8f }, color);


		R::drawQuadCentered({ 0.5f, -0.5f, 0.1f }, { 0.5f, 0.75f }, color2);

		R::drawQuadCentered({ 0,0, -0.1f }, { 20, 20 }, tex, color3, 10);

		R::rotate(rotation, false);
		R::drawQuadCentered({ -2.0f, 0.0f, 0.0f }, { 1, 1 }, tex, { 1,1,1,1 }, 20);
		R::setRotation(0);

		for (float x = -5.0f; x < 5.0f; x += 0.5) {
			for (float y = -5.0f; y < 5.0f; y += 0.5) {
				glm::vec4 color = { (x + 5.0) / 10.0f, 0.4f, (y + 5.0) / 10.0f, 0.75f };
				R::drawQuadCentered({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
		R::endScene();

		m_frameBuffer->unbind();
		//tim2.stop(true);
		tim.stop(true);
		this->tim.stop();
	}

	void EditorLayout::onGUIRender() {
		static bool dockspaceOpen = true;
		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// Submit the DockSpace
		ImGuiIO& io = ImGui::GetIO();

		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);


		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows,
				// which we can't undo at the moment without finer window depth/z control.
				if (ImGui::MenuItem("Exit") != 0) { ME::Application::getInstance().close(); }


				ImGui::EndMenu();
			}


			ImGui::EndMenuBar();
		}
		ImGui::Begin("Settings");
		ImGui::ColorEdit4("color 1", glm::value_ptr(color));
		ImGui::ColorEdit4("color 2", glm::value_ptr(color2));
		ImGui::ColorEdit4("color 3", glm::value_ptr(color3));
		for (ME::TimerResult tr : ME::TimerResult::allResults) {
			char label[50] = {};
			strcpy(label, tr.name);
			strcat(label, " %.3fms");
			ImGui::Text(label, tr.timer);
		}
		ME::TimerResult::clearTimerResult();
		ImGui::End();


		ImGui::Begin("ViewPort");
		ImGui::Image((void*)m_frameBuffer->getColorAttach(), ImGui::GetWindowSize(), ImVec2(0,1), ImVec2(1,0));
		ImGui::End();
		ImGui::End();
	}
}