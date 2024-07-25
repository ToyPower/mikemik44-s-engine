#pragma once
#include <glm/glm.hpp>
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
		virtual void setRotation(float rot) = 0;
		virtual void rotate(const glm::vec3& angles, float amt = 1) = 0;
		virtual glm::vec3 getPosition() = 0;
		virtual float getRotation() = 0;
	};
	class OthrographicCamera : public Camera{

	public:
		OthrographicCamera(float left = -1.0f, float right = 1.0f, float bottom = -1.0f, float top = 1.0f);
		void updateData();
		virtual const glm::mat4 getProjection() const override { return m_projection; }
		virtual const glm::mat4 getView() const  override { return view; }
		virtual const glm::mat4 getViewProjection() const override { return fin; }
		virtual const glm::vec3 getForward() const override { return forward; }
		virtual const glm::vec3 getBackward() const override { return backward; }
		virtual const glm::vec3 getUp() const override { return up; }
		virtual const glm::vec3 getDown() const override { return down; }
		virtual const glm::vec3 getLeft() const override { return left; }
		virtual const glm::vec3 getRight() const override { return right; }
		virtual void setPosition(const glm::vec3& pos)  override { this->pos = pos; updateData();}
		virtual void setRotation(float rot)  override { this->rot = rot; updateData(); }
		virtual void move(const glm::vec3& movement, float amt = 1) override;
		virtual void rotate(const glm::vec3& angles, float amt = 1) override;
		virtual glm::vec3 getPosition() override { return pos; }
		virtual float getRotation() override { return rot; }

	private: 
		glm::mat4 m_projection, view, fin;
		glm::vec3 forward = { 0,-1,0 }, left = { 1,0,0 }, right = { -1,0,0 }, backward = { 0,1,0 }, up = { 0,-1,0 }, down = { 0,1,0 };
		glm::vec3 pos = { 0,0,0 };
		float rot = 0.0f;
		
	};

}