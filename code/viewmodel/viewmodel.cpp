#include "viewmodel.h"

void ViewModel::bindFunction()
{
	loadImg4Dir = [this](std::any file_path)
	{
		model->openImage(std::any_cast<std::string>(file_path));
		model->parseFormula();
	};
}
