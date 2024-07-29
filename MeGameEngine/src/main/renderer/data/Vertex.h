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
			std::map<const std::string, glm::vec4>::iterator it = data4.begin();
			while (it != data4.end()) {
				glm::vec4 ref = it->second;
				arr.push_back(ref.x);
				arr.push_back(ref.y);
				arr.push_back(ref.z);
				arr.push_back(ref.w);
				++it;
			}
			std::map<const std::string, glm::vec3>::iterator it2 = data3.begin();
			while (it2 != data3.end()) {
				glm::vec4 ref = it->second;
				arr.push_back(ref.x);
				arr.push_back(ref.y);
				arr.push_back(ref.z);
				++it2;
			}
			std::map<const std::string, glm::vec2>::iterator it3 = data2.begin();
			while (it3 != data2.end()) {
				glm::vec4 ref = it->second;
				arr.push_back(ref.x);
				arr.push_back(ref.y);
				++it3;
			}
		}

		void putData(const std::string ref, glm::vec2 data) {
			data2[ref] = data;
			up = true;
			size += 4 * 2;
		}

		void putData(const std::string ref, glm::vec3 data) {
			data3[ref] = data;
			up = true;
			size += 4 * 3;
		}

		void putData(const std::string ref, glm::vec4 data) {
			data4[ref] = data;
			up = true;
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
				allElem.push_back({ShaderType::Vec3, "position"});
				std::map<const std::string, glm::vec4>::iterator it = data4.begin();
				while (it != data4.end()) {
					const std::string ref = it->first;
					allElem.push_back({ ShaderType::Vec4, ref });
					++it;
				}
				std::map<const std::string, glm::vec3>::iterator it2 = data3.begin();
				while (it2 != data3.end()) {
					const std::string ref = it2->first;
					allElem.push_back({ ShaderType::Vec3, ref });
					++it2;
				}
				std::map<const std::string, glm::vec2>::iterator it3 = data2.begin();
				while (it3 != data2.end()) {
					const std::string ref = it3->first;
					allElem.push_back({ ShaderType::Vec4, ref });
					++it3;
				}
				
				layout = BufferLayout(std::initializer_list<BufferElements>(&allElem.front(), &allElem.front() + allElem.size()));
				
			}
			return layout;
		}
		operator glm::vec3() const {return pos; }
	private:
		uint32_t size = 0;
		bool up = true;
		glm::vec3 pos;
		BufferLayout layout;
		std::map<const std::string, glm::vec4> data4;
		std::map<const std::string, glm::vec3> data3;
		std::map<const std::string, glm::vec2> data2;
	};

}
