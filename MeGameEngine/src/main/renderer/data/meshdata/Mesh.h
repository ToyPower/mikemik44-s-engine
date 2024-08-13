#pragma once
#include <hzpch.h>
#include <glm/glm.hpp>
#include "Transform.h"
#include "Material.h"
#include "main/renderer/buffers/VertexArray.h"
#include "main/renderer/buffers/Buffers.h"
#include "main/renderer/data/Vertex.h"
namespace ME {
	
	class Mesh {
	public:
		void clear() {
			vertices.clear();
			indices.clear();
			this->trans.setPos({ 0,0,0 });
			this->trans.setRotation({ 0,0,0 });
			this->trans.setScale({ 1,1,1 });
			updated = true;
		}
		Mesh(Transform& trans = Transform(), Ref<Material> mat = Ref<Material>()) : trans(trans), mat(mat){
			mat = (getMaterialFromBase("Base"));
		}
		
		void loadFromString(const std::string& str) {

		}
		void setMaterial(Ref<Material> mat) {
			this->mat = mat;
		}

		void setTransform(const Transform& trans) {
			this->trans = trans;
		}

		std::string toString() {
			return std::string("");
		}

		Transform& getTransform() {
			return trans;
		}

		Ref<Material> getMaterial() {
			if (mat.get() == getMaterialFromBase("Base").get()) {
				mat = Ref<Material>(new Material());
			}

			if (mat == nullptr) {
				mat = Ref<Material>(new Material());
			}

			return mat;
		}

		uint32_t* addVertex(Vertex& pos) {
			uint32_t place = vertices.size();
			
			pos.addData(vertices);
			actPos.push_back(glm::vec3(pos.getPos().x, pos.getPos().y, pos.getPos().z));
			uint32_t placee = vertices.size();
			tmp = pos.getLayout();
			return new uint32_t[2]{ place, placee };
		}

		void addVertexArray(Vertex* pos, uint32_t size) {
			for (uint32_t i = 0; i < size; i++) {
				addVertex(pos[i]);
			}
		}

		uint32_t findVertex(glm::vec3 pos) {
			for (uint32_t i = 0; i < vertices.size(); i += 3) {

				if (pos.x == vertices[i] && pos.y == vertices[i + 1] && pos.z == vertices[i + 2]) {
					return i;
				}
			}
			return -1;
		}

		void addTriangle(uint32_t a, uint32_t b, uint32_t c) {
			indices.push_back(a);
			indices.push_back(b);
			indices.push_back(c);
		}

		void addSquare(uint32_t a, uint32_t b, uint32_t c, uint32_t d) {
			addTriangle(a, b, c);
			addTriangle(a, c, d);
		}

		Ref<VertexArray> getVertexArray() {
			if (updated) {
				updated = false;

				Ref<VertexBuffer> buf = VertexBuffer::create(vertices.data(), vertices.size() * sizeof(vertices.data()));
				buf->setLayout(tmp);
				res = VertexArray::create();
				res->addVertexBuffer(buf);
				res->setIndexBuffer(IndexBuffer::create(indices.data(), indices.size()));
			}
			return res;
		}
		std::vector < glm::vec3>& getActPos() { return actPos; }
		std::vector<float>& getVertices() {
			return vertices;
		}
	private:
		Transform trans;
		Ref<Material> mat;
		BufferLayout tmp;
		std::vector<float> vertices = {};
		std::vector<glm::vec3> actPos = {};
		std::vector<uint32_t> indices = {};
		Ref<VertexArray> res;
		uint32_t si = 0;
		bool updated = true;
	};
}
