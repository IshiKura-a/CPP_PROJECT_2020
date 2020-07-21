#pragma once
#include <functional>
#include <string>
#include <any>
#include <variant>
#include <stdexcept>

using Value = std::variant<int32_t, double_t>;
using Byte = char;
using VarValPair = std::pair<std::string, Value>;
template <typename T> using ptr = std::shared_ptr<T>;

using EventFunction = std::function<void()>;
using CallbackFunction = std::function<void()>;
using WorkFunction = std::function<void(std::any)>;
using WorkFunctionNoArg = std::function<void()>;
using WorkFunctionWithRetVal = std::function<std::any()>;
template <typename T> using Getter = std::function<T()>;
template <typename T> using Setter = std::function<void(const T&)>;
//template <typename T> using SetterR = std::function<void(T&&)>;

inline int32_t valueToInt(Value v) noexcept(false)
{
	if (v.index() == 0)
		return std::get<0>(v);
	else
		throw std::logic_error("Value is not int");
}

inline double_t valueToDouble(Value v) noexcept(false)
{
	if(v.index() == 1)
		return std::get<1>(v);
	else
		throw std::logic_error("Value is not double");
}