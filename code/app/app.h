#pragma once
#include "../view/view.h"
#include "../viewmodel/viewmodel.h"
#include "../model/model.h"


class App
{
private:
	ptr<View> view;
	ptr<ViewModel> viewModel;
	ptr<Model> model;
public:
	App()
	{

		view = std::make_shared<View>();
		viewModel = std::make_shared<ViewModel>();
		model = std::make_shared<Model>();

		// view->setImgLabel(std::make_shared<QLabel>());
		// view->setLatexLabel(std::make_shared<QLabel>());
		view->setLatexEditor(std::make_shared<QPlainTextEdit>());
		view->setTimer(std::make_shared<QTimer>());
		view->setStatusBar(std::make_shared<QStatusBar>());
		view->setEngineSelectionInterface(std::make_shared<EngineSelection>(view.get()));
		view->setCalculateInterface(std::make_shared<Calculation>());
		view->setHelpMsgBox(std::make_shared<QMessageBox>());

		viewModel->bindModel(model);
		viewModel->bindFunction();


		view->setRenderLatexString(viewModel->getRenderLatexString());
		view->setCalculateLatexFormula(viewModel->getGetFormulaResult());
		view->setLoadImg4Dir(viewModel->getGetLatexStringFromImageFile());
		view->setLoadImg4DirB(viewModel->getGetLatexStringFromImageFileB());
		view->setDisplayHelpDocument(viewModel->getDisplayHelpDocument());
		view->setPrettifyLatexFormula(viewModel->getPrettifyFormula());

		


		// view update notification动态绑定
		viewModel->bindCallback_LatexStringUpdateView(
			[this]() {view->latexStringViewUpdateNotified(); }
		);
		viewModel->bindCallback_ImageDataUpdateView(
			[this]() {view->imageDataViewUpdateNotified(); }
		);
		viewModel->bindCallback_VarValPairsUpdateView(
			[this]() {view->resultViewUpdateNotified(); }
		);
		viewModel->bindCallback_ResultUpdateView(
			[this]() {view->varValPairsUpdateNotified(); }
		);

		// 绑定数据
		view->setLatexStringGetter(viewModel->getLatexString);
		view->setLatexStringSetter(viewModel->setLatexString);
		view->setImageDataGetter(viewModel->getImageData);
		view->setVarValPairsGetter(viewModel->getVarValPairs);
		view->setVarValPairsSetter(viewModel->setVarValPairs);
		view->setResultGetter(viewModel->getResult);


		// 同步数据
		model->notifyAll();

	};
	void run()
	{
		view->initQLayout();
		view->show();
	}
};
