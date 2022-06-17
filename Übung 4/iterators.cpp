#include <iostream>
#include <list>
#include <string>
#include <vector>

// function template for printing contents of containers to std::cout
template <class T>
void printContainer(T& container)
{
	std::cout << "{ ";
	for(const auto& element : container)
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

	outContainer = inContainer;
	auto in_ptr_front = inContainer.begin();
	auto in_ptr_back = inContainer.end();
	auto out_ptr = outContainer.begin();
	in_ptr_back--;
	

	while(out_ptr != outContainer.end()){

		*out_ptr=*in_ptr_front;
		out_ptr++;
		if(out_ptr != outContainer.end()){
			*out_ptr=*in_ptr_back;
			out_ptr++;
		}

		in_ptr_front++;
		in_ptr_back--;

	}
	return outContainer;
}

// TODO 4.2b - Remove all duplicates from the given container.
template <class T, class DataType = typename T::value_type>
void remove_duplicates(T& container)
{
	// Use DataType as data type for the chosen temporary data container
	T outContainer = container;
	auto ptr1 = outContainer.begin();
	auto end = --outContainer.end();
	auto ptr2 = end;
	while (ptr1 != --outContainer.end()){
		ptr2 = end;
		while (ptr2 != ptr1){
			if(*ptr1 == *ptr2){
				outContainer.erase(ptr2);
				end = --outContainer.end();
				ptr2 = end;
			}
			--ptr2;
			//std::cout << *(outContainer.begin()) << ", " <<*(--outContainer.end()) << std::endl;
			//printContainer(outContainer);
		}
		ptr1++;
	}
	container = outContainer;

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
	/*testFrontBackPairingFunctionality();
	std::cout << std::endl;*/
	testRemoveDuplicateFunctionality();
	std::cout << std::endl;
	/*testAddDifferenceFunctionality();*/

	return 0;
}
