#include "viewmodel.h"

void ViewModel::bindModel(ptr<Model> model)
{
	{
		this->model = model;
		this->model->bindCallback_LatexStringChanged(
			[this]() {this->latexStringChangedNotified(); }
		);
		this->model->bindCallback_ImageDataChanged(
			[this]() {this->imageDataChangedNotified(); }
		);
		this->model->bindCallback_VarValPairsChanged(
			[this]() {this->varValPairsChangedNotified(); }
		);
		this->model->bindCallback_ResultChanged(
			[this]() {this->resultChangedNotified(); }
		);
	}
}


void ViewModel::bindFunction()
{
	loadImg4Dir = [this](std::any file_path)
	{
		model->openImage(std::any_cast<std::string>(file_path));
		model->parseFormula();
	};
}
