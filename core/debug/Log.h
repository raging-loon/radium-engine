#ifndef CORE_DEBUG_LOG_H_
#define CORE_DEBUG_LOG_H_


#ifdef RAD_DEBUG
#include "core/Variant.h"
#include <spdlog/spdlog.h>

namespace radium
{
	
class Log
{
public:
	static void init();
	
	static const auto& getEngineLogger() { return m_engineLogger; }
	static const auto& getClientLogger() { return m_clientLogger; }

private:
	static std::shared_ptr<spdlog::logger> m_engineLogger;
	static std::shared_ptr<spdlog::logger> m_clientLogger;

};


} // radium

template<>
struct fmt::formatter<radium::Variant> : fmt::formatter<std::string>
{
	auto format(radium::Variant v, format_context& ctx) const -> decltype(ctx.out())
	{
		switch (v.getType())
		{
			case radium::Variant::INT:
				return fmt::format_to(ctx.out(), "{}", (int)v);
			case radium::Variant::BOOL:
				return fmt::format_to(ctx.out(), "{}", (bool)v);
			default:
				return fmt::format_to(ctx.out(), "{}", "unknown type");
		}
	}
};


#define RAD_ENGINE_INFO(...)		::radium::Log::getEngineLogger()->info(__VA_ARGS__)
#define RAD_ENGINE_TRACE(...)		::radium::Log::getEngineLogger()->trace(__VA_ARGS__)
#define RAD_ENGINE_ERROR(...)		::radium::Log::getEngineLogger()->error(__VA_ARGS__)
#define RAD_ENGINE_CRITICAL(...)	::radium::Log::getEngineLogger()->critical(__VA_ARGS__)
#define RAD_ENGINE_WARN(...)		::radium::Log::getEngineLogger()->warn(__VA_ARGS__)

#else
#define RAD_ENGINE_INFO(...)	
#define RAD_ENGINE_TRACE(...)	
#define RAD_ENGINE_ERROR(...)	
#define RAD_ENGINE_CRITICAL(...)
#define RAD_ENGINE_WARN(...)	

#endif // RAD_DEBUG



#endif // CORE_DEBUG_LOG_H_