#include <cstdlib>
#include <iostream>
#include <string>

// ToDo: Exercise 1.d - adapt and implement combinations

int combinations(int number)
{
	return 0;
}

int main(int argc, char* argv[])
{
	if (argc != 2)
		return 1; // invalid number of parameters

	int n = std::stoi(argv[1]);

	std::cout << combinations(n) << std::endl;

	return 0;
}
