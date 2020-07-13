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

	// ���ڽ�������ȾͼƬ��latex string
	ptr<std::string> latexString;
	// ��Ⱦ��ͼƬ�Ķ���������
	ptr<std::vector<Byte>> imageData;
	// ��ʽ�еı���-ֵ��
	ptr<std::vector<VariableValuePair>> variableValuePairs;
	// ��ʽ������
	ptr<std::string> result;
	
	// notifier
	// ��model�е����ݷ����仯ʱ��֪ͨview model

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
	// ����޸���model�е�����, ��Ҫ���ö�Ӧ��notify������ʹ��setter

	// ��ͼƬ�ļ�, ������model��imageData
	// @param:
	// file_path: ��Ҫ��ȡ��ͼƬ·��
	void openImage(std::string file_path);

	// ��Ⱦmodel�е�latexString, ������model��imageData
	void renderLatexFormula();

	// ��ȡ������Ϣ
	// @return:
	// ������Ϣ��string
	std::string getHelpManual();

	// ʹ��model�е�latexString, ����ʽ�����ɱ��ʽ��
	void parseFormula();

	// ʹ��model�е�variableValuePairs, ������ʽ�����
	// ����model��result
	void calculateFormula();


	// data getter and setter

	//һЩreminder:
	// ��ֱֹ��ʹ��getter���ص�ָ���޸����ݣ�������׽����data changed�¼���
	// set without notify����view model��model��Ӧ��view���޸�
	// �Ƿ���Ҫ����ϸ�������޸Ĺ���, ����variableValuePairs.push_back

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

	// view model�õ�setterʱ, Ӧ���ǽ�view�ĸı�Ӧ����model
	// ���view modelʹ�õ�setter�������notification
	// ��Щ˽�еķ��������notification, ����model�Լ������ݵ��޸�
	
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

	// ����ͬ��MVVM����, ���ڳ�ʼ��
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
	// ��ʼ��ʱ�õ�
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

