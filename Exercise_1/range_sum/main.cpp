#include <iostream>

inline
int read_number() {
    int nmbr;
    std::cin >> nmbr;
    return nmbr;
}

int main(int argc, char **args) {

    int numberOne, numberTwo;

    std::cout << "This is 'Range Sum'!" << std::endl;
    std::cout << "Please enter the first of two numbers: ";

    std::cin >> numberOne;

    if( std::cin.good() ) {

        std::cout << "Great, now please enter the second number: ";

        std::cin >> numberTwo;

        if( std::cin.good() ) {

            if( numberOne < numberTwo ) {
                long sum = 0;
                for(int i = numberOne; i < numberTwo; ++i) {
                    sum += i;
                }
                std::cout << "Wonderful! Here is the result: " << sum << std::endl;
            } else {
                std::cout << "Unfortunately, we encountered that your second number is smaller than your first number." << std::endl;
            }
        } else {
            std::cout << "Unfortunately, we encountered an error in your second input!" << std::endl;
        }
    } else {
        std::cout << "Unfortunately, we encountered an error in your first input!" << std::endl;
    }
}