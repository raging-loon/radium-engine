#ifndef CORE_DEBUG_LOG_FORMAT_H_
#define CORE_DEBUG_LOG_FORMAT_H_
#include <spdlog/spdlog.h>
#include "math/mat4x4.h"
#include "core/Variant.h"

/* This file provides formatters for spdlog so we can log custom objects*/

template<>
struct fmt::formatter<radium::math::Mat4x4> : fmt::formatter<std::string>
{
	auto format(radium::math::Mat4x4 m, format_context& ctx) const -> decltype(ctx.out())
	{
		return fmt::format_to(ctx.out(),
			"[ {}, {}, {}, {} ]\n"
			"[ {}, {}, {}, {} ]\n"
			"[ {}, {}, {}, {} ]\n"
			"[ {}, {}, {}, {} ]\n",

			m(0, 0), m(0, 1), m(0, 2), m(0, 3),
			m(1, 0), m(1, 1), m(1, 2), m(1, 3),
			m(2, 0), m(2, 1), m(2, 2), m(2, 3),
			m(3, 0), m(3, 1), m(3, 2), m(3, 3)


		);
	}

};

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