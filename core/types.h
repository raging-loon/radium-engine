#ifndef CORE_TYPES_H_
#define CORE_TYPES_H_

#include <cstdint>
#include <utility>
namespace radium
{
	
using byte = unsigned char;

using U8  = uint8_t;
using U16 = uint16_t;
using U32 = uint32_t;
using U64 = uint64_t;

using I8  = int8_t;
using I16 = int16_t;
using I32 = int32_t;
using I64 = int64_t;


/* 
 *		function pointer wrapper
 *	
 *	usage:
 *		radium::function<ReturnType(ArgumentTypes...)> fnPtr;
 * 
 *		radium::function<ReturnType()> fnPtrWithNoArguments;
 *
*/
template<typename R, typename... Args>
class function;

template <typename Ret, typename... Args>
class function <Ret(Args...)>
{
public:
	using FnPtr = Ret(*)(Args...);


	constexpr explicit function(FnPtr f)
		: m_fptr(f)
	{
	}

	constexpr function()
		: m_fptr(nullptr)
	{
	}

	constexpr function& operator=(FnPtr& f)
	{
		m_fptr = f;
		return *this;
	}
	constexpr function& operator=(FnPtr&& f)
	{
		m_fptr = std::move(f);
		return *this;

	}
	constexpr Ret operator()(Args... a)
	{
		return (*m_fptr)(a...);
	}
private:

	FnPtr m_fptr;
};



}


#endif // CORE_TYPES_H_