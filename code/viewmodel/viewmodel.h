#pragma once
#include "../model/model.h"
#include "../common/def.h"
#include "../common/notifiable.h"
#include <QString>
#include <QByteArray>
#include <QVector>

class ViewModel :public Notifiable
{
private:

	ptr<Model> model;

	// 用于解析和渲染图片的latex string
	ptr<QString> latexString;
	// 渲染后图片的二进制数据
	ptr<QByteArray> imageData;
	// 公式中的变量-值组
	ptr<QVector<VarValPair>> varValPairs;
	// 公式计算结果
	ptr<QString> result;

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
	// WorkFunctionWithRetVal: 参数为void, 返回std::any

	// 使用model中的variableValuePairs, 计算表达式树结果
	// 更新model的result
	WorkFunctionNoArg getFormulaResult;
	
	// 渲染model中的latexString, 并更新model的imageData
	// @param: std::string
	// 设定渲染结果的格式, 支持png,gif,svg
	WorkFunction renderLatexString;
	
	// 识别路径为file_path的图片. 识别结果将覆盖latex string.
	// @param: std::string file_path
	// 需要读取的图片路径
	WorkFunction getLatexStringFromImageFile;

	// 识别路径为file_path的图片. 识别结果将覆盖latex string.
	// @param: std::string file_path
	// 需要读取的图片路径
	// 使用baidu的API
	WorkFunction getLatexStringFromImageFileB;
	
	// 获取帮助信息
	// @return:
	// 帮助信息的string
	WorkFunctionWithRetVal displayHelpDocument;

	// 将latex string中多余的空格删除
	WorkFunctionNoArg prettifyFormula;

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
	auto getGetLatexStringFromImageFile() const
	{
		return getLatexStringFromImageFile;
	}
	auto getGetLatexStringFromImageFileB() const
	{
		return getLatexStringFromImageFileB;
	}
	auto getDisplayHelpDocument() const
	{
		return displayHelpDocument;
	}
	auto getPrettifyFormula() const
	{
		return prettifyFormula;
	}

	/******************** data getter and setter ********************/
	// 禁止直接使用getter返回的指针修改数据(这样捕捉不到data changed事件)
	// setter会将view的修改同步到model
	// 直接使用lambda函数便于view的绑定

	Getter<ptr<QString>> getLatexString = [this]() {return latexString; };
	Setter<QString> setLatexString = [this](const QString& str)
	{
		latexString = std::make_shared<QString>(str);
		this->latexStringChangeApplyToModel();
	};

	Getter<ptr<QByteArray>> getImageData = [this]() {return imageData; };
	// image data不能被view设置


	Getter<ptr<const QVector<VarValPair>>> getVarValPairs = [this]() {return varValPairs; };
	Setter<QVector<VarValPair>> setVarValPairs = [this](const QVector<VarValPair>& pair)
	{
		varValPairs = std::make_shared<QVector<VarValPair>>(pair);
		this->varValPairsChangeApplyToModel();
	};

	Getter<ptr<QString>> getResult = [this]() {return result; };
	// result不能被view设置

	/******************** binding ********************/

	// 绑定一个model实例，在model触发数据成员变化事件时调用此view model的notified函数
	void bindModel(ptr<Model> model);

	// 绑定功能函数
	void bindFunction();

	/******************** callback function binding ********************/

	void bindCallback_LatexStringUpdateView(const CallbackFunction& fun)
	{
		latexStringUpdateView = registerEvent(fun);
	}
	void bindCallback_ImageDataUpdateView(const CallbackFunction& fun)
	{
		imageDataUpdateView = registerEvent(fun);
	}
	void bindCallback_VarValPairsUpdateView(const CallbackFunction& fun)
	{
		varValPairsUpdateView = registerEvent(fun);
	}
	void bindCallback_ResultUpdateView(const CallbackFunction& fun)
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
		const auto latex_string = model->getLatexString();
		latexString = std::make_shared<QString>(latex_string->c_str());

		// 触发view的更新事件
		latexStringUpdateViewNotify();
	}

	void imageDataChangedNotified()
	{
		const auto image_data = model->getImageData();
		imageData = std::make_shared<QByteArray>(image_data->data(), image_data->size());

		// 触发view的更新事件
		imageDataUpdateViewNotify();
	}

	// model向上同步数据时会用到
	void varValPairsChangedNotified()
	{
		const auto variable_value_pairs = model->getVarValPairs();
		varValPairs = std::make_shared<QVector<VarValPair>>(variable_value_pairs->begin(), variable_value_pairs->end());

		// 触发view的更新事件
		varValPairsUpdateViewNotify();
	}

	void resultChangedNotified()
	{
		const auto res = model->getResult();
		result = std::make_shared<QString>(res->c_str());

		// 触发view的更新事件
		resultUpdateViewNotify();
	}

	// view->view model->model方向
	// 需要修改model的数据，不需要触发update view

	void latexStringChangeApplyToModel() const
	{
		model->setLatexStringWithoutNotify(latexString->toStdString());
	}

	void varValPairsChangeApplyToModel() const
	{
		model->setVarValPairsWithoutNotify(std::vector<VarValPair>(varValPairs->begin(), varValPairs->end()));
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
