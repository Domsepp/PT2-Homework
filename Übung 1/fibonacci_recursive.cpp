#include <cstdlib>
#include <iostream>
#include <string>

int sum = 0;

int fibonacci(int number) {
    if (number < 1) {
        return 0;
    }
    sum++;
    if (number <= 2) {
        return 1;
    } else {
        return fibonacci(number - 1) + fibonacci(number - 2);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) return 1;  // invalid number of parameters

	int n = std::stoi(argv[1]);

    std::cout << n << " : " << fibonacci(n) << " : #" << sum << std::endl;

    return 0;
}
