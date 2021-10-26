#include <iostream>
#include "Mathlib_Interface.h"


int main()
{
	Function f( []( Complex z ) 
	{ 
		return epow( 0-( z * z ) ) * sin( z.a );
	} );
	std::cout << f.Fourier( 1, 1000000 ).ToString() << std::endl;
}