#pragma once
#include <functional>
#include <string>
#include <any>
#include <stdexcept>

using Byte = char;
using VarValPair = std::pair<std::string, std::string>;
template <typename T> using ptr = std::shared_ptr<T>;

using EventFunction = std::function<void()>;
using CallbackFunction = std::function<void()>;
using WorkFunction = std::function<void(std::any)>;
using WorkFunctionNoArg = std::function<void()>;
using WorkFunctionWithRetVal = std::function<std::any()>;
template <typename T> using Getter = std::function<T()>;
template <typename T> using Setter = std::function<void(const T&)>;
//template <typename T> using SetterR = std::function<void(T&&)>;
