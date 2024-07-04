#ifndef CORE_DEBUG_LOG_FORMAT_H_
#define CORE_DEBUG_LOG_FORMAT_H_
#include <spdlog/spdlog.h>
#include "core/Variant.h"

/* This file provides formatters for spdlog so we can log custom objects*/

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


#endif // CORE_DEBUG_LOG_FORMAT_H_