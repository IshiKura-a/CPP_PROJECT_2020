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


	// function
	// ����޸���model�е�����, ��Ҫ���ö�Ӧ��notify����

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
	// ���ʹ�÷��ص�ָ���޸���model�����ݣ��Ƿ�׽����data changed�¼��ˣ�
	// �Ƿ���Ҫ����ϸ�������޸Ĺ���, ����variableValuePairs.push_back


	const auto& getLatexString() const
	{
		return latexString;
	}
	void setLatexString(const std::string& str)
	{
		latexString = std::make_shared<std::string>(str);
	}
	const auto& getImageData() const
	{
		return imageData;
	}
	// image data���ܱ�view model����
private:
	void setImageData(const std::vector<Byte>& data)
	{
		imageData = std::make_shared<std::vector<Byte>>(data);
	}
public:
	const auto& getVariableValuePairs() const
	{
		return variableValuePairs;
	}
	void setVariableValueString(const std::vector<VariableValuePair>& pair)
	{
		variableValuePairs = std::make_shared<std::vector<VariableValuePair>>(pair);
	}
	const auto& getResult() const
	{
		return result;
	}
	// result���ܱ�view model����
private:
	void setResult(const std::string res)
	{
		result = std::make_shared<std::string>(res);
	}
public:


	
	// event setter

	void setLatexStringChangedNotifier(EventFunction notifier)
	{
		latexStringChangedNotifier = notifier;
	}
	void setImageDataChangedNotifier(EventFunction notifier)
	{
		imageDataChangedNotifier = notifier;
	}
	// model��Ų��������޸�variableValuePairs?
	// һ��Ӧ��ֻ����view model�޸�?
	// ��ʱ�������notifier, ���о��ò���
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

