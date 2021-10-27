#include "pch.h"
#include "Mathlib_Interface.h"

Complex epow( Complex z )
{
	return pow( e, z.a ) * ( cos( z.b ) + sin( z.b ) * i );
}

Complex pow( float64 a, Complex b )
{
	return epow( log( a ) * b );
}

Complex pow( Complex a, Complex b )
{
	float64 r = sqrt( a.a * a.a + a.b * a.b );
	float64 t = atan( a.b / a.a );
	return epow( log( r ) * b + b * t * i );
}