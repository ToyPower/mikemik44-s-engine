#pragma once
#include "main/renderer/renderer/apistuff/RendererApi.h"
namespace ME {

	class OpenGLRendererAPI : public RendererAPI{

	public:
		virtual void init() override;
		virtual void clear() override;
		virtual void setClearColor(float r = 0, float g = 0, float b = 0, float a = 1.0f) override;
		virtual void setClearColor(glm::vec4& color = glm::vec4(0,0,0,1)) override;
		virtual void drawIndex(const Ref<VertexArray>& obj) override;
	};

}