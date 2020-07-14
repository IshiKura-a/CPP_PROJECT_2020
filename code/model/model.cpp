#include "model.h"
#include "CppCurl.h"
#include "../module/JsonParser/JsonParser.h"

void Model::openImage(std::string file_path)
{
	RequestManager manager;
	setImageData(manager->openImage(file_path));
}


void Model::parseFormula()
{
	RequestManager manager;
	auto json = manager->formulaRecognitionMathpix(*imageData, "png");
	setLatexString(JsonParser::parseCurlReturnValMathpix(json));
}
