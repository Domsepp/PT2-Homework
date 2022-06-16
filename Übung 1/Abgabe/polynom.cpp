#include <math.h>

#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

double polynom(double base, int n, vector<double> v) {
    double sum = 0;
    int i = 0;
    for (auto it = begin(v); it != end(v); ++it) {
        sum += *it * pow(base, i);
        i++;
    }

    return sum;
}

void prettyPrint(double decimal) {
    string d = to_string(decimal);
    int len = d.length();
    cout << d[3] << endl;
    int count = 0;
    for(int i = 0; i<len; i++){
        if(d[i] == '.'){
            count = i;
            break;
        }
    }
    int decpoints = count / 3;
    int printvar = 0;
    for(int i = count; i>0; i--){
        if(i%3 == 0){
            cout << ".";
        }
        cout << d[printvar];
        printvar ++;
    }
    cout << ",";
    for(int i = count+1; i<len;i++){
        cout << d[i];
    }
    /* if (decimal < 1000) {
        cout << decimal;
    } else {
        int i = 0;
        while ((decimal + 1) > pow(10, i)) {
            i++;
        }
        int next = 0;
        int count = (i - 1) / 3;
        cout << "count = " << count << endl;

        for (int a = 0; a < count;) {
            next = decimal / (pow(10, 3 * count));
            cout  << "next = " << next << ".";
            decimal -= next * pow(10, 3 * count);
            std::cout << "decimal = " << decimal << std::endl;
            count--;
        }
        std::cout << ((int)decimal) % (std::pow(10, (i % 3))) << std::endl;
        cout << decimal;
    }*/

}

int main(int argc, char* argv[]) {
    double x;
    double n;
    vector<double> v;
    try {
        x = stod(argv[1]);
        n = stod(argv[2]);
        for (int i = 3; i <= argc - 1; i++) {
            v.insert(v.end(), stod(argv[i]));
        }
    } catch (const exception& e) {
        cerr << /*e.what()*/ "You can only enter numbers." << '\n';
        return 0;
    }
    if (argc < 4) return 1;  // invalid number of parameters
    if (stoi(argv[argc - 1]) == 0) {
        cout << "Last Parameter can't be 0!";
        return 0;
    }
    if (stoi(argv[2]) != argc - 3) {
        cout << "You set n to " << stoi(argv[2]) << ", but provided "
                  << argc - 3 << " parameters.\n";
        return 0;
    }
    double result = polynom(x, n, v);
    cout << result << endl;
    prettyPrint(result);

    // ToDo: Exercise 2.a - read parameters and x, deal with invalid values

    // ToDo: Exercise 2.b - print P(x)
    // ToDo: Exercise 2.c - print P(x) with prettyPrint

    // std::cout << "6.543";

    return 0;
}