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
	try {
		setImageData(manager->downloadRenderedFormula(*latexString, "svg"));
	}
	catch (std::runtime_error& e)
	{
		std::cerr << e.what();
	}
}
