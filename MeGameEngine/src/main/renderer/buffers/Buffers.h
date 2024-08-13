#pragma once
#include <hzpch.h>
namespace ME{
	enum class ShaderType : uint32_t{
		None = 0, Vec3, Vec2, Vec4, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};
	
	static uint32_t shaderTypeSize(ShaderType type) {
		switch (type) {
		case ShaderType::Float:
			return 4;
		case ShaderType::Vec2:
			return 4 * 2;
		case ShaderType::Vec3:
			return 4 * 3;
		case ShaderType::Vec4:
			return 4 * 4;
		case ShaderType::Float2:
			return 4 * 2;
		case ShaderType::Float3:
			return 4 * 3;
		case ShaderType::Float4:
			return 4 * 4;
		case ShaderType::Mat3:
			return 4 * 3 * 3;
		case ShaderType::Mat4:
			return 4 * 4 * 4;
		case ShaderType::Int:
			return 4;
		case ShaderType::Int2:
			return 4 * 2;
		case ShaderType::Int3:
			return 4 * 3;
		case ShaderType::Int4:
			return 4 * 4;
		case ShaderType::Bool:
			return 1;
		}
		ME_CORE_ASSORT(false, "Unknown Shader Type cannot get size!");
		return 0;
	}

	struct BufferElements {
		std::string name;
		uint32_t offset;
		uint32_t size;
		bool normalized = false;
		ShaderType data;
		uint32_t getComponentCount() {
			switch (data) {
			case ShaderType::Float:
				return 1;
			case ShaderType::Vec2:
				return 2;
			case ShaderType::Vec3:
				return 3;
			case ShaderType::Vec4:
				return 4;
			case ShaderType::Float2:
				return 2;
			case ShaderType::Float3:
				return 3;
			case ShaderType::Float4:
				return 4;
			case ShaderType::Mat3:
				return 3 * 3;
			case ShaderType::Mat4:
				return 4 * 4;
			case ShaderType::Int:
				return 1;
			case ShaderType::Int2:
				return 2;
			case ShaderType::Int3:
				return 3;
			case ShaderType::Int4:
				return 4;
			case ShaderType::Bool:
				return 1;
			}
			ME_CORE_ASSORT(false, "Unknown Shader Type cannot get size!");
			return 0;
		}
		BufferElements(ShaderType type, const std::string& name) : name(name), data(type), size(0), offset(0){
			size = shaderTypeSize(type);
		}
	};

	class BufferLayout {

	public:
		
		BufferLayout(const std::initializer_list<BufferElements> allElem = {}, bool normalized = false) : m_elements(allElem), m_normalized(normalized) {
			calculateStrideAndOffsets();
		}
		inline const std::vector<BufferElements> getElements() { return m_elements; }
		std::vector<BufferElements>::iterator begin() { return m_elements.begin(); }
		std::vector<BufferElements>::iterator end() { return m_elements.end(); }
		std::vector<BufferElements>::const_iterator begin() const { return m_elements.begin(); }
		std::vector<BufferElements>::const_iterator end()  const { return m_elements.end(); }
		uint32_t getStrife() { return m_stride; }
		bool getNormalized() { return m_normalized; }
		void setNormalized(bool normal) { m_normalized = normal; }
	private:
		void calculateStrideAndOffsets() {
			uint32_t offset = 0;
			m_stride = 0;
			
			for (BufferElements& h : m_elements) {
				h.offset = offset;
				offset += h.size;
				m_stride += h.size;
			}
			
		}
	private:
		std::vector<BufferElements> m_elements;
		uint32_t m_stride;
		bool m_normalized;
	};

	class VertexBuffer {

	public:
		virtual ~VertexBuffer() {};
		
		virtual const void setLayout(BufferLayout& layout) = 0;
		virtual const BufferLayout& getLayout() const = 0;
		virtual void bind() = 0;
		virtual void setData(const void* data, uint32_t size) = 0;
		virtual void unbind() = 0;
		static Ref<VertexBuffer> create(uint32_t size);
		static Ref<VertexBuffer> create(float* vertices, uint32_t size);


	};

	class IndexBuffer {
	public:
		virtual ~IndexBuffer() {};
		virtual uint32_t getCount() const = 0;
		virtual void bind() = 0;
		virtual void unbind() = 0;
		static Ref<IndexBuffer> create(uint32_t* vertices, uint32_t size);


	};

}
