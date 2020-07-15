#include "model.h"
#include "CppCurl.h"
#include "../module/JsonParser/JsonParser.h"
#include <iostream>



void Model::getFormulaFromImage(std::string file_path)
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

void Model::renderLatexFormula()
{
	RequestManager manager;
	try {
		setImageData(manager->downloadRenderedFormula(*latexString, "svg"));
	}
	catch (std::runtime_error& e)
	{
		std::cerr << e.what();
	}
}
