#include <cstdlib>
#include <iostream>
#include <string>

int fibonacci(int number)
{
	// ToDo: Exercise 1.c - count number of calculation steps

	// ToDo: Exercise 1.b - return 0 on bad arguments

	// ToDo: Exercise 1.b - retrieve nth fibonacci number iteratively

	return 0;
}

int main(int argc, char* argv[])
{
	if (argc != 2)
		return 1; // invalid number of parameters

	int n = std::stoi(argv[1]);

	// ToDo: Exercise 1.c - print calculation steps

	std::cout << fibonacci(n) << std::endl;

	return 0;
}
