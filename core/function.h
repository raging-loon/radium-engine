#ifndef CORE_FUNCTION_H_
#define CORE_FUNCTION_H_

#include <utility>
namespace radium
{

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

	constexpr function(function& f) : m_fptr (f.m_fptr) { }

	constexpr function(function&& f) : m_fptr(std::move(f.m_fptr)) { }


	template <typename T>
	constexpr function(T&& f) : m_fptr(std::forward<T>(f)) { }

	constexpr function() : m_fptr(nullptr) { }

	~function() = default;
	
	template <typename T>
	constexpr function& operator=(T&& f)
	{
		m_fptr = std::forward<T>(f).m_fptr;
		return *this;
	}


	constexpr void operator=(FnPtr& f) { m_fptr = f; }

	constexpr void operator=(FnPtr&& f) { m_fptr = std::move(f); }

	constexpr Ret operator()(Args... a)
	{
		return (*m_fptr)(a...);
	}

	
	constexpr bool isValid() const { return m_fptr != nullptr; }
private:

	FnPtr m_fptr;
};


} // radium


#endif // CORE_FUNCTION_H_