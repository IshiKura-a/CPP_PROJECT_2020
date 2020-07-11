#include "model.h"
#include "viewmodel.h"


int main()
{
	std::shared_ptr<Model> m = std::make_shared<Model>();
	std::shared_ptr<ViewModel> vm = std::make_shared<ViewModel>();
	vm->bindModel(m);
	
	// ��һ��Ӧ�ð���view��viewmodel�Ĺ�����
	vm->setLatexStringViewUpdateNotifier([](){std::cout<<"View says nothing.\n";});
	
	m->latexStringChangedNotify();
	system("pause");
}
