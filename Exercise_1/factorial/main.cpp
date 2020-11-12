#include "math.h"
#include <cmath>
#include <iostream>

double factorial(const int nmbr) {

	// if(nmbr == 0 || nmbr == 1) {
	// 	return 1.0;
	// }

	// const double euler = std::exp(1.0);

	// return sqrt(2.0 * M_PI * nmbr) * pow(nmbr / euler,  nmbr);

	double result = 1.0;
	for(int i = 1; i <= nmbr; ++i) {
		result = result * i;
	}

	return result;
}

int main(int argc, char **args) {

	int fac_nmbr;

	std::cout << "Hello, this is factorial!" << std::endl;
	std::cout << "Please enter your number: ";

	std::cin >> fac_nmbr;

	if( std::cin.good() ) {

		if( fac_nmbr < 0) {

			std::cout << "Unfortunately, we encountered an unexpected input." << std::endl;

		} else {
			const double fac = factorial(fac_nmbr);

			std::cout << "Estimated factorial: " << fac << std::endl;
		}

	} else {
		std::cout << "Unfortunately, we encountered an unexpected input." << std::endl;
	}
}
