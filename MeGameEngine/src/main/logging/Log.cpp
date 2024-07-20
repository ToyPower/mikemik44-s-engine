#include "Log.h"

namespace ME {
	std::shared_ptr<spdlog::logger> Log::m_coreLogger;
	std::shared_ptr<spdlog::logger> Log::m_clientLogger;
	std::vector<std::shared_ptr<spdlog::logger>> Log::m_Loggers;
	std::vector<const char*> Log::m_Loggernames;
	void Log::init() {
		
		spdlog::set_pattern("%^%n-%T: %v%$");
		m_coreLogger = spdlog::stdout_color_mt("Engine");
		m_coreLogger->set_level(spdlog::level::trace);

		m_clientLogger = spdlog::stdout_color_mt("Game");
		m_clientLogger->set_level(spdlog::level::trace);
	}
	std::shared_ptr<spdlog::logger>& Log::GetLogger(const char* name) {
		for (uint32_t i = 0; i < m_Loggernames.size(); i++) {
			if (name == m_Loggernames[i]) {
				return m_Loggers[i];
			}
		}
		spdlog::set_pattern("%^%n-%T: %v%$");
		std::shared_ptr<spdlog::logger> log = spdlog::stdout_color_mt(name);
		log->set_level(spdlog::level::trace);

		m_Loggers.push_back(log);
		m_Loggernames.push_back(name);
		return log;
	}
}