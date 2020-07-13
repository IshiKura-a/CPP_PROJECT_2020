#pragma once
#include "../view/view.h"
#include "../viewmodel/viewmodel.h"
#include "../model/model.h"

#ifndef APP_H
#define APP_H

#endif // APP_H

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

		viewModel->bindModel(model);

		view->setRenderLatexString(viewModel->getRenderLatexString());
		view->setDisplayLatexFormula(viewModel->getGetFormulaResult());
		view->setLoadImg4Dir(viewModel->getLoadImg4Dir());
		view->setChangeLatexFormula(viewModel->getChangeLatexFormula());
		view->setDisplayHelpDocument(viewModel->getDisplayHelpDocument());

		view->setImgLabel(std::make_shared<QLabel>());
		view->setLatexLabel(std::make_shared<QLabel>());
		view->setLatexEditor(std::make_shared<QPlainTextEdit>());
		view->setTimer(std::make_shared<QTimer>());
		view->setLatexStringGetter(viewModel->getLatexString);

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
			[this]() {view->variableValuePairsUpdateNotified(); }
		);

		// 绑定数据
		// TODO:
		// 还没写完, 要把其他数据也绑定上去
		view->setLatexStringGetter(viewModel->getLatexString);
		view->setLatexStringSetter(viewModel->setLatexString);

		// 同步数据
		model->notifyAll();

		// 试试, 如果显示成功就说明数据传输正常
		view->setLatexString("quit");
		model->notifyAll();
	};
	void run()
	{
		view->initQLayout();
		view->show();
	}
};