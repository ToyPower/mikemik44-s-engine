#pragma once
#include <hzpch.h>
#include "glm/glm.hpp"
namespace ME {

	class Vertex {
	public:
		uint32_t getSize() {
			return size;
		}
		Vertex(const glm::vec3& pos) : pos(pos) {
			this->data2 = {};
			this->data3 = {};
			this->data4 = {};
			size += 4 * 3;
		}

		void addData( std::vector<float>& arr) {
			arr.push_back(pos.x);
			arr.push_back(pos.y);
			arr.push_back(pos.z);
			for (uint32_t i = 0; i < list.size(); i++) {
				const std::string ref = list[i];
				uint32_t j = list2[i];
				if (j == 2) {
					auto h = data2[ref];
					arr.push_back(h.x);
					arr.push_back(h.y);
				}
				else if (j == 3) {
					auto h = data3[ref];
					arr.push_back(h.x);
					arr.push_back(h.y);
					arr.push_back(h.z);
				}
				else if (j == 4) {
					auto h = data4[ref];
					arr.push_back(h.x);
					arr.push_back(h.y);
					arr.push_back(h.z);
					arr.push_back(h.w);
				}
			}
		}

		void putData(std::string ref, glm::vec2 data) {
			data2[ref] = data;
			up = true;
			size += 4 * 2;
			if (!cont(ref)) {
				list.push_back(ref);
				list2.push_back(2);
			}
		}

		

		void putData(std::string ref, glm::vec3 data) {
			data3[ref] = data;
			up = true;
			size += 4 * 3;
			if (!cont(ref)) {
				list.push_back(ref);
				list2.push_back(3);
			}
		}

		void putData(std::string ref, glm::vec4 data) {
			data4[ref] = data;
			up = true;
			if (!cont(ref)) {
				list.push_back(ref);
				list2.push_back(4);
			}
			size += 4 * 4;
		}

		bool hadData2(const std::string ref) {
			return data2.find(ref) != data2.end();
		}

		bool hadData3(const std::string ref) {
			return data3.find(ref) != data3.end();
		}

		bool hadData4(const std::string ref) {
			return data4.find(ref) != data4.end();
		}

		glm::vec2& getData2(const std::string ref) {
			return data2[ref];
		}

		glm::vec3& getData3(const std::string ref) {
			return data3[ref];
		}

		glm::vec4& getData4(const std::string ref) {
			return data4[ref];
		}

		std::map<const std::string, glm::vec2>& getData2() {
			return data2;
		}

		std::map<const std::string, glm::vec3>& getData3() {
			return data3;
		}

		std::map<const std::string, glm::vec4>& getData4() {
			return data4;
		}

		glm::vec3& getPos() { return pos; }
		void setPos(const glm::vec3& pos) { this->pos = pos; }
		BufferLayout getLayout() {
			if (up) {
				up = false;
				std::vector<BufferElements> allElem;
				allElem.push_back({ ShaderType::Vec3, "m_position" });
				for (uint32_t i = 0; i < list.size(); i++) {
					std::string ref = list[i];
					uint32_t j = list2[i];
					if (j == 2) {
						allElem.push_back({ ShaderType::Vec2, ref });
					}
					else if (j == 3) {
						allElem.push_back({ ShaderType::Vec3, ref });
					}
					else if (j == 4) {
						allElem.push_back({ ShaderType::Vec4, ref });
					}
				}
				
				layout = BufferLayout(std::initializer_list<BufferElements>(&allElem.front(), &allElem.front() + allElem.size()));
				
			}
			return layout;
		}
		operator glm::vec3() const {return pos; }
	private:
		bool cont(std::string& str) {
			if (std::find(list.begin(), list.end(), str) != list.end()) {
				return true;
			}
			return false;
		}
		uint32_t size = 0;
		bool up = true;
		glm::vec3 pos;
		BufferLayout layout;
		std::map<const std::string, glm::vec4> data4;
		std::map<const std::string, glm::vec3> data3;
		std::map<const std::string, glm::vec2> data2;
		std::vector<std::string> list = {};
		std::vector<uint32_t> list2 = {};
	};

}
