#include <cstdlib>
#include <iostream>
#include <string>

void change(const int due, const int paid, std::ostream& out)
{
	// ToDo: compute and write set of change tuples to output stream
}

int main(int argc, char* argv[])
{
	if (argc != 3)
		return 1; // invalid number of parameters

	int due = std::stoi(argv[1]);
	int paid = std::stoi(argv[2]);

	// ToDo: catch invalid arguments

	change(due, paid, std::cout);

	// ToDo: write change data as CSV to file if necessary

	return 0;
}
