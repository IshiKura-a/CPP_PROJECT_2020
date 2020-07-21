#include "model.h"
#include "CppCurl.h"
#include "../module/JsonParser/JsonParser.h"
#include "../module/XMLparser/XMLparser.h"
#include "../module/HelpManual.h"
#include <iostream>

void Model::getLatexStringFromImage(const std::string& file_path)
{
	RequestManager manager;
	try {
		auto json = manager->formulaRecognitionMathpix(file_path);
		setLatexString(JsonParser::parseCurlReturnValMathpix(json));
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
		setResult(XMLParser::parseCurlResult(manager->getFormulaResult(*latexString)));
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
	std::string str(100,' ');
	int count = 0;
	for (auto& i : *latexString)
	{
		if (i != ' ' && i != '\n' && i != '\r')
			str[count++] = i;
		if(count==str.size())
			str.resize(count*2);
	}
	str.resize(count);
	setLatexString(str);
}
