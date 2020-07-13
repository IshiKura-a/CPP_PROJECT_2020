#pragma once
#include "../model/model.h"
#include "../common/def.h"
#include "../common/notifiable.h"

class ViewModel :public Notifiable
{
private:

	ptr<Model> model;

	// TODO:
	// 下列数据类型需要改成对应的Qt类
	// ********************************
	// 用于解析和渲染图片的latex string
	ptr<std::string> latexString;
	// 渲染后图片的二进制数据
	ptr<std::vector<Byte>> imageData;
	// 公式中的变量-值组
	ptr<std::vector<VarValPair>> varValPairs;
	// 公式计算结果
	ptr<std::string> result;
	// ********************************

	/******************** notifier ********************/
	// 当model中的数据发生变化时, 通知view model

	EventId latexStringUpdateView = EventUnregistered;
	EventId imageDataUpdateView = EventUnregistered;
	EventId varValPairsUpdateView = EventUnregistered;
	EventId resultUpdateView = EventUnregistered;

	/******************** function pointer ********************/

	// 用于view的动态绑定
	// WorkFunction: 参数为std::any
	// WorkFunctionNoArg: 参数为void

	WorkFunctionNoArg getFormulaResult;
	WorkFunctionNoArg renderLatexString;
	WorkFunctionNoArg loadImg4Dir;
	WorkFunctionNoArg changeLatexFormula;
	WorkFunctionNoArg displayHelpDocument;
	WorkFunctionNoArg changeLatexDisplay;

public:

	/******************** function getter ********************/

	auto getRenderLatexString() const
	{
		return renderLatexString;
	}
	auto getGetFormulaResult() const
	{
		return getFormulaResult;
	}
	auto getLoadImg4Dir() const
	{
		return loadImg4Dir;
	}
	auto getChangeLatexFormula() const
	{
		return changeLatexFormula;
	}
	auto getDisplayHelpDocument() const
	{
		return displayHelpDocument;
	}

	/******************** data getter and setter ********************/
	// 禁止直接使用getter返回的指针修改数据(这样捕捉不到data changed事件)
	// setter会将view的修改同步到model
	// getter直接使用lambda函数, 便于view的绑定

	Getter<ptr<const std::string>> getLatexString = [this]()
	{return latexString; };
	Setter<std::string> setLatexString = [this](const std::string& str)
	{
		latexString = std::make_shared<std::string>(str);
		this->latexStringChangeApplyToModel();
	};
	Getter<ptr<const std::vector<Byte>>> getImageData = [this]() {return imageData; };
	// image data不能被view设置
	//void setImageData(const std::vector<Byte>& data)
	//{
	//	imageData = std::make_shared<std::vector<Byte>>(data);
	//}
	Getter<ptr<const std::vector<VarValPair>>> getVarValPairs = [this]() {return varValPairs; };
	Setter<std::vector<VarValPair>> setVarValPairs = [this](std::vector<VarValPair> pair)
	{
		varValPairs = std::make_shared<std::vector<VarValPair>>(pair);
		this->varValPairsChangeApplyToModel();
	};
	Getter<ptr<const std::string>> getResult = [this]() {return result; };
	// result不能被view设置
	//void setResult(const std::string res)
	//{
	//	result = std::make_shared<std::string>(res);
	//}

	/******************** binding ********************/

	// 绑定一个model实例，在model触发data changed事件时调用此view model的notified函数
	void bindModel(ptr<Model> model)
	{
		this->model = model;
		this->model->bindCallback_LatexStringChanged(
			[this]() {this->latexStringChangedNotified(); }
		);
		this->model->bindCallback_ImageDataChanged(
			[this]() {this->imageDataChangedNotified(); }
		);
		this->model->bindCallback_VarValPairsChanged(
			[this]() {this->varValPairsChangedNotified(); }
		);
		this->model->bindCallback_ResultChanged(
			[this]() {this->resultChangedNotified(); }
		);
	}

	/******************** callback function binding ********************/

	void bindCallback_LatexStringUpdateView(CallbackFunction fun)
	{
		latexStringUpdateView = registerEvent(fun);
	}
	void bindCallback_ImageDataUpdateView(CallbackFunction fun)
	{
		imageDataUpdateView = registerEvent(fun);
	}
	void bindCallback_VarValPairsUpdateView(CallbackFunction fun)
	{
		varValPairsUpdateView = registerEvent(fun);
	}
	void bindCallback_ResultUpdateView(CallbackFunction fun)
	{
		resultUpdateView = registerEvent(fun);
	}


	/******************** callback function ********************/
	// 这些回调函数可以和以上函数一样动态绑定
	// 不过我一时没想出这里动态绑定的意义，所以就写成静态的函数了

	// model->view model->view方向
	// 不需要修改model的数据，需要触发update view

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
		latexStringUpdateViewNotify();
	}

	void imageDataChangedNotified()
	{
		// TODO:
		// 更新view model中的data
		// 此处应当更新view model中的image data
		// somefunction()

		auto image_data = model->getImageData();
		imageData = std::make_shared<std::vector<Byte>>(*image_data);

		// 触发view的更新事件
		imageDataUpdateViewNotify();
	}

	// 初始化时会用到
	void varValPairsChangedNotified()
	{
		// TODO:
		// 更新view model中的data
		// 此处应当更新view model中的variable value pairs
		// somefunction()

		auto variable_value_pairs = model->getVarValPairs();
		varValPairs = std::make_shared<std::vector<VarValPair>>(*variable_value_pairs);

		// 触发view的更新事件
		varValPairsUpdateViewNotify();
	}

	void resultChangedNotified()
	{
		// TODO:
		// 更新view model中的data
		// 此处应当更新view model中的result
		// somefunction()

		auto res = model->getResult();
		result = std::make_shared<std::string>(*res);

		// 触发view的更新事件
		resultUpdateViewNotify();
	}

	// view->view model->model方向
	// 需要修改model的数据，不需要触发update view

	void latexStringChangeApplyToModel() const
	{
		model->setLatexStringWithoutNotify(*latexString);
	}

	void varValPairsChangeApplyToModel() const
	{
		model->setVarValPairsWithoutNotify(*varValPairs);
	}

	/******************** event trigger ********************/

	void latexStringUpdateViewNotify() const
	{
		raiseEvent(latexStringUpdateView);
	}

	void imageDataUpdateViewNotify() const
	{
		raiseEvent(imageDataUpdateView);
	}

	void varValPairsUpdateViewNotify() const
	{
		raiseEvent(varValPairsUpdateView);
	}

	void resultUpdateViewNotify() const
	{
		raiseEvent(resultUpdateView);
	}

};
