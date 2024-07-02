#ifndef CORE_SMART_PTR_H_
#define CORE_SMART_PTR_H_

#include <memory>

namespace radium
{

/**
 * Smart Ptr
 * 
 * This is a facade over std::xyz_ptr
 * 
 * This so if a custom SmartPtr implementation
 * is ever need, only this file needs to be changed.
 * None of the code relying on it will need to be changed
 * 
*/

template <typename T>
using Ref = std::shared_ptr<T>;

template<typename T, typename... Ts>
constexpr Ref<T> MakeRef(Ts&&... ts)
{
	return std::make_shared<T>(std::forward<Ts>(ts)...);
}


template <typename T>
using Scope = std::unique_ptr<T>;

template<typename T, typename... Ts>
constexpr Scope<T> MakeScope(Ts&&... ts)
{
	return std::make_unique<T>(std::forward<Ts>(ts)...);
}


} // radium

#endif // CORE_SMART_PTR_H_