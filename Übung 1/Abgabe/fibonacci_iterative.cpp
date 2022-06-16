#include <cstdlib>
#include <iostream>
#include <string>

int sum = 0;
int fibonacci(int number) {
    if (number < 1) {
        return 0;
    }
    if (number < 3) {
        return 1;
    }else{
		int lastfib = 1;
		int newfib = 1;
		for (int i = 3; i <= number; i++)
		{
			sum++;
			newfib += lastfib;
			lastfib = newfib - lastfib;
		}
		return newfib;
	}
}

int main(int argc, char* argv[]) {
    if (argc != 2) return 1;  // invalid number of parameters

    int n = std::stoi(argv[1]);
	
    std::cout << n << " : " << fibonacci(n) << " : #" << sum << std::endl;

    return 0;
}
