#ifndef CORE_CONFIG_HASH_H_
#define CORE_CONFIG_HASH_H_

#include <cstdint>

namespace radium
{

namespace fnv1a
{
constexpr uint32_t prime = 0xe963a535;
constexpr uint32_t offsetBasis = 0x811c9dc5;

constexpr uint32_t generate(const char* str)
{
	uint32_t res = offsetBasis;
	while (*str)
	{
		res ^= static_cast<uint32_t>(*str++);
		res *= prime;
	}
	return res;
}

} // fnv1a

} // radium

#define CID(x) radium::fnv1a::generate(x)


#endif // CORE_CONFIG_HASH_H_