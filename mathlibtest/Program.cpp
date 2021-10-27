#include <iostream>
#include "Mathlib_Interface.h"


int main()
{
	/*
	Function *ZW;
	Function zx = ( ZW = new Function( []( Complex z ) 
	{ 
		return 1 / ( 2 * pi * i * z - 1 );
	} ) )->InverseFourier();
	Function xx = Function( []( Complex z )
	{
		return z;
	} );

	Function yx = xx.Convolution( &zx );

	std::cout << yx[ 1 ].ToString() << std::endl;

	delete ZW;
	*/

	///*
	Function ZW = Function( []( Complex z )
	{
		return 1 / ( 2 * pi * i * z - 1 );
	} );

	Function *xx;
	Function XW = ( xx = new Function( []( Complex z )
	{
		return z;
	} ) )->Fourier();

	Function YW = Function( [&XW, &ZW]( Complex z )
	{
		return XW[ z ] * ZW[ z ];
	} );

	Function yx = YW.InverseFourier();

	std::cout << yx[ 4.3996 ].ToString() << std::endl;

	delete xx;
	//*/
}