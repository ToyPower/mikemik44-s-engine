#pragma once
#include "main/entry/Application.h"
#include "main/layer/Layer.h"
#include "main/corefiles/specialincludes.h"
#include "main/input/Input.h"
#include "main/dataentry/KeyCodes.h"
#include "main/dataentry/MouseButtonCodes.h"
#include "main/renderer/buffers/Buffers.h"
#include "main/renderer/renderer/main/Renderer.h"
#include "main/renderer/renderer/main/RendererContent.h"
#include "main/renderer/buffers/VertexArray.h"
#include "main/renderer/shaders/Shader.h"
#include "main/renderer/data/camera/Camera.h"
#include "main/dataentry/TimeStep.h"
#include "main/renderer/data/meshdata/Transform.h"
#include "main/renderer/data/meshdata/Material.h"
#include "main/renderer/data/meshdata/Mesh.h"
#include "main/renderer/data/Vertex.h"
#include "main/renderer/data/camera/CameraController.h"
#include "main/renderer/renderer/Texture.h"
#include "main/renderer/2D/Renderer2D.h"

#include "main/events/EventCaller.h"


#define mptr glm::value_ptr