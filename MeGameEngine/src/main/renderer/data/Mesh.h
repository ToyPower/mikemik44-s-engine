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
		Mesh(Transform& trans = Transform(), Material& mat = Material()) : trans(trans), mat(mat){}
		
		Transform& getTransform() {
			return trans;
		}

		Material& getMaterial() {
			return mat;
		}

		uint32_t* addVertex(Vertex& pos) {
			uint32_t place = vertices.size();

			pos.addData(vertices);
		
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

		std::shared_ptr<VertexArray> getVertexArray() {
			if (updated) {
				updated = false;
				std::vector<float> all = {};
				all.push_back(-0.5f);
				all.push_back(-0.5f);
				all.push_back(0.0f);

				all.push_back(-0.5f);
				all.push_back(0.5f);
				all.push_back(0.0f);

				all.push_back(0.5f);
				all.push_back(0.5f);
				all.push_back(0.0f);

				uint32_t inn[3] = {
					0,1,2
				};
				
				std::shared_ptr<VertexBuffer> buf = std::shared_ptr<VertexBuffer>(VertexBuffer::create(vertices.data(), vertices.size() * sizeof(vertices.data())));
				buf->setLayout(tmp);
				res.reset(VertexArray::create());
				res->addVertexBuffer(buf);
				res->setIndexBuffer(std::shared_ptr<IndexBuffer>(IndexBuffer::create(indices.data(), indices.size() * sizeof(indices.data()))));
			}
			return res;
		}
	private:
		Transform trans;
		Material mat;

		BufferLayout tmp;
		std::vector<float> vertices = {};
		std::vector<uint32_t> indices = {};
		std::shared_ptr<VertexArray> res;
		bool updated = true;
	};
}
