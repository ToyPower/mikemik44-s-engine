#include "hzpch.h"
#include "EventCaller.h"
namespace ME {
	std::vector<std::vector<std::function<bool(Events&)>>> EventCaller::eventMethods;
	std::vector<const char*> EventCaller::eventMethodName;
}