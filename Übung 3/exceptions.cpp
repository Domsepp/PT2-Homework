#include <array>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>




// transforms a string to a date. Throws a logic_error if year is *not* between 1893 and 2018
std::tm stringToTime(const std::string& date)
{
	std::tm t{};
	std::istringstream ss(date);
	ss >> std::get_time(&t, "%Y%m%d");

	if (ss.fail() || t.tm_year < -7 || t.tm_year > 118)
	{
		throw std::logic_error("Year should be between 1893 and 2018    ");
	}

	return t;
}

class FormatException : public std::runtime_error
{
	// Inherits all constructors of std::runtime_error
	using std::runtime_error::runtime_error;
};

void writeOutFormatException(const FormatException& e)
{
	std::cout << "Exception: Wrong Format" << std::endl;
}


void parseLine(const std::string& line, size_t lineNum, int &num_errors, int &num_inval_lines)
{
	const std::array<std::string, 4> fieldNames = { "Date", "Temperature", "Rainfall", "Unknown field" };

	std::string date = line.substr(0,8);																		// Hier splitte ich erstmal den übergebenen String auf
	std::string hum = line.substr(9,line.length());
	std::string temp = "";
	std::ofstream log_file;
	log_file.open("error_log.log",std::fstream::app);															// Öffnen der log-Datei ohne sie zu überschreiben

	bool error = false;

	std::tm Date_val;

	float rainfall;
	float temperature; 

	bool is_exception = false;

	try{																										// Konvertierung des Datums
		Date_val = stringToTime(date);
	}
	catch(const std::logic_error& e){
		std::cerr << e.what() << "   in line   " << lineNum << std::endl;
		log_file << lineNum << " " << date << " " << e.what() << " " << std::endl;
		is_exception = true;
		num_errors ++;
	}

	while(hum != ""){																							// verbleibender String wird nun bei ; aufgesplittet
		if(hum[0] == ';'){
			hum.erase(0,1);
			break;
		}
		temp.push_back(hum[0]);																					// temp und hum halten jeweil Tempreatur und Niederschlag
		hum.erase(0,1);
	}

	try{																										// Umwandlung des Niederschlages und Abfangen der Exception (Das gleich wird nochmal für Temp gemacht)
		rainfall = std::stof(hum);
	}
	catch(const std::exception& ex){
		log_file << lineNum << " " << hum << " " << ex.what() << " " << std::endl;
		is_exception = true;
		num_errors ++;																							// custom-Exception die an die aufrufende Funktion "geworfen" wird
	}
	try{																										// Muss extra abgefangen werden, da Werte separat in log-Datei stehen sollen
		temperature = std::stof(temp);
	}
	catch(const std::exception& ex){
		log_file << lineNum << " " << temp << " " << ex.what() << " " << std::endl;
		is_exception = true;
		num_errors ++;
	}

	if(is_exception == true){
		num_inval_lines++;
		throw FormatException("Wrong Format");
	}
	log_file.close();

	//std::cout << "Temp: " << temperature << "  Rain: " << rainfall << std::endl;
	// TODO 3.1b: parse a given line, check dates by calling stringToTime, check temperature/rainfall by
	// calling std::stof. Catch all exceptions thrown by these methods. If there have been any exceptions,
	// aggregate all necessary information into an instance of FormatException and throw that instance.
}

// TODO 3.1d

void checkData(std::string fileName)
{
	std::ifstream file;
	std::string s = "";
	int linenumber = 0;

	int num_of_inval_lines = 0;

	std::ofstream log_file;
	log_file.open("error_log.log",std::fstream::app);																	// Log-Datei muss in jeder Funktion, die sie benutzt separat geöffnet werden

	int num_exceptions = 0;
	try{
		file.open(fileName, std::ios::in);
		while(getline(file, s, '\n'))
		{
			if(linenumber == 0) {
				linenumber++;
				continue;
			}	
			try{
				parseLine(s,linenumber+1,num_exceptions,num_of_inval_lines);
				//std::cout << s << std::endl; 
				
			}
			catch(FormatException &ex){
				writeOutFormatException(ex);
			}
			linenumber++;
		}
		file.close();
	}
	catch (std::ifstream::failure e){																					// Fängt Fehler beim Öffnen der csv-Datei ab
		std::cerr << "Exception opening/reading/closing file\n";
		num_of_inval_lines++;
		num_exceptions ++;
	}

	std::cout << "Number of exceptions: " << num_exceptions << std::endl;    
	std::cout << "Number of invalid lines: " << num_of_inval_lines << std::endl;  
	std::cout << "Number of valid lines: " << ((linenumber-1)-num_of_inval_lines) << std::endl;  
	log_file.close();
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
