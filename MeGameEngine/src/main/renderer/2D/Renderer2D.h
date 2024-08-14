#pragma once
#include "main/renderer/shaders/Shader.h"
#include "main/renderer/renderer/main/Renderer.h"
#include "main/renderer/renderer/main/RendererContent.h"
#include "main/renderer/data/camera/Camera.h"
namespace ME {

	class Renderer2D {

	public:
		
		static void flush();
		static void beginScene(Ref<Camera> cam);
		static void endScene();
		static void clear(glm::vec4 color = glm::vec4(0, 0, 0,1)) { ME::RendererContent::setClearColor(color); ME::RendererContent::clear(); };
		static void init();
		static void shutdown();
		static void drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void drawQuadCentered(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void drawQuadCentered(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void rotate(float amt, bool isRadians = true) {
			if (isRadians) {
				rot += amt;
			}
			else {
				rot += glm::radians(amt);
			}
		}
		static void setRotation(float angle, bool isRadians = true) {
			if (!isRadians) {
				rot = glm::radians(angle);
			}
			else {
				rot = angle;
			}
		}
		static void translate(const glm::vec3& movement) {
			pos += movement;
		}
		static void setTranslation(const glm::vec3& position) {
			pos = position;
		}

		static void drawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture> texture2D, const glm::vec4& color = glm::vec4(1, 1, 1, 1), float tileFactor = 1.0f);
		static void drawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture> texture2D, const glm::vec4& color = glm::vec4(1, 1, 1, 1), float tileFactor = 1.0f);
		static void drawQuadCentered(const glm::vec2& position, const glm::vec2& size, const Ref<Texture> texture2D, const glm::vec4& color = glm::vec4(1, 1, 1, 1), float tileFactor = 1.0f);
		static void drawQuadCentered(const glm::vec3& position, const glm::vec2& size, const Ref<Texture> texture2D, const glm::vec4& color = glm::vec4(1, 1, 1, 1), float tileFactor = 1.0f);
		static bool hasInit();
		static void flushAndReset();
	private:
		static Ref<Texture> whiteTex;
		static float rot;
		static glm::vec3 pos;
		
	};

}