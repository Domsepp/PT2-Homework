#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

int modulo(const std::string& a, int b) {
    int res = 0;
 
    // One by one process all digits of 'num'
    for (int i = 0; i < a.length(); i++)
        res = (res * 10 + (int)a[i] - '0') % b;
 
    return res;

    /*
        Die Zahl ist in dem Fall so groß, dass man sie nicht einfach in ein Zahlenformat umwandeln kann. Daher muss mann den Modulo über ein komplexeres Verfahren berechnen und kann nicht 
        einfach den %-Operator nutzen.
    */

}

bool isCheckDigitCorrect(const std::string& testString) {
    std::string iban;

    int x = static_cast<unsigned char>(testString[0]);
    x = x - 55;
    iban.append(std::to_string(x));
    x = static_cast<unsigned char>(testString[1]);
    x = x - 55;
    iban.append(std::to_string(x));
    iban.append(testString.substr(2, 2));

    int pt = 4;

    while (testString[pt]) {
        iban.push_back(testString[pt]);
        pt++;
    }
    if (modulo(iban,100) == 1) {
        return true;
    }
    return false;
}

bool isValueCorrect(const std::string& teststring, const int& column) {
    std::regex regExp("[A-Z][a-z]{1,14}");
    std::regex IBAN("[A-Z]{2}[0-9]{16,32}");

    switch (column) {
        // TODO: implement cases for other columns
        case 0:
        case 1:
            if (std::regex_match(teststring, regExp)) {
                std::cout << "Matched" << std::endl;
            } else {
                return false;
            }
            break;
        case 2:
            if (std::regex_match(teststring, IBAN)) {
                std::cout << "Matched IBAN" << std::endl;
            } else {
                return false;
            }
            break;
        default:
            return false;
    }

    return true;
}

void readTokensAndLines(char* path) {
    std::ifstream file(path);
    std::string parsed;
    std::string line;

    std::string delimiter = ",";
    std::string split;
    size_t pos = 0;

    std::string fehler;
    bool fehlerErkannt = false;

    std::ofstream file2("fileio.log");
    file2.clear();

    std::vector<std::string> splitString;

    while (std::getline(file, line)) {
        std::istringstream linestream;
        linestream.str(line);

        while (
            (pos = line.find(delimiter)) !=
            std::string::npos) {  // teilt den String anhand des "delimiter" auf
            split = line.substr(0, pos);
            line.erase(0, pos + delimiter.length());
            splitString.push_back(split);
        }
        splitString.push_back(line);

        std::cout << splitString[0] << " " << splitString[1] << " -";

        for (std::string::size_type i = 0; i < splitString[2].size();
             i++) {  // gibt IBAN formattiert aus
            if (i % 4 == 0) {
                std::cout << " ";
            }
            std::cout << splitString[2][i];
        }
        std::cout << std::endl;

        for (int i = 0; i < 3; i++) {
            if (!(isValueCorrect(splitString[i], i))) {
                fehlerErkannt = true;
                switch (i) {
                    case 0:
                        fehler.append(" Vorname inkorrekt ");
                        break;
                    case 1:
                        fehler.append(" Nachname inkorrekt ");
                        break;
                    case 2:
                        fehler.append(" IBAN inkorrekt ");
                        break;
                    default:
                        break;
                }
            }
        }

        if (fehlerErkannt) {
            file2 << "Fehler in der Zeile: " << splitString[0] << " "
                  << splitString[1] << " - " << splitString[2] << ": \t"
                  << fehler << std::endl;
        } else {
            std::cout << isCheckDigitCorrect(splitString[2]) << std::endl;
            std::cout << "Aufgerufen" << std::endl;
        }
        fehler = "";
        fehlerErkannt = false;
        splitString.clear();

        // TODO: - Split line and write result to std::cout
        //       - Check each part of line with isValueCorrect and log if values
        //       are not supported
        //       - Use and extend isValueCorrect and isCheckDigitCorrect
        //       function for this
    }
    file2.close();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "not enough arguments - USAGE: fileio [DATASET]\n";
        return -1;  // invalid number of parameters
    }

    std::cout << "Given path to persons.dat: " << argv[1] << "\n";

    readTokensAndLines(argv[1]);
    std::cout << modulo("4152523526252528027853958240132131", 97)
              << "\n";  // expected result is 42

    return 0;
}
