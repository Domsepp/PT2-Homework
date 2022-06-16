#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

using namespace std;

int modulo(const string& a, int b) {
    int c = stoi(a);
    cout << c << endl;
    return -1;
}

bool isCheckDigitCorrect(const string& testString) { return true; }

bool isValueCorrect(const string& teststring, const int& column) {
    regex regExp;
    string iban;

    switch (column) {
        case 0:
        // same as case 1
        case 1:
            // test, if first letter is 'A'<=letter<='Z'
            // while there is another letter != 0, if 'a'<=letter<='z'
            // counter++; else return false;

            break;
        case 2:
            // transform
            int pt = 4;
            while (teststring[pt]) {
                iban.push_back(teststring[pt]);
            }
            // DE36 (Bsp) to end
            if (teststring[0] >= 'A' && teststring[0] <= 'Z') {
                int i = atoi(teststring.replace(0,1,"1"));
            }

            // validate (pt is reused)
            pt = 0;
            int result = 0;
            int i = 0;
            while (iban[pt]) {
                if (iban[pt] > '9' || iban[pt] < '0') {
                    return false;
                } else {
                    if (i < 9) {
                        result = 10 * result + iban[pt];
                        i++;
                    } else {
                        result = result % 97;
                        i = 2;
                    }
                }
            }
            result = result % 97;

            // IBAN
            /*IBAN:		            GB82 WEST 1234 5698 7654 32
            Rearrange:		        W E S T12345698765432 G B82
            Convert to integer:		3214282912345698765432161182
            Compute remainder:		3214282912345698765432161182	mod 97 =
            1*/
            /*Piece-wise calculation D mod 97 can be done in many ways. One such
way is as follows:

Starting from the leftmost digit of D, construct a number using the first 9
digits and call it N. Calculate N mod 97. Construct a new 9-digit N by
concatenating the above result (step 2) with the next 7 digits of D. If there
are fewer than 7 digits remaining in D but at least one, then construct a new N,
which will have less than 9 digits, from the above result (step 2) followed by
the remaining digits of D Repeat steps 2–3 until all the digits of D have been
processed The result of the final calculation in step 2 will be D mod 97 = N
mod 97.*/
        default:
            return false;
    }

    return regex_match(teststring, regExp);
}

void readTokensAndLines(char* path) {
    ifstream file(path);
    string parsed;
    string line;

    while (getline(file, line)) {
        istringstream linestream;
        linestream.str(line);

        // TODO: - Split line and write result to std::cout
        //       - Check each part of line with isValueCorrect and log if values
        //       are not supported
        //       - Use and extend isValueCorrect and isCheckDigitCorrect
        //       function for this
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "not enough arguments - USAGE: fileio [DATASET]\n";
        return -1;  // invalid number of parameters
    }

    cout << "Given path to persons.dat: " << argv[1] << "\n";

    readTokensAndLines(argv[1]);
    cout << modulo("4152523526252528027853958240132131", 97)
         << "\n";  // expected result is 42

    return 0;
}
