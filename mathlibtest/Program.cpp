#include <iostream>
#include "Mathlib_Interface.h"


int main()
{
	Function ZW = Function( []( Complex z ) 
	{ 
		return 1 / ( 2 * pi * i * z - 1 );
	} );
	Function zx = ZW.InverseFourier();
	Function xx = Function( []( Complex z )
	{
		return z;
	} );

	Function yx = xx.Convolution( zx );


	std::cout << yx[ 0 ].ToString() << std::endl;
}