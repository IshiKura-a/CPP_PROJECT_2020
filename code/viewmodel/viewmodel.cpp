#include "viewmodel.h"

void ViewModel::bindFunction()
{
	loadImg4Dir = [this](std::any file_path)
	{
		model->getFormulaFromImage(std::any_cast<std::string>(file_path));
	};
}
