#pragma once
#include "hzpch.h"
#include "../specialincludes.h"
namespace ME {

	class EventCaller {

	private:
		static std::vector<std::vector<std::function<bool(Events*)>>> eventMethods;
		static std::vector<const char*> eventMethodName;
	public:

		static void addEventListener(std::function<bool(Events*)> func, const char* eventName) {
			for (int i = 0; i < eventMethodName.size(); i++) {
				if (strcmp(eventMethodName[i], eventName) == 0) {

					eventMethods[i].push_back(func);
					return;
				}
			}
			std::vector<std::function<bool(Events*)>> b;
			b.push_back(func);
			eventMethods.push_back(b);
			eventMethodName.push_back(eventName);

		}

		static bool callEvent(Events* e) {
			for (int i = eventMethodName.size(); i >= 0; i--) {
				const char* name = eventMethodName[i];
				if (name == e->name()) {
					auto values = eventMethods[i];
					for (int j = values.size() - 1; j >= 0; j--) {
						bool res = values[j](e);
						if (!res) {
							return res;
						}
					}
					return true;
				}
			}
			return true;
		}
	};
}

