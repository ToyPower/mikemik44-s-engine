#include <hzpch.h>
#include "Renderer2D.h"
ME::Vertex create2(const glm::vec3& pos, const glm::vec2& texCoord) {
	ME::Vertex v(pos);
	v.putData("texCoord", texCoord);
	return v;
}
namespace ME {

	struct Renderer2DStorage {
		Ref<Mesh> mesh;
		Ref<Mesh> tex_mesh;
		Ref<Shader> shader;
	};
	static Renderer2DStorage* storage = nullptr;
	
	bool Renderer2D::hasInit() {
		return storage == nullptr;
	}

	void Renderer2D::init() {
		if (storage != nullptr) {
			return;
		}
		
		storage = new Renderer2DStorage();
		storage->mesh = Ref<Mesh>(new Mesh());
		storage->mesh->addVertex(Vertex({ -0.5f, -0.5f, 0.0f }));
		storage->mesh->addVertex(Vertex({ -0.5f, 0.5f, 0.0f }));
		storage->mesh->addVertex(Vertex({ 0.5f, 0.5f, 0.0f }));
		storage->mesh->addVertex(Vertex({ 0.5f, -0.5f, 0.0f }));
		storage->mesh->addSquare(0, 1, 2, 3);

		storage->tex_mesh = Ref<Mesh>(new Mesh());
		storage->tex_mesh->addVertex(create2({ -0.5f, -0.5f, 0.0f }, {0, 1}));
		storage->tex_mesh->addVertex(create2({ -0.5f, 0.5f, 0.0f }, {0,0}));
		storage->tex_mesh->addVertex(create2({ 0.5f, 0.5f, 0.0f }, {1,0}));
		storage->tex_mesh->addVertex(create2({ 0.5f, -0.5f, 0.0f }, {1,1}));
		storage->tex_mesh->addSquare(0, 1, 2, 3);


		storage->shader = Shader::create("assets/shaders/data.shader");
		
	}

	void Renderer2D::shutdown() {
		delete storage;
		storage = nullptr;
	}

	void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
		drawQuad(glm::vec3(position, 1), size, color);
	}

	void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
		storage->mesh->getMaterial()->tex = nullptr;
		storage->mesh->getTransform().setPos(position);
		storage->mesh->getTransform().setScale(size);
		storage->mesh->getMaterial()->albeto = color;
		Renderer::submit(storage->shader, storage->mesh);

	}

	void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture> texture2D, const glm::vec4& color) {
		drawQuad(glm::vec3(position, 1), size, texture2D, color);
	}

	void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture> texture2D, const glm::vec4& color) {
		storage->tex_mesh->getTransform().setPos(position);
		storage->tex_mesh->getTransform().setScale(size);
		
		storage->tex_mesh->getMaterial()->albeto = color;
		storage->tex_mesh->getMaterial()->tex = texture2D;
		storage->shader->bind();
		storage->shader->setUniformBool("u_hasTexture", true);
		Renderer::submit(storage->shader, storage->tex_mesh, true);
		storage->shader->setUniformBool("u_hasTexture", false);
		storage->shader->unbind();

	}


}
