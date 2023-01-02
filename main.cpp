#include "vector.hpp"
#include <vector>
#include <iostream>

int main()
{
	std::vector<int> stdnum(6, 10);
	ft::vector<int> ftnum(6, 10);

	std::cout << "stdnum = ";

	// ranged loop
  	for (const int& i : stdnum) {
		std::cout << i << "  ";
	}

	std::cout << "my vector" << std::endl;
	std::cout<< "ftnum = ";

	// ranged loop
  	for (const int& i : ftnum) {
		std::cout << i << "  ";
	}


}