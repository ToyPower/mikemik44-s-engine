#pragma once
#include "string"
#include "vector"
namespace ME {

	class StrUtil {

	public:
		static std::vector<std::string> split(const std::string& name, const std::string& chk) {
			std::vector<std::string> allStr;
			bool pass = false;
			std::size_t it = 0;
			std::string ref = name;
			
			while (pass == false) {
				std::size_t check = ref.find(chk);
				if (check != std::string::npos) {
					std::string res = (ref.substr(0, check));
					if (res.length() != std::string::npos) {
						allStr.push_back(res);
						if (res.length()+1 >= ref.length()) {
							ref = "";
							break;
						}
						ref = ref.substr(res.length()+1);
					}
					else {
						allStr.push_back("");
						ref = ref.substr(1);
					}
					
					if (ref.length() == 0) {
						break;
					}
				}
				else {
					break;
				}
			}
			if (ref.length() == 0) {
				allStr.push_back("");
			}
			else {
				allStr.push_back(ref);
			}
			return allStr;

		}

		static bool hasWild(const std::string& name, const std::string& chk) {
			auto col = split(name, "*");
			bool match = true;
			bool hadWild = false;
			std::string hp = chk;
			for (uint32_t i = 0; i < col.size(); i++) {
				auto c = col[i];
				if (c == "" || c.length() == 0) {
					hadWild = true;
					continue;
				}
				else {
					if (hadWild) {
						if (col.size() - 1 == i) {
							if (hp != c) {
								match = false;
								break;
							}
						}
						else {
							auto ind = hp.find(c);
							if (ind == std::string::npos) {
								ME_CORE_INFO("IFAIL: {0}-{1}", hp, c);
								match = false;
								break;
							}
							hp = hp.substr(ind + c.length());
						}
						
					}
					else {
						if (hp.length() > c.length() && hp.substr(0,c.length()) == c) {
							hp = hp.substr(c.length());
							
							hadWild = true;
							continue;
						}
						else {
							ME_CORE_INFO("FAIL: {0}-{1}", hp, c);
							match = false;
							break;
						}
					}
				}
			}
			return match;
		}

	};

}
