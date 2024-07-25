
#include <MeCore.h>
#include <glm/glm.hpp>

#include <imgui/imgui.h>
#define R ME::Renderer
#define RC ME::RendererContent
class ExampleLayer : public ME::Layer {

public:
	float aspect = 800.0 / 600.0;
	ME::OthrographicCamera cam = ME::OthrographicCamera(-1.0f* aspect, 1.0f* aspect, -1.0f, 1.0f);
	std::shared_ptr<ME::VertexArray> vertex, square;
	std::shared_ptr<ME::Shader> shader, shader2;
	ExampleLayer() : Layer("ExampleLayer") {
		
		float vertices[3 * 3 + 3 * 4] = {
			-0.5f, -0.5f, 0.0f,  1, 0, 0,1,
			0.0f, 0.5f, 0.0f,    0, 1, 0,1,
			0.5f, -0.5f, 0.0f,    0, 0, 1,1,
		};
		ME::BufferLayout layout = {

			{ME::ShaderType::Vec3, "m_Position"},
			{ME::ShaderType::Vec4, "m_color"},

		};

		uint32_t indices[3] = {
			0, 1, 2
		};
		auto buf = std::shared_ptr<ME::VertexBuffer>(ME::VertexBuffer::create(vertices, sizeof(vertices)));
		buf->setLayout(layout);
		auto ind = std::shared_ptr<ME::IndexBuffer>(ME::IndexBuffer::create(indices, sizeof(indices)));
		vertex = std::shared_ptr<ME::VertexArray>(ME::VertexArray::create());
		vertex->addVertexBuffer(buf);
		vertex->setIndexBuffer(ind);




		float vertices2[4*3] = {
			-0.75f, -0.75f, 0.0f,
			-0.75f, 0.75f, 0.0f,
			0.75f, 0.75f, 0.0f,
			0.75f, -0.75f, 0.0f
		};
		ME::BufferLayout layout2 = {

			{ME::ShaderType::Vec3, "m_Position"},
			
		};

		uint32_t indices2[6] = {
			0, 1, 2,
			0, 2, 3
		};
		auto buf2 = std::shared_ptr<ME::VertexBuffer>(ME::VertexBuffer::create(vertices2, sizeof(vertices2)));
		buf2->setLayout(layout2);
		auto ind2 = std::shared_ptr<ME::IndexBuffer>(ME::IndexBuffer::create(indices2, sizeof(indices2)));
		square = std::shared_ptr<ME::VertexArray>(ME::VertexArray::create());
		square->addVertexBuffer(buf2);
		square->setIndexBuffer(ind2);
		
		const std::string& a = R"(#version 410 core
			layout(location = 0) in vec3 position;
			layout(location = 1) in vec4 color1;
			uniform mat4 u_proj;

			out vec4 color;

			void main() {
				color = color1;
				gl_Position = u_proj * vec4(position,1);
			}
		)";
		const std::string& b = R"(#version 410 core
			in vec4 color;
			
			void main() {
			
				gl_FragColor = color;

			}
		)";
		shader.reset(new ME::Shader(a, b));

		const std::string& a2 = R"(#version 410 core
			layout(location = 0) in vec3 position;
			out vec4 color;
			uniform mat4 u_proj;

			void main() {
				color = vec4(0.2f, 0.3f, 0.0f,1.0f);
				gl_Position = u_proj * vec4(position,1);
			}
		)";
		const std::string& b2 = R"(#version 410 core
			in vec4 color;
			
			void main() {
			
				gl_FragColor = color;

			}
		)";
		shader2.reset(new ME::Shader(a2, b2));
	
	};

	virtual void onGUIRender() override {
		

	}

	void onUpdate() override {
		float offset = (1.0f / 144.0f) * 60.0f;
		if (ME::Input::isKeyPress(ME_KEY_W)) {
			cam.move(cam.getForward(), 0.1 * offset);
		}

		if (ME::Input::isKeyPress(ME_KEY_Q)) {
			cam.rotate({ 0,0,1 }, 2 * offset);
		}

		if (ME::Input::isKeyPress(ME_KEY_E)) {
			cam.rotate({ 0,0,-1 }, 2 * offset);
		}
		if (ME::Input::isKeyPress(ME_KEY_S)) {
			cam.move(cam.getBackward(), 0.1 * offset);
		}
		if (ME::Input::isKeyPress(ME_KEY_A)) {
			cam.move(cam.getLeft(), 0.1 * offset);
		}
		if (ME::Input::isKeyPress(ME_KEY_D)) {
			cam.move(cam.getRight(), 0.1 * offset);
		}

		if (ME::Input::isKeyPress(ME_KEY_UP)) {
			cam.move({0,-1,0}, 0.1 * offset);
		}
		if (ME::Input::isKeyPress(ME_KEY_DOWN)) {
			cam.move({0,1,0}, 0.1 * offset);
		}
		if (ME::Input::isKeyPress(ME_KEY_LEFT)) {
			cam.move({1,0,0}, 0.1 * offset);
		}
		if (ME::Input::isKeyPress(ME_KEY_RIGHT)) {
			cam.move({-1,0,0}, 0.1 * offset);
		}
		//ME_CLIENT_INFO("ExampleLayer::onUpdate");
	}
	
	bool init = false;
	void onRender() override {
		
		RC::setClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		RC::clear();
		R::beginScene(cam);
		
		R::submit(shader2, square);
		
		R::submit(shader, vertex);
		
		R::endScene();
	}

	bool onEvent(ME::Events& e) override {
	
		return true;
	}
};

class Sandbox : public ME::Application {
public:
	
	Sandbox() {
		pushLayer(new ExampleLayer());
	
	}
	~Sandbox() {

	}
};

ME::Application* ME::CreateApplication() {
	return new Sandbox();
}