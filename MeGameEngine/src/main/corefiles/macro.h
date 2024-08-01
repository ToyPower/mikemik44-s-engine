#pragma once
#include <memory.h>
#ifdef UNNNN
#ifdef ME_PLATFORM_WINDOWS
	#ifdef ME_BUILD_DLL
		#define ME_API _declspec(dllexport)
	#else
		#define ME_API _declspec(dllimport)
	#endif	
#else
	#error We only support windws
#endif
#else
#define ME_API
#endif

#define ME_CORE_INFO(...) ::ME::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ME_CORE_WARN(...) ::ME::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ME_CORE_TRACE(...) ::ME::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ME_CORE_ERROR(...) ::ME::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ME_CORE_FATAL(...) ::ME::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#ifdef ME_Debug
	#define ME_ENABLE_ASSERT
#endif

#ifdef ME_ENABLE_ASSERT
#define ME_CORE_ASSORT(num, ...) {if (!num) {ME::Log::GetCoreLogger()->error(__VA_ARGS__);__debugbreak();}}
#else
#define ME_CORE_ASSORT(num, ...)
#endif
#define ME_CLIENT_INFO(...) ::ME::Log::GetClientLogger()->info(__VA_ARGS__)
#define ME_CLIENT_WARN(...) ::ME::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ME_CLIENT_TRACE(...) ::ME::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ME_CLIENT_ERROR(...) ::ME::Log::GetClientLogger()->error(__VA_ARGS__)
#define ME_CLIENT_FATAL(...) ::ME::Log::GetClientLogger()->fatal(__VA_ARGS__)

#define ME_LOG_INFO(name, ...) ::ME::Log::GetLogger(name)->info(__VA_ARGS__)
#define ME_LOG_WARN(name, ...) ::ME::Log::GetLogger(name)->warn(__VA_ARGS__)
#define ME_LOG_TRACE(name, ...) ::ME::Log::GetLogger(name)->trace(__VA_ARGS__)
#define ME_LOG_ERROR(name, ...) ::ME::Log::GetLogger(name)->error(__VA_ARGS__)
#define ME_LOG_FATAL(name, ...) ::ME::Log::GetLogger(name)->fatal(__VA_ARGS__)
namespace ME {
	template<typename T>
	using scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}