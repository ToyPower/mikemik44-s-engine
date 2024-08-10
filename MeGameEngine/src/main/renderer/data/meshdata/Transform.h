#pragma once

#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

namespace ME {

	class Transform {

	public:
		glm::mat4 getYaw(float angle) {
			return glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0, 1, 0));
		}
		glm::mat4 getPitch(float angle) {
			return glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(1, 0, 0));
		}
		glm::mat4 getRoll(float angle) {
			return glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0, 0, 1));
		}
		glm::mat4 rotatea(const glm::vec3& rot) {
			return getYaw(rot.x) * getPitch(rot.y) * getRoll(rot.z);
		}
		Transform(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& rotation = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& scale = glm::vec3(1,1,1)) {
			this->pos = position;
			this->rot = rotation;
			this->scale = scale;
			this->op = glm::vec3(position);
			this->oo = glm::vec3(rotation);
			this->os = glm::vec3(scale);
			this->translate = glm::translate(glm::mat4(1.0f), position);
			this->rotates = rotatea(rot);
			
			this->scalar = glm::scale(glm::mat4(1.0f), scale);
			this->ro = this->rotates * this->scalar;
			this->fin = this->translate * this->ro;
			
		}

		inline glm::vec3& getPosition() {

			return this->pos;

		}

		inline const glm::vec3& getRotation() const {

			return this->rot;

		}

		inline const glm::vec3& getScale() const {

			return this->scale;

		}

		void move(const glm::vec3& movement, float amt = 1) {
			this->pos += movement * amt;
		}

		void move(const glm::vec2 movement, float amt = 1) {
			this->pos += glm::vec3(movement,0)* amt;
		}

		void setPos(const glm::vec3& pos) {
			this->pos = pos;
		}

		void setPos(const glm::vec2& pos) {
			this->pos = glm::vec3(pos,1);
		}

		void rotate(const glm::vec3& angles, float amt = 1) {
			this->rot += angles * amt;
		}

		void setRotation(const glm::vec3& angles) {
			this->rot = angles;
			
		}

		void setScale(const glm::vec3& scale) {
			this->scale = scale;
		}
		void setScale(const glm::vec2& scale) {
			this->scale = glm::vec3(scale, 1);
		}
		bool match(glm::vec3 a, glm::vec3 b) {
			return a.x == b.x && a.y == b.y && a.z == b.z;
		}
		glm::mat4 getMeshMatrix() {
			bool alt = false;
			if (!match(pos, op)) {
				translate = glm::translate(glm::mat4(1.0f), pos);
				op.x = pos.x;
				op.y = pos.y;
				op.z = pos.z;
				alt = true;
			}
			bool ch = false;
			if (!match(rot, oo)) {
				rotates = rotatea(rot);
				oo.x = rot.x;
				oo.y = rot.y;
				oo.z = rot.z;
				ch = true;
			}

			if (!match(scale, os)) {
				scalar = glm::scale(glm::mat4(1.0f), scale);
				os.x = scale.x;
				os.y = scale.y;
				os.z = scale.z;
				ch = true;
			}

			if (ch) {
				ro = rotates * scalar;
				fin = translate * ro;
			}
			else if(alt) {
				fin = translate * scalar;
			}
			
			return fin;
		}

	private:
		glm::mat4 translate, rotates, scalar, ro, fin;
		glm::vec3 pos, rot, scale, op, oo, os;
	};

}
