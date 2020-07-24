#include "model.h"
#include "CppCurl.h"
#include "../module/JsonParser/JsonParser.h"
#include "../module/XMLparser/XMLparser.h"
#include "../module/HelpManual.h"
#include <iostream>

bool isOperator(char ch)
{
	return !isalnum(ch);
}

std::string Model::applyVarValPairs()
{
	if (varValPairs->empty())
		return *latexString;
	auto str = *latexString;
	for (auto& i : *varValPairs)
	{
		auto it = str.find_first_of(i.first);

		while (it != str.npos) {
			int prev = it - 1;
			bool isSubStr = false;
			if (prev >= 0 && !isOperator(str[prev]))
				isSubStr = true;
			else {
				int aft = it + i.first.size();
				if (aft < str.size() && !isOperator(str[aft]))
					isSubStr = true;
			}
			if (!isSubStr) {
				str.erase(it, i.first.length());
				str.insert(it, i.second);
			}
			it = str.find_first_of(i.first, it + 1);
		}
	}
	return str;
}


void Model::getLatexStringFromImage(const std::string& file_path, bool isMathpixAPI)
{
	RequestManager manager;
	try {

		if (isMathpixAPI) {
			auto json = manager->formulaRecognitionMathpix(file_path);
			setLatexString(JsonParser::parseCurlReturnValMathpix(json));
		}
		else
		{

			auto json = manager->formulaRecognitionBaidu(file_path);
			setLatexString(JsonParser::parseCurlReturnValBaidu(json));
		}
	}
	catch (std::runtime_error& e)
	{
		std::cerr << e.what();
	}
}

void Model::renderLatexString(const std::string& image_format)
{
	RequestManager manager;
	try {
		setImageData(manager->downloadRenderedFormula(*latexString, image_format));
	}
	catch (std::runtime_error& e)
	{
		std::cerr << e.what();
	}
}

void Model::calculateLatexString()
{
	RequestManager manager;
	try
	{
		setResult(XMLParser::parseCurlResult(manager->getFormulaResult("0+" + applyVarValPairs())));
	}
	catch (std::runtime_error& e)
	{
		std::cerr << e.what();
	}
}

std::string Model::getHelpManual()
{
	return HelpManual;
}

void Model::prettifyLatexString()
{
	std::string str(100, ' ');
	int count = 0;
	bool isStr = false;
	for (auto& i : *latexString)
	{
		if (i == '\'' || i == '\"')
			isStr = !isStr;
		if (!isStr && i != ' ' && i != '\n' && i != '\r')
			str[count++] = i;
		if (count == str.size())
			str.resize(count * 2);
	}
	str.resize(count);
	setLatexString(str);
}
