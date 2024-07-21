#pragma once
#include "hzpch.h"
#include "../specialincludes.h"
namespace ME {
	class Events {
	public:
		Events(const char* name) {
			this->m_name = name;
		}
		~Events() {

		}
		std::vector<const char*> getParams() {
			return std::vector<const char*>(this->paramname);
		}
		std::any& getParam(const char* name) {
			
			for (int i = 0; i < paramname.size(); i++) {
				//ME_CORE_INFO("{0}", paramname[i] == name);
				if (strcmp(paramname[i], name)==0) {
					return params[i];
				}
			}
			return std::any(nullptr);
		}
		template <class T>
		void putParam(const char* param, T t) {
			params.push_back(std::any(2));
			//ME_CORE_INFO("type: {0}", params[params.size()-1].type());
			paramname.push_back(param);
		}
		const char* name() { return m_name; }
	private:
		const char* m_name;
		std::vector<std::any> params = {};
		std::vector<const char*> paramname = {};

	};
}