#include <iostream>
#include <list>
#include <string>
#include <vector>

// function template for printing contents of containers to std::cout
template <class T>
void printContainer(T& container)
{
	std::cout << "{ ";
	for (const auto& element : container)
	{
		std::cout << element << " ";
	}
	std::cout << "}" << std::endl;
}

// TODO 4.2a - Merge front-back pairings of elements of inContainer into outContainer.
template <class T>
T front_back_pairing(const T& inContainer)
{
	T outContainer{};

	return outContainer;
}

// TODO 4.2b - Remove all duplicates from the given container.
template <class T, class DataType = typename T::value_type>
void remove_duplicates(T& container)
{
	// Use DataType as data type for the chosen temporary data container
}

// TODO 4.2c - Expand the given container by inserting the numerical
//             differences of each element to its neighbors.
template <class T>
void insert_differences(T& container)
{}

void testFrontBackPairingFunctionality()
{
	// define sample data
	const std::vector<int> sampleDataInt = { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
	const std::list<std::string> sampleDataString = { "Die",     "eines", "ist",  "Gebrauch", "der",
													  "Sprache", "in",    "sein", "Wortes",   "Bedeutung" };

	// test for integer vector
	const auto helpIntVector = front_back_pairing(sampleDataInt);
	printContainer(sampleDataInt);
	printContainer(helpIntVector);

	// test for string list
	const auto helpStringList = front_back_pairing(sampleDataString);
	printContainer(sampleDataString);
	printContainer(helpStringList);
}

void testRemoveDuplicateFunctionality()
{
	// define sample data
	std::vector<int> sampleDataInt = { 10, 11, 10, 13, 14, 15, 15, 15, 18, 19, 12, 11, 17 };
	std::list<std::string> sampleDataString = { "Die",       "___",     "eines", "ist",   "Gebrauch",
												"der",       "Sprache", "in",    "sein",  "Wortes",
												"Bedeutung", "Die",     "ist",   "blabla" };

	// test for integer vector
	printContainer(sampleDataInt);
	remove_duplicates(sampleDataInt);
	printContainer(sampleDataInt);

	// test for string vector
	printContainer(sampleDataString);
	remove_duplicates(sampleDataString);
	printContainer(sampleDataString);
}

void testAddDifferenceFunctionality()
{
	// define sample data
	std::list<int> sampleDataInt = { 10, 11, 14, 16, 1, 18 };

	// test for integer vector
	printContainer(sampleDataInt);
	insert_differences(sampleDataInt);
	printContainer(sampleDataInt);
}

int main()
{
	testFrontBackPairingFunctionality();
	std::cout << std::endl;
	testRemoveDuplicateFunctionality();
	std::cout << std::endl;
	testAddDifferenceFunctionality();

	return 0;
}
