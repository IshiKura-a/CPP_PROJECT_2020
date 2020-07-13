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

	// ��������������Ҫ�ĳɶ�Ӧ��Qt��
	// ********************************
	// ���ڽ�������ȾͼƬ��latex string
	ptr<std::string> latexString;
	// ��Ⱦ��ͼƬ�Ķ���������
	ptr<std::vector<Byte>> imageData;
	// ��ʽ�еı���-ֵ��
	ptr<std::vector<VariableValuePair>> variableValuePairs;
	// ��ʽ������
	ptr<std::string> result;
	// ********************************
	
	// notifier
	// ��view model�е����ݷ����仯ʱ��֪ͨview
	
	EventFunction latexStringViewUpdateNotifier;
	EventFunction imageDataViewUpdateNotifier;
	//EventFunction variableValuePairsViewUpdateNotifier;
	EventFunction resultViewUpdateNotifier;

	// function
	
	// ����view�Ķ�̬��

	// ���ǵ�view�ķ������ܴ��в���, WorkFunctionҲ��������
	// Ҳ��Ӧ�û���std::any
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

	// ��һ��modelʵ������model����data changed�¼�ʱ���ô�view model��notified����
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
	// ��Щ�ص��������Բ������¼��������Ƶķ�������ɶ�̬��
	// ������һʱû������ﶯ̬�󶨵����壬���Ծ�д�ɾ�̬�ĺ�����
	
	void latexStringChangedNotified()
	{
		// ����viewmodel�е�data
		// �˴�Ӧ������viewmodel�е�latex string
		// ��modelʹ�õ����ݽṹת��viewʹ�õ����ݽṹ
		// ����latex string��Ӧ string->QString
		
		latexString = model->getLatexString();

		// ����view�ĸ����¼�
		latexStringViewUpdateNotify();
	}

	void imageDataChangedNotified()
    {
	    // ����viewmodel�е�data
		// �˴�Ӧ������viewmodel�е�image data
		// somefunction()

    	imageData = model->getImageData();

		// ����view�ĸ����¼�
		imageDataViewUpdateNotifier();
    }

	void resultChangedNotified()
    {
	    // ����viewmodel�е�data
		// �˴�Ӧ������viewmodel�е�result
		// somefunction()

    	result = model->getResult();

		// ����view�ĸ����¼�
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

