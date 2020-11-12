#include <string>
#include <cctype>
#include <iostream>
#include <algorithm>

int main(int argc, char **args) {

	std::string line;
	std::getline(std::cin, line);

	line.erase( std::remove_if(line.begin(), line.end(),
		[](const char c) { return std::ispunct(c); } ), line.end() );

	std::cout << line << std::endl;
}
