#include <array>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// transforms a string to a date. Throws a logic_error if year is *not* between 1893 and 2018
std::tm stringToTime(const std::string& date)
{
	std::tm t{};
	std::istringstream ss(date);
	ss >> std::get_time(&t, "%Y%m%d");

	if (ss.fail() || t.tm_year < -7 || t.tm_year > 118)
	{
		throw std::logic_error("Year should be between 1893 and 2018");
	}

	return t;
}

class FormatException : public std::runtime_error
{
	// Inherits all constructors of std::runtime_error
	using std::runtime_error::runtime_error;
};

void parseLine(const std::string& line, size_t lineNum)
{
	const std::array<std::string, 4> fieldNames = { "Date", "Temperature", "Rainfall", "Unknown field" };

	// TODO 3.1b: parse a given line, check dates by calling stringToTime, check temperature/rainfall by
	// calling std::stof. Catch all exceptions thrown by these methods. If there have been any exceptions,
	// aggregate all necessary information into an instance of FormatException and throw that instance.
}

// TODO 3.1d
void writeOutFormatException(const FormatException& e)
{}

void checkData(const std::string& path)
{
	std::ifstream file;

	// TODO 3.1a: open file + read each line + call parseLine function (catch ifstream::failure)
	// TODO 3.1c: read each line + call parseLine function (catch FormatException) + count valid + invalid
	//            lines
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid number of arguments - USAGE: exceptions [DATASET]" << std::endl;
		return -1;
	}

	checkData(argv[1]);

	return 0;
}
