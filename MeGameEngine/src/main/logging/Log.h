#pragma once
#include "hzpch.h"
#include "spdlog/spdlog.h"
#include <spdlog/sinks/stdout_color_sinks.h>
namespace ME {

	class ME_API Log {

	public:
		static void init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return m_coreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return m_clientLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetLogger(const char* name);
	private:
		static std::shared_ptr<spdlog::logger> m_coreLogger;
		static std::shared_ptr<spdlog::logger> m_clientLogger;
		static std::vector<std::shared_ptr<spdlog::logger>> m_Loggers;
		static std::vector<const char*> m_Loggernames;
	};

}

