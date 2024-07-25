#include <hzpch.h>
#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>
void rotate1(glm::vec3& ref, float angle) {
	float _x = cos(glm::radians(angle));
	float _y = sin(glm::radians(angle));
	float x = ref.x;
	float y = ref.y;
	float nx = x * _x - y * _y;
	float ny = y * _x + x * _x;
	ref.x = nx;
	ref.y = ny;
}

void rotate2(glm::vec3& ref, float angle) {
	float _x = sin(glm::radians(angle));
	float _y = cos(glm::radians(angle));
	float x = ref.y;
	float y = ref.x;
	float nx = x * _x + y * _y;
	float ny = y * _x - x * _x;
	ref.x = nx;
	ref.y = ny;
}

namespace ME {

	OthrographicCamera::OthrographicCamera(float left, float right, float bottom, float top) : m_projection(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)) {
		view = glm::mat4(1.0f);
		fin = m_projection * view;
	}
	
	void OthrographicCamera::updateData() {
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(rot), glm::vec3(0, 0, 1));
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * rotation;
		forward = glm::vec3(0, -1, 0);
		backward = glm::vec3(0, 1, 0);
		left = glm::vec3(1, 0, 0);
		right = glm::vec3(-1, 0, 0);
		rotate1(forward, rot);
		rotate1(backward, rot);
		rotate2(left, rot);
		rotate2(right, rot);

		up = forward;
		down = backward;
		view = glm::inverse(transform);
		fin = m_projection * view;
	}

	void OthrographicCamera::move(const glm::vec3& movement, float amt) {
		this->pos += movement * amt;
		updateData();
	}
	void OthrographicCamera::rotate(const glm::vec3& angles, float amt) {
		this->rot += angles.z* amt;
		updateData();
	}

}