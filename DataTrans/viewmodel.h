#pragma once
#include "model.h"
// #include "view.h"


#include <iostream>

class Model;
class View;

class ViewModel
{
private:
	using Byte = unsigned char;
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

	EventFunction latexStringViewUpdateNotifier;

	// function

	// ��̬��model�Ĺ��ܺ���
    WorkFunction getFormulaResult;
    WorkFunction renderLatexString;
    WorkFunction loadImg4Dir;
    WorkFunction changeLatexFormula;
    WorkFunction displayHelpDocument;
public:

	// function
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
			[&]() {this->latexStringChangedNotified(); }
		);
	}

/*    void bindView(ptr<View> view)
    {
        this->setLatexStringViewUpdateNotifier(view->getLatexStringViewUpdateNotifier());
    }*/

	// data getter and setter
    auto getLatexString()
    {
        return latexString;
    }

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
	// ��Щ�ص��������Բ������¼��������Ƶķ�������ɶ�̬��
	// ������һʱû������ﶯ̬�󶨵����壬���Ծ�д�ɾ�̬�ĺ�����
	
	void latexStringChangedNotified()
	{
		std::cout << "View model received model saying latex string has changed!\n";

		// ����viewmodel�е�data
		// �˴�Ӧ������viewmodel�е�latex string
		// somefunction()

		// ����view�ĸ����¼�
		latexStringViewUpdateNotify();
	}

	// event trigger

	void latexStringViewUpdateNotify() const
	{
		std::cout << "View model says latex string has changed!\n";
		latexStringViewUpdateNotifier();
	}
};

