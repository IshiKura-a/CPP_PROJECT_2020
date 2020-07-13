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

	
	Model()
	{
		latexString = std::make_shared<std::string>();
		imageData = std::make_shared<std::vector<Byte>>();
		variableValuePairs = std::make_shared<std::vector<VariableValuePair>>();
		result = std::make_shared<std::string>();
	}

	
	// function
	// 如果修改了model中的数据, 需要调用对应的notify函数或使用setter

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
	// 禁止直接使用getter返回的指针修改数据（这样捕捉不到data changed事件）
	// set without notify用于view model在model层应用view的修改
	// 是否需要更精细的数据修改功能, 例如variableValuePairs.push_back

	std::shared_ptr<const std::string> getLatexString() const
	{
		return latexString;
	}
	void setLatexStringWithoutNotify(const std::string& str)
	{
		latexString = std::make_shared<std::string>(str);
	}
	std::shared_ptr<const std::vector<Byte>> getImageData() const
	{
		return imageData;
	}
	std::shared_ptr<const std::vector<VariableValuePair>> getVariableValuePairs() const
	{
		return variableValuePairs;
	}
	void setVariableValuePairsWithoutNotify(const std::vector<VariableValuePair>& pair)
	{
		variableValuePairs = std::make_shared<std::vector<VariableValuePair>>(pair);
	}
	std::shared_ptr<const std::string> getResult() const
	{
		return result;
	}
	
private:

	// view model用到setter时, 应当是将view的改变应用于model
	// 因此view model使用的setter不会产生notification
	// 这些私有的方法会产生notification, 用于model自己对数据的修改
	
	void setLatexString(const std::string& str)
	{
		latexString = std::make_shared<std::string>(str);
		latexStringChangedNotify();
	}
	void setImageData(const std::vector<Byte>& data)
	{
		imageData = std::make_shared<std::vector<Byte>>(data);
		imageDataChangedNotify();
	}
	void setVariableValuePairs(const std::vector<VariableValuePair>& pair)
	{
		variableValuePairs = std::make_shared<std::vector<VariableValuePair>>(pair);
		variableValuePairsChangedNotify();
	}
	void setResult(const std::string res)
	{
		result = std::make_shared<std::string>(res);
		resultChangedNotify();
	}
public:

	// 主动同步MVVM数据, 用于初始化
	void notifyAll() const
	{
		latexStringChangedNotify();
		imageDataChangedNotify();
		resultChangedNotify();
		variableValuePairsChangedNotify();
	}
	
	// event setter
	
	void setLatexStringChangedNotifier(EventFunction notifier)
	{
		latexStringChangedNotifier = notifier;
	}
	void setImageDataChangedNotifier(EventFunction notifier)
	{
		imageDataChangedNotifier = notifier;
	}
	// 初始化时用到
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

