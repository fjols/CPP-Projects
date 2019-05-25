#include<iostream>
#include<string>
#define ADD(a, b) (a + b)
#define SUB(a, b) (a - b)
#define MULT(a, b) (a * b)
#define DIV(a, b) (a / b)

int main()
{
	int iNumOne = 5;
	int iNumTwo = 8;
	int iResult;
	char cOperator;

	std::cout << "Input an operator to use: ";
	std::cin >> cOperator;

	switch (cOperator)
	{
	case '+':
		iResult = ADD(iNumOne, iNumTwo);
		std::cout << "Addition Preprocessor Result: " << iResult << std::endl;
		break;
	case '-':
		iResult = SUB(iNumOne, iNumTwo);
		std::cout << "Subtraction Preprocessor Result: " << iResult << std::endl;
		break;
	case '*':
		iResult = MULT(iNumOne, iNumTwo);
		std::cout << "Multiplication Preprocessor Result: " << iResult << std::endl;
		break;
	case '/':
		iResult = DIV(iNumOne, iNumTwo);
		std::cout << "Division Preprocessor Result: " << iResult << std::endl;
		break;

	default:
		std::cout << "Error" << std::endl;
		break;
	}
	
	system("pause");
	return 0;
}