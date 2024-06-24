#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
using radium::Log;

std::shared_ptr<spdlog::logger> Log::m_engineLogger;
std::shared_ptr<spdlog::logger> Log::m_clientLogger;

void Log::init()
{
    spdlog::sink_ptr sinks[2];
    

    sinks[0] = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    sinks[1] = std::make_shared<spdlog::sinks::basic_file_sink_mt>("radium.log", true);
    

    m_engineLogger = std::make_shared<spdlog::logger>("ENGINE", std::begin(sinks), std::end(sinks));
    spdlog::register_logger(m_engineLogger);
    m_engineLogger->set_level(spdlog::level::trace);
    m_engineLogger->flush_on(spdlog::level::trace);


    m_clientLogger = std::make_shared<spdlog::logger>("CLIENT", std::begin(sinks), std::end(sinks));
    spdlog::register_logger(m_clientLogger);

    m_clientLogger->set_level(spdlog::level::trace);
    m_clientLogger->flush_on(spdlog::level::trace);

}
