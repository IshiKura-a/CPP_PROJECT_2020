#include "CppCurl.h"
#include <iostream>
#include <fstream>
#include <ctime>
#pragma comment(lib,"CppCurl.lib")

int main()
{

	RequestManager manager;

	std::string latex = "\\sigma(z)=\\frac{1}{1+e^{-z}}";

	auto time = clock();

	std::cout << "Trying fetching rendered latex formula image...\n\n";
	// get image in buffer

	try {
		time = clock();
		
		auto formula_buffer = manager->downloadRenderedFormula(latex, "svg");

		std::cout << "Successfully download image in buffer.\n";
		std::cout << "time = " << clock() - time << "\n\n";

		time = clock();
		
		manager->saveImage(formula_buffer, "formula_buffer.svg");

		std::cout << "Successfully save buffer in ./formula_buffer.svg.\n";
		std::cout << "time = " << clock() - time << "\n\n";
	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what();
	}

	// get image as file
	try {
		time = clock();
		
		manager->downloadRenderedFormula(latex, "formula.svg", "svg");

		std::cout << "Successfully download image as file in ./formula.svg\n";
		std::cout << "time = " << clock() - time << "\n\n";
	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what();
	}

	// test recognition API

	std::cout << "\n\nUsing baidu API...\n\n";

	// using vector<Byte>

	try {
		time = clock();
		
		auto s = manager->openImage("maxwell.png");

		std::cout << manager->formulaRecognitionBaidu(s) << std::endl;
		std::cout << "time = " << clock() - time << "\n\n";
	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what();
	}


	std::cout << "\n\nUsing mathpix API...\n\n";

	// using file path

	try {
		time = clock();
		std::cout << manager->formulaRecognitionMathpix("maxwell.png") << std::endl;
		std::cout << "time = " << clock() - time << "\n\n";
	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what();
	}

	system("pause");
}