#pragma once
#include <functional>
#include <memory>
#include <string>
#include <vector>


#include <iostream>

class ViewModel;

class Model
{
private:
	using Byte = unsigned char;
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

	void getFormulaResult();

	// data getter and setter

	//һЩreminder:
	// ���ʹ�÷��ص�ָ���޸���model�����ݣ��Ƿ�׽����data changed�¼��ˣ�


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
	void setImageData(const std::vector<Byte>& data)
	{
		imageData = std::make_shared<std::vector<Byte>>(data);
	}
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


	
	// event getter and setter

	void setLatexStringChangedNotifier(EventFunction notifier)
	{
		latexStringChangedNotifier = notifier;
	}
	auto getLatexStringChangedNotifier() const
	{
		return latexStringChangedNotifier;
	}
	void setImageDataChangedNotifier(EventFunction notifier)
	{
		imageDataChangedNotifier = notifier;
	}
	auto getImageDataChangedNotifier() const
	{
		return imageDataChangedNotifier;
	}
	void setVariableValuePairsChangedNotifier(EventFunction notifier)
	{
		variableValuePairsChangedNotifier = notifier;
	}
	auto getVariableValuePairsChangedNotifier() const
	{
		return variableValuePairsChangedNotifier;
	}
	void setResultChangedNotifier(EventFunction notifier)
	{
		resultChangedNotifier = notifier;
	}
	auto getResultChangedNotifier() const
	{
		return resultChangedNotifier;
	}
	
	// event trigger

	void latexStringChangedNotify() const
	{
		std::cout << "Model says latex string has changed!\n";
		latexStringChangedNotifier();
	}
	void imageDataChangedNotify() const
	{
		std::cout << "Model says image data has changed!\n";
		imageDataChangedNotifier();
	}
	void variableValuePairsChangedNotify() const
	{
		std::cout << "Model says variable-value pairs have changed!\n";
		variableValuePairsChangedNotifier();
	}
	void resultChangedNotify() const
	{
		std::cout << "Model says result has changed!\n";
		resultChangedNotifier();
	}
};

