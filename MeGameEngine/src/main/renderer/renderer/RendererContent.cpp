#include <hzpch.h>
#include "RendererContent.h"
#include "main/platform/opengl/renderer/OpenGLRendererAPI.h"

namespace ME {

	RendererAPI* RendererContent::s_api = new OpenGLRendererAPI();

}