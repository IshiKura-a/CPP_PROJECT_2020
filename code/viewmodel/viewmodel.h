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
	EventFunction variableValuePairsViewUpdateNotifier;
	EventFunction resultViewUpdateNotifier;

	// function

	// ����view�Ķ�̬��

	// TODO:
	// ���ǵ�view�ķ������ܴ��в���, WorkFunctionҲ��������
	// Ҳ��Ӧ�û���std::any
	
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
	// ��ֱֹ��ʹ��getter���ص�ָ���޸����ݣ�������׽����data changed�¼���
	// setter������data changed�¼�, ��view���޸�ͬ����model

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
	// image data���ܱ�view����
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
	// result���ܱ�view����
	//void setResult(const std::string res)
	//{
	//	result = std::make_shared<std::string>(res);
	//}

	// binding

	// ��һ��modelʵ������model����data changed�¼�ʱ���ô�view model��notified����
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
	// ��Щ�ص��������Բ������¼��������Ƶķ�������ɶ�̬��
	// ������һʱû������ﶯ̬�󶨵����壬���Ծ�д�ɾ�̬�ĺ�����

	// model->view model->view����
	// ����Ҫ�޸�model�����ݣ���Ҫ����view update

	void latexStringChangedNotified()
	{
		// TODO:
		// ����view model�е�data
		// �˴�Ӧ������view model�е�latex string
		// ��modelʹ�õ����ݽṹת��viewʹ�õ����ݽṹ
		// ����latex string��Ӧ string->QString

		auto latex_string = model->getLatexString();
		latexString = std::make_shared<std::string>(*latex_string);

		// ����view�ĸ����¼�
		latexStringViewUpdateNotify();
	}

	void imageDataChangedNotified()
	{
		// TODO:
		// ����viewmodel�е�data
		// �˴�Ӧ������viewmodel�е�image data
		// somefunction()

		auto image_data = model->getImageData();
		imageData = std::make_shared<std::vector<Byte>>(*image_data);

		// ����view�ĸ����¼�
		imageDataViewUpdateNotifier();
	}

	// ��ʼ��ʱ���õ�
	void variableValuePairsChangedNotified()
	{
		// TODO:
		// ����viewmodel�е�data
		// �˴�Ӧ������viewmodel�е�variable value pairs
		// somefunction()
		
		auto variable_value_pairs = model->getVariableValuePairs();
		variableValuePairs = std::make_shared<std::vector<VariableValuePair>>(*variable_value_pairs);

		variableValuePairsViewUpdateNotifier();
	}

	void resultChangedNotified()
	{
		// TODO:
		// ����viewmodel�е�data
		// �˴�Ӧ������viewmodel�е�result
		// somefunction()

		auto res = model->getResult();
		result = std::make_shared<std::string>(*res);

		// ����view�ĸ����¼�
		resultViewUpdateNotifier();
	}

	// view->view model->model����
	// ��Ҫ�޸�model�����ݣ�����Ҫ����view update

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

