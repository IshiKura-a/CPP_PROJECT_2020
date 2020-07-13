#pragma once
#include <functional>
#include <memory>
#include <string>
#include <vector>


#include <iostream>

class ViewModel;

class Model
{
private:
	using Byte = unsigned char;
	using VariableValuePair = std::pair<std::string, double_t>;
	template <typename T>
	using ptr = std::shared_ptr<T>;
	using EventFunction = std::function<void()>;

	// 用于解析和渲染图片的latex string
	ptr<std::string> latexString;
	// 渲染后图片的二进制数据
	ptr<std::vector<Byte>> imageData;
	// 公式中的变量-值组
	ptr<std::vector<VariableValuePair>> variableValuePairs;
	// 公式计算结果
	ptr<std::string> result;

	EventFunction latexStringChangedNotifier;
	EventFunction imageDataChangedNotifier;
	EventFunction variableValuePairsChangedNotifier;
	EventFunction resultChangedNotifier;

	
public:
	Model()
	{
		latexString = std::make_shared<std::string>();
		imageData = std::make_shared<std::vector<Byte>>();
		variableValuePairs = std::make_shared<std::vector<VariableValuePair>>();
		result = std::make_shared<std::string>();
	}
	// function

	void getFormulaResult();

	// data getter and setter

	//一些reminder:
	// 如果使用返回的指针修改了model的数据，是否捕捉不到data changed事件了？


	const auto& getLatexString() const
	{
		return latexString;
	}
	void setLatexString(const std::string& str)
	{
		latexString = std::make_shared<std::string>(str);
	}
	const auto& getImageData() const
	{
		return imageData;
	}
	void setImageData(const std::vector<Byte>& data)
	{
		imageData = std::make_shared<std::vector<Byte>>(data);
	}
	const auto& getVariableValuePairs() const
	{
		return variableValuePairs;
	}
	void setVariableValueString(const std::vector<VariableValuePair>& pair)
	{
		variableValuePairs = std::make_shared<std::vector<VariableValuePair>>(pair);
	}
	const auto& getResult() const
	{
		return result;
	}
	// result不能被view model设置
private:
	void setResult(const std::string res)
	{
		result = std::make_shared<std::string>(res);
	}
public:


	
	// event getter and setter

	void setLatexStringChangedNotifier(EventFunction notifier)
	{
		latexStringChangedNotifier = notifier;
	}
	auto getLatexStringChangedNotifier() const
	{
		return latexStringChangedNotifier;
	}
	void setImageDataChangedNotifier(EventFunction notifier)
	{
		imageDataChangedNotifier = notifier;
	}
	auto getImageDataChangedNotifier() const
	{
		return imageDataChangedNotifier;
	}
	void setVariableValuePairsChangedNotifier(EventFunction notifier)
	{
		variableValuePairsChangedNotifier = notifier;
	}
	auto getVariableValuePairsChangedNotifier() const
	{
		return variableValuePairsChangedNotifier;
	}
	void setResultChangedNotifier(EventFunction notifier)
	{
		resultChangedNotifier = notifier;
	}
	auto getResultChangedNotifier() const
	{
		return resultChangedNotifier;
	}
	
	// event trigger

	void latexStringChangedNotify() const
	{
		std::cout << "Model says latex string has changed!\n";
		latexStringChangedNotifier();
	}
	void imageDataChangedNotify() const
	{
		std::cout << "Model says image data has changed!\n";
		imageDataChangedNotifier();
	}
	void variableValuePairsChangedNotify() const
	{
		std::cout << "Model says variable-value pairs have changed!\n";
		variableValuePairsChangedNotifier();
	}
	void resultChangedNotify() const
	{
		std::cout << "Model says result has changed!\n";
		resultChangedNotifier();
	}
};

