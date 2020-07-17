#include "model.h"
#include "CppCurl.h"
#include "../module/JsonParser/JsonParser.h"
#include "../module/XMLparser/XMLparser.h"
#include <iostream>

void Model::getFormulaFromImage(const std::string& file_path)
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

void Model::renderLatexFormula(const std::string& image_format)
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

void Model::calculateFormula()
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

