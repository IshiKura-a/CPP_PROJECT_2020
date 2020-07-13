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
	//EventFunction variableValuePairsViewUpdateNotifier;
	EventFunction resultViewUpdateNotifier;

	// function
	
	// 用于view的动态绑定

	// 考虑到view的方法可能带有参数, WorkFunction也许并不适用
	// 也许应该换成std::any
	// 
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
	
	// binding

	// 绑定一个model实例，在model触发data changed事件时调用此view model的notified函数
	void bindModel(std::shared_ptr<Model> model)
	{
		this->model = model;
		this->model->setLatexStringChangedNotifier(
			[this]() {this->latexStringChangedNotified(); }
		);
    	this->model->setImageDataChangedNotifier(
			[this](){this->imageDataChangedNotified();}
		);
    	this->model->setResultChangedNotifier(
			[this](){this->resultChangedNotified();}
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
	void setResultViewUpdateNotifier(EventFunction notifier)
    {
	    resultViewUpdateNotifier = notifier;
    }
	

	// event callback
	// 这些回调函数可以采用与事件函数类似的方法来达成动态绑定
	// 不过我一时没想出这里动态绑定的意义，所以就写成静态的函数了
	
	void latexStringChangedNotified()
	{
		// 更新viewmodel中的data
		// 此处应当更新viewmodel中的latex string
		// 将model使用的数据结构转成view使用的数据结构
		// 例如latex string就应 string->QString
		
		latexString = model->getLatexString();

		// 触发view的更新事件
		latexStringViewUpdateNotify();
	}

	void imageDataChangedNotified()
    {
	    // 更新viewmodel中的data
		// 此处应当更新viewmodel中的image data
		// somefunction()

    	imageData = model->getImageData();

		// 触发view的更新事件
		imageDataViewUpdateNotifier();
    }

	void resultChangedNotified()
    {
	    // 更新viewmodel中的data
		// 此处应当更新viewmodel中的result
		// somefunction()

    	result = model->getResult();

		// 触发view的更新事件
		resultViewUpdateNotifier();
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

