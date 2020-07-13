#pragma once
#include <functional>
#include <string>
#include <any>
#include <variant>

using Value = std::variant<int32_t,double_t>;
using Byte = char;
using VarValPair = std::pair<std::string, Value>;
template <typename T> using ptr = std::shared_ptr<T>;

using EventFunction = std::function<void()>;
using CallbackFunction = std::function<void()>;
using WorkFunction = std::function<void(std::any)>;
using WorkFunctionNoArg = std::function<void()>;
template <typename T> using Getter = std::function<T()>;
template <typename T> using Setter = std::function<void(const T&)>;