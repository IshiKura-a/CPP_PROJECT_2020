#pragma once
#include <functional>
#include <memory>
#include <string>
#include <vector>

class ViewModel;

class Model
{
private:
	using Byte = char;
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

	// notifier
	// 当model中的数据发生变化时，通知view model
	
	EventFunction latexStringChangedNotifier;
	EventFunction imageDataChangedNotifier;
	EventFunction variableValuePairsChangedNotifier;
	EventFunction resultChangedNotifier;

	
public:


	// function
	// 如果修改了model中的数据, 需要调用对应的notify函数

	// 打开图片文件, 并更新model的imageData
	// @param:
	// file_path: 需要读取的图片路径
	void openImage(std::string file_path);

	// 渲染model中的latexString, 并更新model的imageData
	void renderLatexFormula();

	// 获取帮助信息
	// @return:
	// 帮助信息的string
	std::string getHelpManual();

	// 使用model中的latexString, 将公式解析成表达式树
	void parseFormula();

	// 使用model中的variableValuePairs, 计算表达式树结果
	// 更新model的result
	void calculateFormula();

	// data getter and setter

	//一些reminder:
	// 如果使用返回的指针修改了model的数据，是否捕捉不到data changed事件了？
	// 是否需要更精细的数据修改功能, 例如variableValuePairs.push_back


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
	// image data不能被view model设置
private:
	void setImageData(const std::vector<Byte>& data)
	{
		imageData = std::make_shared<std::vector<Byte>>(data);
	}
public:
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


	
	// event setter

	void setLatexStringChangedNotifier(EventFunction notifier)
	{
		latexStringChangedNotifier = notifier;
	}
	void setImageDataChangedNotifier(EventFunction notifier)
	{
		imageDataChangedNotifier = notifier;
	}
	// model大概不会主动修改variableValuePairs?
	// 一般应该只会有view model修改?
	// 暂时留着这个notifier, 但感觉用不上
	void setVariableValuePairsChangedNotifier(EventFunction notifier)
	{
		variableValuePairsChangedNotifier = notifier;
	}
	void setResultChangedNotifier(EventFunction notifier)
	{
		resultChangedNotifier = notifier;
	}
	
	// event trigger

	void latexStringChangedNotify() const
	{
		latexStringChangedNotifier();
	}
	void imageDataChangedNotify() const
	{
		imageDataChangedNotifier();
	}
	void variableValuePairsChangedNotify() const
	{
		variableValuePairsChangedNotifier();
	}
	void resultChangedNotify() const
	{
		resultChangedNotifier();
	}
};

