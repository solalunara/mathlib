#include <iostream>
#include <string>
#include "Mathlib_Interface.h"



int main()
{
	Complex c = pow( 8 + 5i, 3 - 2i );
	std::cout << c.ToString() << std::endl;
}