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
glm::mat4 getYaw1(float angle) {
	return glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0, 1, 0));
}
glm::mat4 getPitch1(float angle) {
	return glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(1, 0, 0));
}
glm::mat4 getRoll1(float angle) {
	return glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0, 0, 1));
}
glm::mat4 rotatea1(const glm::vec3& rot) {
	return getYaw1(rot.x) * getPitch1(rot.y) * getRoll1(rot.z);
}
glm::vec3 rotate3(const glm::vec3& vec, const glm::mat4& matrix) {
	glm::vec4 tmp = glm::vec4(vec, 1);
	tmp = matrix * tmp;
	return glm::vec3(tmp.x, tmp.y, tmp.z);
}

namespace ME {

	PerspectiveCamera::PerspectiveCamera(float fov, float width, float height, float near1, float far1) : m_projection(glm::perspectiveFov(glm::radians(fov), width, height, near1, far1)), far1(far1), near1(near1), fov(fov), m_width(width), m_height(height), m_bounds(Bounds()) {
		view = glm::mat4(1.0f);
		fin = m_projection * view;
		m_bounds.left = -1;
		m_bounds.right = 1;
		m_bounds.top = -1.0f;
		m_bounds.bottom = 1.0f;
	}

	void PerspectiveCamera::onResize(float width, float height) {
		if (this->m_width != width || this->m_height != height) {
			this->m_width = width;
			this->m_height = height;
			m_projection = glm::perspectiveFov(glm::radians(fov), width, height, near1, far1);
			fin = m_projection * view;
		}
	}

	void PerspectiveCamera::updateData() {
		glm::mat4 rotation = rotatea1(rot);
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * rotation;
		forward = glm::vec3(0, 0, 1);
		backward = glm::vec3(0, 0, -1);
		left = glm::vec3(1, 0, 0);
		right = glm::vec3(-1, 0, 0);
		forward = rotate3(forward, rotation);
		backward = rotate3(backward, rotation);
		left = rotate3(left, rotation);
		right = rotate3(right, rotation);
		
		up = glm::vec3(0,1,0);
		down = glm::vec3(0,-1,0);
		up = rotate3(up, rotation);
		down = rotate3(down, rotation);
		view = glm::lookAtLH(pos, pos + forward, glm::vec3(0, 1, 0));
		fin = m_projection * view;
		forward *= -1;
		backward *= -1;
	}

	OthrographicCamera::OthrographicCamera(float aspect) : zoom1(1.0f), aspect(aspect), m_projection(glm::ortho(-aspect, aspect, -1.0f, 1.0f)) {
		m_bounds.left = -aspect;
		m_bounds.right = aspect;
		m_bounds.top = -1.0f;
		m_bounds.bottom = 1.0f;
		view = glm::mat4(1.0f);
		fin = m_projection * view;

	}

	OthrographicCamera::OthrographicCamera(float width, float height) : zoom1(1.0f), aspect(width/height), m_projection(glm::ortho(-width/height, width/height, -1.0f, 1.0f)) {
		view = glm::mat4(1.0f);
		fin = m_projection * view;
		m_bounds.left = -width/height;
		m_bounds.right = width/height;
		m_bounds.top = -1.0f;
		m_bounds.bottom = 1.0f;
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


}