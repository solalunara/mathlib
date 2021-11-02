#include <iostream>
#include "Mathlib_Interface.h"


int main()
{
	/*
	Function *ZW;
	Function zx = ( ZW = new Function( []( Complex z ) 
	{ 
		return 1 / ( 2 * pi * i * z - 1 );
	} ) )->InverseFourier( 0 );
	Function xx = Function( []( Complex z )
	{
		return z;
	} );

	Function yx = xx.Convolution( &zx, 0 );

	std::cout << yx( 0 ).ToString() << std::endl;

	delete ZW;
	*/

	/*
	Function ZW = Function( []( Complex z )
	{
		return 1 / ( 2 * pi * i * z - 1 );
	} );

	Function *xx;
	Function XW = ( xx = new Function( []( Complex z )
	{
		return z;
	} ) )->Fourier( 0 );

	Function YW = Function( [&XW, &ZW]( Complex z )
	{
		return XW( z ) * ZW( z );
	} );

	Function yx = YW.InverseFourier( 0 );


	std::cout << yx( 0 ).ToString() << std::endl;

	delete xx;
	*/

	Function f = Function( []( Complex z )
	{
		return sin( z.a );
	} );
	Function F = f.Fourier( 0 );

	for ( float a = 0; a < 10; a += .1f )
	{
		std::cout << std::to_string( a ) + ": " << F( a ).ToString() << std::endl;
	}
}