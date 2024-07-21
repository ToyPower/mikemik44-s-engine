#include <hzpch.h>
#include "ImGuiLayer.h"
#include "../specialincludes.h"
#include "../platform/opengl/imgui_impl_opengl3.h"
namespace ME {

	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {

	}

	ImGuiLayer::~ImGuiLayer() {

	}
	
	void ImGuiLayer::onAttach() {
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;
		
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::onDetach() {

	}

	void ImGuiLayer::onUpdate() {
		

		Window& dt = Application::getInstance().getWindow();
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(dt.getWidth(), dt.getHeight());
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();
		float time = (float)glfwGetTime();
		io.DeltaTime = m_time > 0.0f ? time - m_time : (1.0f/60.0f);
		m_time = time;

		static bool showDemo = true;
		ImGui::ShowDemoWindow(&showDemo);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	}

	void ImGuiLayer::onRender() {
		
	}

	bool ImGuiLayer::onEvent(Events& e) {
		
		ImGuiIO& io = ImGui::GetIO();
		if (e.name() == "windowKeyPress") {
			int key = std::any_cast<int>(e.getParam("key"));
			//ME_CORE_INFO("{0} | {1}", key, GLFW_KEY_RIGHT_CONTROL);
			io.KeysDown[key] = true;
			io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
			io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
			io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
			io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
		}
		else if (e.name() == "windowKeyRelease") {
			int key = std::any_cast<int>(e.getParam("key"));
			io.KeysDown[key] = false;
			io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
			io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
			io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
			io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
		}
		else if (e.name() == "windowKeyTyped") {
			int key = std::any_cast<int>(e.getParam("character"));
			if (key > 0 && key < 0x100000) {
				io.AddInputCharacter((unsigned short)key);
			}
		}
		else if (e.name() == "windowButtonPress") {
			int button = std::any_cast<int>(e.getParam("button"));
			
			io.MouseDown[button] = true;
		}
		else if (e.name() == "windowButtonRelease") {
			int button = std::any_cast<int>(e.getParam("button"));
			io.MouseDown[button] = false;
		}
		else if (e.name() == "windowMouseMove") {
			auto f = io.MousePos;
			ME_CORE_INFO("{0},{1}", f.x, f.y);
			double _x = std::any_cast<double>(e.getParam("x"));
			double _y = std::any_cast<double>(e.getParam("y"));
			
			io.MousePos = ImVec2((float)_x, (float)_y);
		}
		else if (e.name() == "windowMouseScroll") {
			io.MouseWheelH += std::any_cast<double>(e.getParam("xoff"));
			io.MouseWheel += std::any_cast<double>(e.getParam("yoff"));
		}

		return true;
	}

}
