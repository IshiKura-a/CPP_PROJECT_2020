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
		model->getLatexStringFromImage(std::any_cast<std::string>(file_path));
	};
	renderLatexString = [this](std::any image_format)
	{
		model->renderLatexString(std::any_cast<std::string>(image_format));
	};
	getFormulaResult = [this]()
	{
		model->calculateLatexString();
	};
	displayHelpDocument = [this]()
	{
		return model->getHelpManual();
	};
	prettifyFormula = [this]()
	{
		model->prettifyLatexString();
	};
}
