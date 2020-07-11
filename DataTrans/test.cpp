#include "model.h"
#include "viewmodel.h"


int main()
{
	std::shared_ptr<Model> m = std::make_shared<Model>();
	std::shared_ptr<ViewModel> vm = std::make_shared<ViewModel>();
	vm->bindModel(m);
	
	// 这一步应该包在view绑定viewmodel的过程中
	vm->setLatexStringViewUpdateNotifier([](){std::cout<<"View says nothing.\n";});
	
	m->latexStringChangedNotify();
	system("pause");
}
