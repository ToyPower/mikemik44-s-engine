#pragma once
namespace ME {

	enum class RENDERAPI {

		none = 0, opengl = 1

	};

	class Renderer {

	public:
		static RENDERAPI getAPI() { return m_api; }
	private:
		static RENDERAPI m_api;
	};

}