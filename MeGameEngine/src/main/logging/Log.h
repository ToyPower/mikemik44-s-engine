#pragma once
#include "hzpch.h"
#include "../macro.h"
#include "spdlog/spdlog.h"
#include <spdlog/sinks/stdout_color_sinks.h>
namespace ME {

	class ME_API Log {

	public:
		static void init();
		inline static Ref<spdlog::logger>& GetCoreLogger() { return m_coreLogger; }
		inline static Ref<spdlog::logger>& GetClientLogger() { return m_clientLogger; }
		inline static Ref<spdlog::logger>& GetLogger(const char* name);
	private:
		static Ref<spdlog::logger> m_coreLogger;
		static Ref<spdlog::logger> m_clientLogger;
		static std::vector<Ref<spdlog::logger>> m_Loggers;
		static std::vector<const char*> m_Loggernames;
	};

}

