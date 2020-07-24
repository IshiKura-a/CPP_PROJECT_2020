#pragma once
#include "../common/def.h"
#include "../common/notifiable.h"

class Model : public Notifiable
{
private:

	// 用于解析和渲染图片的latex string
	ptr<std::string> latexString;
	// 渲染后图片的二进制数据
	ptr<std::vector<Byte>> imageData;
	// 公式中的变量-值组
	ptr<std::vector<VarValPair>> varValPairs;
	// 公式计算结果
	ptr<std::string> result;

	/******************** notifier ********************/
	// 当model中的数据发生变化时, 通知view model

	EventId latexStringChanged = EventUnregistered;
	EventId imageDataChanged = EventUnregistered;
	EventId varValuePairsChanged = EventUnregistered;
	EventId resultChanged = EventUnregistered;

	std::string applyVarValPairs();

public:

	Model()
	{
		latexString = std::make_shared<std::string>();
		imageData = std::make_shared<std::vector<Byte>>();
		varValPairs = std::make_shared<std::vector<VarValPair>>();
		result = std::make_shared<std::string>();
	}


	/******************** function ********************/
	// 如果修改了model中的数据, 需要调用对应的notify函数或使用setter

	// 识别路径为file_path的图片. 识别结果将覆盖latex string.
	// @param:
	// file_path: 需要读取的图片路径
	// isMathpixAPI: 为true时使用mathpix的API, 为false时使用baidu的API
	void getLatexStringFromImage(const std::string& file_path, bool isMathpixAPI = true);

	// 渲染model中的latexString, 并更新model的imageData
	// @param:
	// 设定渲染结果的格式, 支持png,gif,svg
	void renderLatexString(const std::string& image_format);

	// 获取帮助信息
	// @return:
	// 帮助信息的string
	std::string getHelpManual();

	// 使用model中的latexString, 将公式解析成表达式树
	//void parseLatexString();

	// 使用model中的variableValuePairs, 计算表达式树结果
	// 更新model的result
	void calculateLatexString();

	// 将latex string中多余的空格删除
	void prettifyLatexString();


	/******************** data getter and setter ********************/
	//一些reminder:
	// 禁止直接使用getter返回的指针修改数据(这样捕捉不到data changed事件)
	// set without notify用于view model在model层应用view的修改
	// 是否需要更精细的数据修改功能?例如varValPairs.push_back

	[[nodiscard]] ptr<const std::string> getLatexString() const
	{
		return latexString;
	}
	void setLatexStringWithoutNotify(const std::string& str)
	{
		latexString = std::make_shared<std::string>(str);
	}
	[[nodiscard]] ptr<const std::vector<Byte>> getImageData() const
	{
		return imageData;
	}
	[[nodiscard]] ptr<const std::vector<VarValPair>> getVarValPairs() const
	{
		return varValPairs;
	}
	void setVarValPairsWithoutNotify(const std::vector<VarValPair>& pair)
	{
		varValPairs = std::make_shared<std::vector<VarValPair>>(pair);
	}
	[[nodiscard]] ptr<const std::string> getResult() const
	{
		return result;
	}

private:

	// view model用到setter时, 应当是将view的改变应用于model, 不会产生notification
	// 这些私有的方法会产生notification, 用于model自己对数据的修改

	void setLatexString(const std::string& str)
	{
		latexString = std::make_shared<std::string>(str);
		latexStringChangedNotify();
	}
	void setLatexString(std::string&& str)
	{
		latexString = std::make_shared<std::string>(std::move(str));
		latexStringChangedNotify();
	}
	void setImageData(const std::vector<Byte>& data)
	{
		imageData = std::make_shared<std::vector<Byte>>(data);
		imageDataChangedNotify();
	}
	void setImageData(std::vector<Byte>&& data)
	{
		imageData = std::make_shared<std::vector<Byte>>(std::move(data));
		imageDataChangedNotify();
	}
	void setVarValPairs(const std::vector<VarValPair>& pair)
	{
		varValPairs = std::make_shared<std::vector<VarValPair>>(pair);
		varValPairsChangedNotify();
	}
	void setVarValPairs(std::vector<VarValPair>&& pair)
	{
		varValPairs = std::make_shared<std::vector<VarValPair>>(std::move(pair));
		varValPairsChangedNotify();
	}
	void setResult(const std::string& res)
	{
		result = std::make_shared<std::string>(res);
		resultChangedNotify();
	}
	void setResult(std::string&& res)
	{
		result = std::make_shared<std::string>(std::move(res));
		resultChangedNotify();
	}
public:

	// 从model向view主动同步数据, 用于初始化
	void notifyAll() const
	{
		latexStringChangedNotify();
		imageDataChangedNotify();
		resultChangedNotify();
		varValPairsChangedNotify();
	}

	/******************** callback function binding ********************/

	void bindCallback_LatexStringChanged(const CallbackFunction& fun)
	{
		latexStringChanged = registerEvent(fun);
	}
	void bindCallback_ImageDataChanged(const CallbackFunction& fun)
	{
		imageDataChanged = registerEvent(fun);
	}
	// 主动同步时使用
	void bindCallback_VarValPairsChanged(const CallbackFunction& fun)
	{
		varValuePairsChanged = registerEvent(fun);
	}
	void bindCallback_ResultChanged(const CallbackFunction& fun)
	{
		resultChanged = registerEvent(fun);
	}

	/******************** event trigger ********************/

	void latexStringChangedNotify() const
	{
		raiseEvent(latexStringChanged);
	}
	void imageDataChangedNotify() const
	{
		raiseEvent(imageDataChanged);
	}
	void varValPairsChangedNotify() const
	{
		raiseEvent(varValuePairsChanged);
	}
	void resultChangedNotify() const
	{
		raiseEvent(resultChanged);
	}
};

