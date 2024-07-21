#pragma once
#include "hzpch.h"
#include "../specialincludes.h"
namespace ME {
	class ME_API Events {
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
			params.push_back(std::any(t));
			//ME_CORE_INFO("type: {0}", params[params.size()-1].type());
			paramname.push_back(param);
		}
		const char* name() { return m_name; }
		const std::string ToString() const {
			std::string ans;
			ans += m_name;
			ans += ", Params {";
			std::stringstream ss;
			for (int i = 0; i < params.size(); i++) {
				auto ans = params[i];
				if (i != 0) {
					ss << ", ";
				}
				ss << paramname[i] << ": ";
				if (ans.type() == typeid(std::string)) {
					ss << std::any_cast<std::string>(ans);
				}
				else if (ans.type() == typeid(int)) {
					ss << std::any_cast<int>(ans);
				}
				else if (ans.type() == typeid(float)) {
					ss << std::any_cast<float>(ans);
				}
				else if (ans.type() == typeid(double)) {
					ss << std::any_cast<double>(ans);
				}
				else if (ans.type() == typeid(const char*)) {
					ss << std::any_cast<const char*>(ans);
				}
				else if (ans.type() == typeid(bool)) {
					ss << std::any_cast<bool>(ans);
				}
			}
			ans += ss.str();
			ans += "}";
			return ans;
		}
		bool handled = false;
	private:
		const char* m_name;
		std::vector<std::any> params = {};
		std::vector<const char*> paramname = {};

	};

	inline std::ostream& operator<<(std::ostream& os, const Events& e)
	{
		return os << e.ToString();
	}
}