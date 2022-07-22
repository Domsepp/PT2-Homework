#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

constexpr int64_t prime = 293; // Prime close to the magnitude of the alphabet
constexpr int64_t hashTableMagnitude = 1000000009;

int64_t nextHash(int64_t hash, int64_t primePow, char leavingChar, char enteringChar) {
	// TODO: Compute next rolling hash based on previous hash, primePow, the
	//       character "leaving" the search window and the character
	//       "entering" the search window.
	// std::cout << "hash = " << hash /*<< ", primePow = " << primePow << ", leavingChar = " << (int)leavingChar << ", enteringChar = " << (int)enteringChar*/;
	hash = (((hash - (leavingChar * primePow) % hashTableMagnitude) * prime) % hashTableMagnitude + enteringChar) % hashTableMagnitude;
	if(hash<0) hash += hashTableMagnitude;
	// std::cout << ", leavinghash = " << hash << std::endl;

	return hash;
}

std::vector<size_t> search(const std::string& pattern, const std::string& text) {
	int i;
	int j;

	const size_t patternLength = pattern.length();
	const size_t textLength = text.length();

	if (textLength < patternLength) {
		return {};
	}

	// TODO: Compute primePow = prime ^ patternLength (modulo hashTableMagnitude).
	//       keep in mind to apply modulo after each operation.
	//       Hint: you can't simply use std::pow because of that.
	int64_t primePow = 1;
	for (size_t i = 1; i < patternLength; i++) {
		primePow = (primePow * prime) % hashTableMagnitude;
	}
	

	// TODO: Compute patternHash, the hash value of the pattern and the first
	//       substringHash.
	std::vector<size_t> positions;

	int64_t patternHash = pattern[0];
	int64_t substringHash = text[0];
	for (size_t i = 1; i < patternLength; i++) {
		patternHash = ((patternHash * prime) + pattern[i]) % hashTableMagnitude;
		substringHash = ((substringHash * prime) + text[i]) % hashTableMagnitude;
	}
	/*if (patternHash == substringHash) {
		positions.push_back(0);
	}*/
	//std::cout << "patternHash = " << patternHash << ", substringHash = " << substringHash << std::endl;

	for(i = 0; i <= textLength - patternLength; i++){
		if(patternHash == substringHash){
			//std::cout << "hashes are the same" << std::endl;
			for(j = 0; j < patternLength; j++){
				if(text[i+j] != pattern[j]){
					break;
				}
			}
			if(j == patternLength){
				std::cout << "Pattern found at: " << i << std::endl;
			}
		}
		if(i < textLength - patternLength){
			substringHash = nextHash(substringHash, primePow, text[i], text[i + patternLength]);
			if (patternHash == substringHash) {
				//std::cout << "patternHash = " << patternHash << ", substringHash = " << substringHash << std::endl;
				positions.push_back(i);
			}
			
			//std::cout << substringHash << std::endl;
		}
	}
	
	/*for (size_t i = patternLength + 1; i < textLength; i++) {
		substringHash = nextHash(substringHash, primePow, text[i-patternLength], text[i]);
		if (patternHash == substringHash) {
			positions.push_back(i-patternLength);
		}
		
	}*/
	
	// TODO: Compare each individual substring's hash with patternHash and push
	//       all found occurrences to the positions vector.
	//       Compute the next substringHash if needed.
	// std::vector<size_t> positions;


	return positions;
}

std::vector<std::string> loadTexts(const std::string& filepath) {
	std::ifstream file;
	file.exceptions(std::ifstream::failbit);
	try {
		file.open(filepath);
	} catch (const std::ifstream::failure& e) {
		std::cerr << R"(Could not open file (")" << filepath << R"("): )" << std::strerror(errno)
				  << std::endl;
		return {};
	}
	file.exceptions(std::ifstream::goodbit);

	std::string line;
	std::vector<std::string> lines;
	while (std::getline(file, line)) {
		lines.push_back(line);
	}
	return lines;
}

int main() {
	const auto texts = loadTexts("loremipsum.txt");
	const std::string pattern = "ipsum";

	std::cout << R"(Searching for ")" << pattern << R"(")" << '\n';

	std::cout << "Found at positions:\n";
	size_t counter = 0;
	for (size_t lineNumber = 0; lineNumber < texts.size(); ++lineNumber) {
		for (size_t linePos : search(pattern, texts[lineNumber])) {
			std::cout << "  " << lineNumber << ", " << linePos << '\n'; // should better output linenumber+1
			counter++;
		}
	}
	std::cout << '\n';
	std::cout << "Number of occurences: " << counter << '\n'; // Expected occurences of "ipsum": 57
	return 0;
}
