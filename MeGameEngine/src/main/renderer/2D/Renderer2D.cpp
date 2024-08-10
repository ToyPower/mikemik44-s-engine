#include <hzpch.h>
#include "Renderer2D.h"
ME::Vertex create2(const glm::vec3& pos, const glm::vec2& texCoord) {
	ME::Vertex v(pos);
	v.putData("texCoord", texCoord);
	return v;
}
namespace ME {
	float Renderer2D::rot = 0;
	glm::vec3 Renderer2D::pos = glm::vec3(0,0,0);

	Ref<Texture> Renderer2D::whiteTex = nullptr;
	struct Renderer2DStorage {
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
		whiteTex = Texture2D::create(1, 1);
		uint32_t whiteTexData = 0xffffffff;
		whiteTex->setPixels(&whiteTexData, sizeof(uint32_t));
		storage = new Renderer2DStorage();

		storage->tex_mesh = Ref<Mesh>(new Mesh());
		storage->tex_mesh->addVertex(create2({ 0.0f, 0.0f, 0.0f }, {0, 1}));
		storage->tex_mesh->addVertex(create2({ 0.0f, 1.0f, 0.0f }, {0,0}));
		storage->tex_mesh->addVertex(create2({ 1.0f, 1.0f, 0.0f }, {1,0}));
		storage->tex_mesh->addVertex(create2({ 1.0f, 0.0f, 0.0f }, {1,1}));
		storage->tex_mesh->addSquare(0, 1, 2, 3);
		storage->tex_mesh->getMaterial()->tex = whiteTex;

		storage->shader = Shader::create("assets/shaders/data.shader");
		
	}

	void Renderer2D::shutdown() {
		delete storage;
		storage = nullptr;
	}

	void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
		drawQuad(glm::vec3(position, 0), size, color);
	}

	void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {

		storage->tex_mesh->getTransform().setPos(position + pos);
		storage->tex_mesh->getTransform().setRotation(glm::vec3(0, 0, rot));
		storage->tex_mesh->getTransform().setScale(size);
		storage->tex_mesh->getMaterial()->albeto = color;
		Renderer::submit(storage->shader, storage->tex_mesh);

	}

	void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture> texture2D, const glm::vec4& color, float tileFactor) {
		drawQuad(glm::vec3(position, 1), size, texture2D, color, tileFactor);
	}

	void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture> texture2D, const glm::vec4& color, float tileFactor) {
		storage->tex_mesh->getTransform().setPos(position + pos);
		storage->tex_mesh->getTransform().setRotation(glm::vec3(0, 0, rot));
		storage->tex_mesh->getTransform().setScale(size);

		storage->tex_mesh->getMaterial()->albeto = color;
		storage->tex_mesh->getMaterial()->tex = texture2D;
		storage->shader->bind();
		storage->shader->setUniformFloat("u_tileFactor", tileFactor);
		Renderer::submit(storage->shader, storage->tex_mesh, true);
		storage->shader->unbind();
		storage->tex_mesh->getMaterial()->tex = whiteTex;

	}

	void Renderer2D::drawQuadCentered(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
		drawQuadCentered(glm::vec3(position, 0), size, color);
	}

	void Renderer2D::drawQuadCentered(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {

		storage->tex_mesh->getTransform().setPos(position + pos);
		storage->tex_mesh->getTransform().setRotation(glm::vec3(0, 0, rot));
		storage->tex_mesh->getTransform().setScale(size);
		storage->tex_mesh->getMaterial()->albeto = color;
		Renderer::submit(storage->shader, storage->tex_mesh);

	}

	void Renderer2D::drawQuadCentered(const glm::vec2& position, const glm::vec2& size, const Ref<Texture> texture2D, const glm::vec4& color, float tileFactor) {
		drawQuadCentered(glm::vec3(position, 1), size, texture2D, color, tileFactor);
	}

	void Renderer2D::drawQuadCentered(const glm::vec3& position, const glm::vec2& size, const Ref<Texture> texture2D, const glm::vec4& color, float tileFactor) {
		storage->tex_mesh->getTransform().setPos(position + pos);
		storage->tex_mesh->getTransform().setRotation(glm::vec3(0, 0, rot));
		storage->tex_mesh->getTransform().setScale(size);

		storage->tex_mesh->getMaterial()->albeto = color;
		storage->tex_mesh->getMaterial()->tex = texture2D;
		storage->shader->bind();
		storage->shader->setUniformFloat("u_tileFactor", tileFactor);
		Renderer::submit(storage->shader, storage->tex_mesh, true);
		storage->shader->unbind();
		storage->tex_mesh->getMaterial()->tex = whiteTex;

	}


}
