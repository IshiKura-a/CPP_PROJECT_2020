#pragma once
#include "../model/model.h"

class ViewModel
{
private:
	using Byte = char;
	using VariableValuePair = std::pair<std::string, double_t>;
	template <typename T>
	using ptr = std::shared_ptr<T>;
	using EventFunction = std::function<void()>;
	using CallbackFunction = std::function<void()>;
	using WorkFunction = std::function<void()>;


	std::shared_ptr<Model> model;

	// TODO:
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

	// notifier
	// 当view model中的数据发生变化时，通知view

	EventFunction latexStringViewUpdateNotifier;
	EventFunction imageDataViewUpdateNotifier;
	EventFunction variableValuePairsViewUpdateNotifier;
	EventFunction resultViewUpdateNotifier;

	// function

	// 用于view的动态绑定

	// TODO:
	// 考虑到view的方法可能带有参数, WorkFunction也许并不适用
	// 也许应该换成std::any
	
	WorkFunction getFormulaResult;
	WorkFunction renderLatexString;
	WorkFunction loadImg4Dir;
	WorkFunction changeLatexFormula;
	WorkFunction displayHelpDocument;
	WorkFunction changeLatexDisplay;
public:

	// function getter

	auto getRenderLatexString()
	{
		return renderLatexString;
	}
	auto getGetFormulaResult()
	{
		return getFormulaResult;
	}
	auto getLoadImg4Dir()
	{
		return loadImg4Dir;
	}
	auto getChangeLatexFormula()
	{
		return changeLatexFormula;
	}
	auto getDisplayHelpDocument()
	{
		return displayHelpDocument;
	}

	// data getter and setter
	// 禁止直接使用getter返回的指针修改数据（这样捕捉不到data changed事件）
	// setter将触发data changed事件, 将view的修改同步到model

	std::shared_ptr<const std::string> getLatexString() const
	{
		return latexString;
	}
	void setLatexString(const std::string& str)
	{
		latexString = std::make_shared<std::string>(str);
		latexStringChangeApplyToModel();
	}
	std::shared_ptr<const std::vector<Byte>> getImageData() const
	{
		return imageData;
	}
	// image data不能被view设置
	//void setImageData(const std::vector<Byte>& data)
	//{
	//	imageData = std::make_shared<std::vector<Byte>>(data);
	//}
	std::shared_ptr<const std::vector<VariableValuePair>> getVariableValuePairs() const
	{
		return variableValuePairs;
	}
	void setVariableValueString(const std::vector<VariableValuePair>& pair)
	{
		variableValuePairs = std::make_shared<std::vector<VariableValuePair>>(pair);
		variableValuePairsChangeApplyToModel();
	}
	std::shared_ptr<const std::string> getResult() const
	{
		return result;
	}
	// result不能被view设置
	//void setResult(const std::string res)
	//{
	//	result = std::make_shared<std::string>(res);
	//}

	// binding

	// 绑定一个model实例，在model触发data changed事件时调用此view model的notified函数
	void bindModel(std::shared_ptr<Model> model)
	{
		this->model = model;
		this->model->setLatexStringChangedNotifier(
			[this]() {this->latexStringChangedNotified(); }
		);
		this->model->setImageDataChangedNotifier(
			[this]() {this->imageDataChangedNotified(); }
		);
		this->model->setVariableValuePairsChangedNotifier(
			[this]() {this->variableValuePairsChangedNotified(); }
		);
		this->model->setResultChangedNotifier(
			[this]() {this->resultChangedNotified(); }
		);
	}


	// event setter

	void setLatexStringViewUpdateNotifier(EventFunction notifier)
	{
		latexStringViewUpdateNotifier = notifier;
	}
	void setImageDataViewUpdateNotifier(EventFunction notifier)
	{
		imageDataViewUpdateNotifier = notifier;
	}
	void setVariableValuePairsViewUpdateNotifier(EventFunction notifier)
	{
		variableValuePairsViewUpdateNotifier = notifier;
	}
	void setResultViewUpdateNotifier(EventFunction notifier)
	{
		resultViewUpdateNotifier = notifier;
	}


	// event callback
	// 这些回调函数可以采用与事件函数类似的方法来达成动态绑定
	// 不过我一时没想出这里动态绑定的意义，所以就写成静态的函数了

	// model->view model->view方向
	// 不需要修改model的数据，需要触发view update

	void latexStringChangedNotified()
	{
		// TODO:
		// 更新view model中的data
		// 此处应当更新view model中的latex string
		// 将model使用的数据结构转成view使用的数据结构
		// 例如latex string就应 string->QString

		auto latex_string = model->getLatexString();
		latexString = std::make_shared<std::string>(*latex_string);

		// 触发view的更新事件
		latexStringViewUpdateNotify();
	}

	void imageDataChangedNotified()
	{
		// TODO:
		// 更新viewmodel中的data
		// 此处应当更新viewmodel中的image data
		// somefunction()

		auto image_data = model->getImageData();
		imageData = std::make_shared<std::vector<Byte>>(*image_data);

		// 触发view的更新事件
		imageDataViewUpdateNotifier();
	}

	// 初始化时会用到
	void variableValuePairsChangedNotified()
	{
		// TODO:
		// 更新viewmodel中的data
		// 此处应当更新viewmodel中的variable value pairs
		// somefunction()
		
		auto variable_value_pairs = model->getVariableValuePairs();
		variableValuePairs = std::make_shared<std::vector<VariableValuePair>>(*variable_value_pairs);

		variableValuePairsViewUpdateNotifier();
	}

	void resultChangedNotified()
	{
		// TODO:
		// 更新viewmodel中的data
		// 此处应当更新viewmodel中的result
		// somefunction()

		auto res = model->getResult();
		result = std::make_shared<std::string>(*res);

		// 触发view的更新事件
		resultViewUpdateNotifier();
	}

	// view->view model->model方向
	// 需要修改model的数据，不需要触发view update

	void latexStringChangeApplyToModel() const
	{
		model->setLatexStringWithoutNotify(*latexString);
	}

	void variableValuePairsChangeApplyToModel() const
	{
		model->setVariableValuePairsWithoutNotify(*variableValuePairs);
	}

	// event trigger

	void latexStringViewUpdateNotify() const
	{
		latexStringViewUpdateNotifier();
	}

	void imageDataViewUpdateNotify() const
	{
		imageDataViewUpdateNotifier();
	}

	void resultViewUpdateNotify() const
	{
		resultViewUpdateNotifier();
	}

};

