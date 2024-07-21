#pragma once
#include "hzpch.h"
#include "../specialincludes.h"
namespace ME {

	class ME_API EventCaller {

	private:
		static std::vector<std::vector<std::function<bool(Events&)>>> eventMethods;
		static std::vector<const char*> eventMethodName;
	public:

		static void addEventListener(std::function<bool(Events&)> func, const char* eventName) {
			for (int i = 0; i < eventMethodName.size(); i++) {
				if (strcmp(eventMethodName[i], eventName) == 0) {

					eventMethods[i].push_back(func);
					return;
				}
			}
			std::vector<std::function<bool(Events&)>> b;
			b.push_back(func);
			eventMethods.push_back(b);
			eventMethodName.push_back(eventName);

		}

		static bool inform(std::string a, std::string b) {
			int pos = a.find("*");
			if (b.length() >= pos) {
				if (strcmp(a.substr(0, pos).c_str(), b.substr(0, pos).c_str()) == 0) {
					return true;
				}
			}
			else {
				return false;
			}
		}
		static bool callEvent(Events& e) {
			for (int i = eventMethodName.size()-1; i >= 0; i--) {
				const char* name = eventMethodName[i];
				if (strcmp(name,e.name()) == 0 || strcmp(name,"*") == 0 || std::string(name).find("*") != std::string::npos && inform(std::string(name), std::string(e.name()))) {
					auto values = eventMethods[i];
				
					for (int j = 0; j < values.size(); j++) {
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

