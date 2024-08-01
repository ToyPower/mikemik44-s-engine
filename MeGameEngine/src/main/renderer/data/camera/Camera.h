#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>
namespace ME {
	class Camera {
	public:
		virtual void updateData() = 0;
		virtual const glm::mat4 getProjection() const = 0;
		virtual const glm::mat4 getView() const = 0;
		virtual const glm::mat4 getViewProjection() const = 0;
		virtual const glm::vec3 getForward() const = 0;
		virtual const glm::vec3 getBackward() const = 0;
		virtual const glm::vec3 getUp() const = 0;
		virtual const glm::vec3 getDown() const = 0;
		virtual const glm::vec3 getLeft() const = 0;
		virtual const glm::vec3 getRight() const = 0;
		virtual void setPosition(const glm::vec3& pos) = 0;
		virtual void move(const glm::vec3& movement, float amt = 1) = 0;
		virtual void setRotation(glm::vec3 rot) = 0;
		virtual void rotate(const glm::vec3& angles, float amt = 1) = 0;
		virtual glm::vec3 getPosition() = 0;
		virtual void onResize(float width, float height) = 0;
		virtual glm::vec3 getRotation() = 0;
		virtual void zoom(float zoomValue) = 0;
		virtual void setZoom(float zoomValue) = 0;
	};

	class PerspectiveCamera : public Camera {
	public:
		PerspectiveCamera(float fov, float width, float height, float near1 = 0.1, float far1 = 100.0);
		
		virtual void onResize(float width, float height) override;
		virtual const glm::mat4 getProjection() const override { return m_projection; }
		virtual const glm::mat4 getView() const  override { return view; }
		virtual const glm::mat4 getViewProjection() const override { return fin; }
		virtual const glm::vec3 getForward() const override { return forward; }
		virtual const glm::vec3 getBackward() const override { return backward; }
		virtual const glm::vec3 getUp() const override { return up; }
		virtual const glm::vec3 getDown() const override { return down; }
		virtual const glm::vec3 getLeft() const override { return right; }
		virtual const glm::vec3 getRight() const override { return left; }
		virtual void setFov(float fov) { this->fov = fov; updatePerspective(); }
		virtual void setNear(float near1) { this->near1 = near1; updatePerspective(); }
		virtual void setFar(float far1) { this->far1 = far1; updatePerspective(); }
		void updatePerspective() {
			m_projection = glm::perspectiveFov(glm::radians(fov*zoom1), m_width, m_height, near1, far1);
			fin = m_projection * view;
		}
		virtual void zoom(float zoomValue) override {
			this->zoom1 = std::clamp(this->fov - zoomValue,0.15f, 10.0f);
			updatePerspective();
		}
		virtual void setZoom(float zoomValue) override {
			this->zoom1 = std::clamp(zoomValue, 0.15f, 10.0f);
			updatePerspective();
		}
		virtual void setPosition(const glm::vec3& pos)  override { this->pos = pos; updateData();
		}
		virtual void setRotation(glm::vec3 rot)  override { this->rot = rot; updateData(); checkRot(this->rot);
		}
		virtual void move(const glm::vec3& movement, float amt = 1) override {
			this->pos += movement * amt;
			updateData();
		}
		void checkRot(glm::vec3& ref) {
			if (ref.x >= 360) ref.x -= 360;
			if (ref.y >= 360) ref.y -= 360;
			if (ref.z >= 360) ref.z -= 360;
			if (ref.x < 0) ref.x += 360;
			if (ref.y < 0) ref.y += 360;
			if (ref.z < 0) ref.z += 360;
		}
		virtual void rotate(const glm::vec3& angles, float amt = 1) override {
			this->rot += (angles * amt);
			checkRot(this->rot);
			updateData();
		}
		virtual glm::vec3 getPosition() override {
			return pos;
		}
		virtual glm::vec3 getRotation() override { return rot; 
		}
		void updateData();

		glm::mat4 m_projection, m_rot, view, fin;
		glm::vec3 forward = { 0,-1,0 }, left = { 1,0,0 },	right = { -1,0,0 }, backward = { 0,1,0 }, up = { 0,-1,0 }, down = { 0,1,0 };
		glm::vec3 pos = { 0,0,0 };
		glm::vec3 rot = { 0, 0, 0 };
		float fov = 40.0f, near1 = 0.1f, far1 = 100.0f, zoom1 = 1.0f;
		float m_width, m_height;
	};

	class OthrographicCamera : public Camera {

	public:
		OthrographicCamera(float aspect);
		OthrographicCamera(float width, float height);
		
		virtual const glm::mat4 getProjection() const override { return m_projection; }
		virtual const glm::mat4 getView() const  override { return view; }
		virtual const glm::mat4 getViewProjection() const override { return fin; }
		virtual const glm::vec3 getForward() const override { return forward; }
		virtual const glm::vec3 getBackward() const override { return backward; }
		virtual const glm::vec3 getUp() const override { return up; }
		virtual const glm::vec3 getDown() const override { return down; }
		virtual const glm::vec3 getLeft() const override { return right; }
		virtual const glm::vec3 getRight() const override { return left; }
		virtual void setPosition(const glm::vec3& pos)  override { this->pos = pos; updateData();}
		virtual void setRotation(glm::vec3 rot)  override { this->rot = rot.z; updateData();}
		virtual void move(const glm::vec3& movement, float amt = 1) override {
			this->pos += movement * amt;
			updateData();
		}
		virtual void rotate(const glm::vec3& angles, float amt = 1) override {
			this->rot += amt * angles.z;
		
			updateData();
		}
		void updatePerspective() {
			m_projection = glm::ortho(-aspect * zoom1, aspect * zoom1, zoom1, -zoom1);
			fin = m_projection * view;
		}
		virtual void zoom(float zoomValue) override {
			this->zoom1 = std::clamp(this->zoom1 - zoomValue, 0.15f, 10.0f);
			updatePerspective();
		}
		virtual void setZoom(float zoomValue) override {
			this->zoom1 = std::clamp(zoomValue, 0.15f, 10.0f);
			
			updatePerspective();
		}
		virtual void onResize(float width, float height) override {
			aspect = width / height;
			updatePerspective();
		}
		virtual glm::vec3 getPosition() override { return pos; }
		virtual glm::vec3 getRotation() override { return glm::vec3(0, 0, rot);  }
		void updateData();
	private:
		float aspect = 1;
		glm::mat4 m_projection, view, fin;
		glm::vec3 forward = { 0,-1,0 }, left = { 1,0,0 }, right = { -1,0,0 }, backward = { 0,1,0 }, up = { 0,-1,0 }, down = { 0,1,0 };
		glm::vec3 pos = { 0,0,0 };
		float rot = 0.0f;
		float zoom1 = 0;
		
	};

}