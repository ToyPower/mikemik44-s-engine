#include <hzpch.h>
#include "Renderer2D.h"
#include <main/platform/opengl/shaders/OpenGLShader.h>
#include "main/renderer/renderer/SubTexture2D.h"
ME::Vertex create2(const glm::vec3& pos, const glm::vec2& texCoord) {
	ME::Vertex v(pos);
	v.putData("texCoord", texCoord);
	return v;
}
namespace ME {
	float Renderer2D::rot = 0;
	glm::vec3 Renderer2D::pos = glm::vec3(0,0,0);

	
	struct QuadVertex {

		glm::vec3 position;
		glm::vec4 color;
		glm::vec2 texCoord;
		float texIndex;
		float tileFactor = 1;

	};
	struct Render2DData {
		const uint32_t maxQuads = 20000;
		const uint32_t maxVert = maxQuads * 4;
		const uint32_t maxInd = maxQuads * 6;
		static const uint32_t maxTextures = 32;
	
		std::array<Ref<Texture>, maxTextures> texSlots;
		uint32_t texSlotIndex = 1;
		Ref<VertexArray> vertexArray;
		Ref<VertexBuffer> vertexBuffer;
		glm::vec4 quadVertices[4];
		Ref<Shader> shader;
		uint32_t indexCount = 0;
		QuadVertex* bufferBase = nullptr;
		QuadVertex* bufferPointer = nullptr;
	};
	
	static Render2DData qdata;
	static bool hinit = false;
	bool Renderer2D::hasInit() {
		return hinit;
	}

	void Renderer2D::init() {
		if (hinit) {
			return;
		}
		qdata.vertexArray = VertexArray::create();

		qdata.vertexBuffer = VertexBuffer::create(qdata.maxVert * sizeof(QuadVertex));
		qdata.vertexBuffer->setLayout(BufferLayout({
			{ShaderType::Vec3, "position"},
			{ShaderType::Vec4, "colour"},
			{ShaderType::Vec2, "texCoords"},
			{ShaderType::Float, "texIndex"},
			{ShaderType::Float, "tileFactor"},
			}));
		qdata.vertexArray->addVertexBuffer(qdata.vertexBuffer);
		
		qdata.bufferBase = new QuadVertex[qdata.maxVert];

		uint32_t* qind = new uint32_t[qdata.maxInd];
		
		uint32_t offset = 0;
		for (uint32_t i = 0; i < qdata.maxInd; i += 6) {

			qind[i + 0] = offset + 0;
			qind[i + 1] = offset + 1;
			qind[i + 2] = offset + 2;

			qind[i + 3] = offset + 0;
			qind[i + 4] = offset + 2;
			qind[i + 5] = offset + 3;
			

			offset += 4;
		}
		Ref<IndexBuffer> indexBuffer = IndexBuffer::create(qind, qdata.maxInd);
		qdata.vertexArray->setIndexBuffer(indexBuffer);
		delete[] qind;
		
		hinit = true;
		Ref<Texture2D> whiteTex = Texture2D::create(1, 1);
		uint32_t whiteTexData = 0xffffffff;
		whiteTex->setPixels(&whiteTexData, sizeof(uint32_t));
		whiteTex->bind();
		qdata.texSlots[0] = whiteTex;
		qdata.texSlotIndex = 1;
		qdata.shader = Shader::create("assets/shaders/data.shader");
		
		int32_t samplers[qdata.maxTextures ];
		for (uint32_t i = 0; i < qdata.maxTextures; i++) {
			samplers[i] = i;
		}
		qdata.shader->bind();
		qdata.shader->setUnfiromIntArray("u_tex", samplers, qdata.maxTextures);
		qdata.quadVertices[0] = glm::vec4(-0.5f, -0.5f, 0, 1);
		qdata.quadVertices[1] = glm::vec4(-0.5f, 0.5f, 0, 1);
		qdata.quadVertices[2] = glm::vec4(0.5f, 0.5f, 0, 1);
		qdata.quadVertices[3] = glm::vec4(0.5f, -0.5f, 0, 1);
	}

	void Renderer2D::shutdown() {
		
	}

	void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
		drawQuad(glm::vec3(position, 0), size, color);
	}

	void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
		if (qdata.indexCount >= qdata.maxInd) {
			flushAndReset();
		}
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position+pos+glm::vec3(size.x/2,size.y/2,0)) 
			* glm::rotate(glm::mat4(1.0f), rot, glm::vec3(0, 0, 1)) 
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		
		qdata.bufferPointer->position = transform * qdata.quadVertices[0];
		qdata.bufferPointer->color = color;
		qdata.bufferPointer->texCoord = { 0,0 };
		qdata.bufferPointer->texIndex = 0;
		qdata.bufferPointer->tileFactor = 1;
		qdata.bufferPointer++;

		qdata.bufferPointer->position = transform * qdata.quadVertices[1];
		qdata.bufferPointer->color = color;
		qdata.bufferPointer->texCoord = { 0,1 };
		qdata.bufferPointer->texIndex = 0;
		qdata.bufferPointer->tileFactor = 1;
		qdata.bufferPointer++;

		qdata.bufferPointer->position = transform * qdata.quadVertices[2];
		qdata.bufferPointer->color = color;
		qdata.bufferPointer->texCoord = { 1,1 };
		qdata.bufferPointer->texIndex = 0;
		qdata.bufferPointer->tileFactor = 1;
		qdata.bufferPointer++;

		qdata.bufferPointer->position = transform * qdata.quadVertices[3];
		qdata.bufferPointer->color = color;
		qdata.bufferPointer->texCoord = { 1,0 };
		qdata.bufferPointer->texIndex = 0;
		qdata.bufferPointer->tileFactor = 1;
		qdata.bufferPointer++;
		qdata.indexCount+=6;

	}

	void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture> texture2D, const glm::vec4& color, float tileFactor) {
		drawQuad(glm::vec3(position, 1), size, texture2D, color, tileFactor);
	}

	void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture> texture2D, const glm::vec4& color, float tileFactor) {
		if (qdata.indexCount >= qdata.maxInd) {
			flushAndReset();
		}
		float ti = 0.0f;
		
		for (uint32_t ts = 1; ts < qdata.texSlotIndex; ts++) {
			if (*qdata.texSlots[ts].get() == *texture2D.get()) {
				ti = (float)ts;
				break;
			}
		}

		if (ti == 0.0f) {
			ti = (float)qdata.texSlotIndex;
			qdata.texSlots[qdata.texSlotIndex] = texture2D;
			qdata.texSlotIndex++;
		}
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position + pos+glm::vec3(size.x/2,size.y/2,0.0f)) * glm::rotate(glm::mat4(1.0f), rot, glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		qdata.bufferPointer->position = transform * qdata.quadVertices[0];
		qdata.bufferPointer->color = color;
		qdata.bufferPointer->texCoord = { 0,0 };
		qdata.bufferPointer->texIndex = ti;
		qdata.bufferPointer->tileFactor = tileFactor;
		qdata.bufferPointer++;

		qdata.bufferPointer->position = transform * qdata.quadVertices[1];
		qdata.bufferPointer->color = color;
		qdata.bufferPointer->texCoord = { 0,1 };
		qdata.bufferPointer->texIndex = ti;
		qdata.bufferPointer->tileFactor = tileFactor;
		qdata.bufferPointer++;

		qdata.bufferPointer->position = transform * qdata.quadVertices[2];
		qdata.bufferPointer->color = color;
		qdata.bufferPointer->texCoord = { 1,1 };
		qdata.bufferPointer->texIndex = ti;
		qdata.bufferPointer->tileFactor = tileFactor;
		qdata.bufferPointer++;

		qdata.bufferPointer->position = transform * qdata.quadVertices[3];
		qdata.bufferPointer->color = color;
		qdata.bufferPointer->texCoord = { 1,0 };
		qdata.bufferPointer->texIndex = ti;
		qdata.bufferPointer->tileFactor = tileFactor;
		qdata.bufferPointer++;
		qdata.indexCount += 6;

	}

	void Renderer2D::drawQuadCentered(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
		drawQuadCentered(glm::vec3(position, 0), size, color);
	}

	void Renderer2D::drawQuadCentered(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
		if (qdata.indexCount >= qdata.maxInd) {
			flushAndReset();
		}
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position + pos) * glm::rotate(glm::mat4(1.0f), rot, glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		qdata.bufferPointer->position = transform * qdata.quadVertices[0];
		qdata.bufferPointer->color = color;
		qdata.bufferPointer->texCoord = { 0,0 };
		qdata.bufferPointer->texIndex = 0;
		qdata.bufferPointer->tileFactor = 1;
		qdata.bufferPointer++;

		qdata.bufferPointer->position = transform * qdata.quadVertices[1];
		qdata.bufferPointer->color = color;
		qdata.bufferPointer->texCoord = { 0,1 };
		qdata.bufferPointer->texIndex = 0;
		qdata.bufferPointer->tileFactor = 1;
		qdata.bufferPointer++;

		qdata.bufferPointer->position = transform * qdata.quadVertices[2];
		qdata.bufferPointer->color = color;
		qdata.bufferPointer->texCoord = { 1,1 };
		qdata.bufferPointer->texIndex = 0;
		qdata.bufferPointer->tileFactor = 1;
		qdata.bufferPointer++;

		qdata.bufferPointer->position = transform * qdata.quadVertices[3];
		qdata.bufferPointer->color = color;
		qdata.bufferPointer->texCoord = { 1,0 };
		qdata.bufferPointer->texIndex = 0;
		qdata.bufferPointer->tileFactor = 1;
		qdata.bufferPointer++;
		qdata.indexCount += 6;
		
	}
	void Renderer2D::beginScene(Ref<Camera> cam) { 
		
		Renderer::beginScene(cam); 
		qdata.shader->bind();
		qdata.vertexArray->bind();
		qdata.shader->setUniformMat4("u_proj", cam->getViewProjection());
		qdata.indexCount = 0;
		qdata.bufferPointer = qdata.bufferBase;
		qdata.texSlotIndex = 1;
	}

	void Renderer2D::endScene() { 
		
		Renderer::endScene();
		if (qdata.indexCount == 0) {
			return;
		}
		uint32_t dataSize = (uint8_t*)qdata.bufferPointer - (uint8_t*)qdata.bufferBase;
		qdata.vertexBuffer->setData(qdata.bufferBase, dataSize);
		
		flush();
	}

	void Renderer2D::flush() {
		for (uint32_t ind = 0; ind < qdata.texSlotIndex; ind++) {
			qdata.texSlots[ind]->bind(ind);
		}
		RendererContent::drawIndex(qdata.vertexArray, qdata.indexCount);
		qdata.vertexArray->unbind();
		qdata.shader->unbind();
		for (uint32_t ind = 0; ind < qdata.texSlotIndex; ind++) {
			qdata.texSlots[ind]->unbind(ind);
		}
	}

	void Renderer2D::drawQuadCentered(const glm::vec2& position, const glm::vec2& size, const Ref<Texture> texture2D, const glm::vec4& color, float tileFactor) {
		drawQuadCentered(glm::vec3(position, 1), size, texture2D, color, tileFactor);
	}
	
	void Renderer2D::flushAndReset() {
		endScene();
		qdata.indexCount = 0;
		qdata.bufferPointer = qdata.bufferBase;
		qdata.texSlotIndex = 1;
		qdata.shader->bind();
		qdata.vertexArray->bind();
	}
	void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<SubTexture2D> texture2D, const glm::vec4& color, float tileFactor) {
		glm::vec2 texCoords[4] = {
			texture2D->getTexCoord(0),
			texture2D->getTexCoord(1),
			texture2D->getTexCoord(2),
			texture2D->getTexCoord(3)
		};
		if (qdata.indexCount >= qdata.maxInd) {
			flushAndReset();
		}
		float ti = 0.0f;

		for (uint32_t ts = 1; ts < qdata.texSlotIndex; ts++) {
			if (*qdata.texSlots[ts].get() == *texture2D->getTexture().get()) {
				ti = (float)ts;
				break;
			}
		}

		if (ti == 0.0f) {
			ti = (float)qdata.texSlotIndex;
			qdata.texSlots[ti] = texture2D->getTexture();
			qdata.texSlotIndex++;
		}
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position + pos + glm::vec3(size.x/2, size.y/2, 0)) * glm::rotate(glm::mat4(1.0f), rot, glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		qdata.bufferPointer->position = transform * qdata.quadVertices[0];
		qdata.bufferPointer->color = color;
		qdata.bufferPointer->texCoord = texCoords[0];
		qdata.bufferPointer->texIndex = ti;
		qdata.bufferPointer->tileFactor = tileFactor;
		qdata.bufferPointer++;

		qdata.bufferPointer->position = transform * qdata.quadVertices[1];
		qdata.bufferPointer->color = color;
		qdata.bufferPointer->texCoord = texCoords[1];
		qdata.bufferPointer->texIndex = ti;
		qdata.bufferPointer->tileFactor = tileFactor;
		qdata.bufferPointer++;

		qdata.bufferPointer->position = transform * qdata.quadVertices[2];
		qdata.bufferPointer->color = color;
		qdata.bufferPointer->texCoord = texCoords[2];
		qdata.bufferPointer->texIndex = ti;
		qdata.bufferPointer->tileFactor = tileFactor;
		qdata.bufferPointer++;

		qdata.bufferPointer->position = transform * qdata.quadVertices[3];
		qdata.bufferPointer->color = color;
		qdata.bufferPointer->texCoord = texCoords[3];
		qdata.bufferPointer->texIndex = ti;
		qdata.bufferPointer->tileFactor = tileFactor;
		qdata.bufferPointer++;
		qdata.indexCount += 6;
	}
	void Renderer2D::drawQuadCentered(const glm::vec3& position, const glm::vec2& size, const Ref<SubTexture2D> texture2D, const glm::vec4& color, float tileFactor) {

		glm::vec2 texCoords[4] = {
			texture2D->getTexCoord(0),
			texture2D->getTexCoord(1),
			texture2D->getTexCoord(2),
			texture2D->getTexCoord(3)
		};
		if (qdata.indexCount >= qdata.maxInd) {
			flushAndReset();
		}
		float ti = 0.0f;

		for (uint32_t ts = 1; ts < qdata.texSlotIndex; ts++) {
			if (*qdata.texSlots[ts].get() == *texture2D->getTexture().get()) {
				ti = (float)ts;
				break;
			}
		}

		if (ti == 0.0f) {
			ti = (float)qdata.texSlotIndex;
			qdata.texSlots[ti] = texture2D->getTexture();
			qdata.texSlotIndex++;
		}
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position + pos) * glm::rotate(glm::mat4(1.0f), rot, glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		qdata.bufferPointer->position = transform * qdata.quadVertices[0];
		qdata.bufferPointer->color = color;
		qdata.bufferPointer->texCoord = texCoords[0];
		qdata.bufferPointer->texIndex = ti;
		qdata.bufferPointer->tileFactor = tileFactor;
		qdata.bufferPointer++;

		qdata.bufferPointer->position = transform * qdata.quadVertices[1];
		qdata.bufferPointer->color = color;
		qdata.bufferPointer->texCoord = texCoords[1];
		qdata.bufferPointer->texIndex = ti;
		qdata.bufferPointer->tileFactor = tileFactor;
		qdata.bufferPointer++;

		qdata.bufferPointer->position = transform * qdata.quadVertices[2];
		qdata.bufferPointer->color = color;
		qdata.bufferPointer->texCoord = texCoords[2];
		qdata.bufferPointer->texIndex = ti;
		qdata.bufferPointer->tileFactor = tileFactor;
		qdata.bufferPointer++;

		qdata.bufferPointer->position = transform * qdata.quadVertices[3];
		qdata.bufferPointer->color = color;
		qdata.bufferPointer->texCoord = texCoords[3];
		qdata.bufferPointer->texIndex = ti;
		qdata.bufferPointer->tileFactor = tileFactor;
		qdata.bufferPointer++;
		qdata.indexCount += 6;

	}



	void Renderer2D::drawQuadCentered(const glm::vec3& position, const glm::vec2& size, const Ref<Texture> texture2D, const glm::vec4& color, float tileFactor) {

		glm::vec2 texCoords[4] = {
			{0,0},
			{0,1},
			{1,1},
			{1,0}
		};
		if (qdata.indexCount >= qdata.maxInd) {
			flushAndReset();
		}
		float ti = 0.0f;

		for (uint32_t ts = 1; ts < qdata.texSlotIndex; ts++) {
			if (*qdata.texSlots[ts].get() == *texture2D.get()) {
				ti = (float)ts;
				break;
			}
		}

		if (ti == 0.0f) {
			ti = (float)qdata.texSlotIndex;
			qdata.texSlots[ti] = texture2D;
			qdata.texSlotIndex++;
		}
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position + pos) * glm::rotate(glm::mat4(1.0f), rot, glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		qdata.bufferPointer->position = transform * qdata.quadVertices[0];
		qdata.bufferPointer->color = color;
		qdata.bufferPointer->texCoord = texCoords[0];
		qdata.bufferPointer->texIndex = ti;
		qdata.bufferPointer->tileFactor = tileFactor;
		qdata.bufferPointer++;

		qdata.bufferPointer->position = transform * qdata.quadVertices[1];
		qdata.bufferPointer->color = color;
		qdata.bufferPointer->texCoord = texCoords[1];
		qdata.bufferPointer->texIndex = ti;
		qdata.bufferPointer->tileFactor = tileFactor;
		qdata.bufferPointer++;

		qdata.bufferPointer->position = transform * qdata.quadVertices[2];
		qdata.bufferPointer->color = color;
		qdata.bufferPointer->texCoord = texCoords[2];
		qdata.bufferPointer->texIndex = ti;
		qdata.bufferPointer->tileFactor = tileFactor;
		qdata.bufferPointer++;

		qdata.bufferPointer->position = transform * qdata.quadVertices[3];
		qdata.bufferPointer->color = color;
		qdata.bufferPointer->texCoord = texCoords[3];
		qdata.bufferPointer->texIndex = ti;
		qdata.bufferPointer->tileFactor = tileFactor;
		qdata.bufferPointer++;
		qdata.indexCount += 6;

	}



}
