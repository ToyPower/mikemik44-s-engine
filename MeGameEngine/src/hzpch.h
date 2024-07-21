#pragma once

#include <iostream>
#include <memory>
#include <functional>
#include <utility>
#include <algorithm>
#include <sstream>

#include <any>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#ifdef ME_PLATFORM_WINDOWS
	#include "Windows.h"
	#include <GLFW/glfw3.h>
#endif