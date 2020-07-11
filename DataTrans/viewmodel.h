#pragma once
#include "model.h"


#include <iostream>

class Model;

class ViewModel
{
private:
	using Byte = unsigned char;
	using VariableValuePair = std::pair<std::string, double_t>;
	template <typename T>
	using ptr = std::shared_ptr<T>;
	using EventFunction = std::function<void()>;
	using CallbackFunction = std::function<void()>;
	using WorkFunction = std::function<void>();


	std::shared_ptr<Model> model;

	// 下列数据类型需要改成对应的Qt类
	// ********************************
	// 用于解析和渲染图片的latex string
	ptr<std::string> latexString;
	// 渲染后图片的二进制数据
	ptr<std::vector<Byte>> imageData;
	// 公式中的变量-值组
	ptr<std::vector<VariableValuePair>> variableValuePairs;
	// 公式计算结果
	ptr<std::string> result;
	// ********************************

	EventFunction latexStringViewUpdateNotifier;

	// function

	// 动态绑定model的功能函数
	WorkFunction getFormulaResult;
	WorkFunction renderLatexString;
	
public:

	// function

	
	
	// binding

	// 绑定一个model实例，在model触发data changed事件时调用此view model的notified函数
	void bindModel(std::shared_ptr<Model> model)
	{
		this->model = model;
		this->model->setLatexStringChangedNotifier(
			[&]() {this->latexStringChangedNotified(); }
		);
	}

	// data getter and setter


	// event getter and setter

	void setLatexStringViewUpdateNotifier(EventFunction notifier)
	{
		latexStringViewUpdateNotifier = notifier;
	}
	auto getLatexStringViewUpdateNotifier() const
	{
		return latexStringViewUpdateNotifier;
	}
	

	// event callback
	// 这些回调函数可以采用与事件函数类似的方法来达成动态绑定
	// 不过我一时没想出这里动态绑定的意义，所以就写成静态的函数了
	
	void latexStringChangedNotified()
	{
		std::cout << "View model received model saying latex string has changed!\n";

		// 更新viewmodel中的data
		// 此处应当更新viewmodel中的latex string
		// somefunction()

		// 触发view的更新事件
		latexStringViewUpdateNotify();
	}

	// event trigger

	void latexStringViewUpdateNotify() const
	{
		std::cout << "View model says latex string has changed!\n";
		latexStringViewUpdateNotifier();
	}
};

