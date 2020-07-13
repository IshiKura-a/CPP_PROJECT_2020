#include "model.h"
#include "viewmodel.h"
#include "view.h"
#include <iostream>


int main()
{
	std::shared_ptr<Model> m = std::make_shared<Model>();
	std::shared_ptr<ViewModel> vm = std::make_shared<ViewModel>();
	std::shared_ptr<View> v = std::make_shared<View>();
	vm->bindModel(m);

	// notification动态绑定
	vm->setLatexStringViewUpdateNotifier(
		[&v]() {v->latexStringViewUpdateNotified(); }
	);
	vm->setImageDataViewUpdateNotifier(
		[&v]() {v->imageDataViewUpdateNotified(); }
	);
	vm->setResultViewUpdateNotifier(
		[&v]() {v->resultViewUpdateNotified(); }
	);

	// function动态绑定
	v->setChangeLatexFormula(vm->getChangeLatexFormula());


	m->latexStringChangedNotify();
	system("pause");
}
