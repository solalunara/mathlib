#include "pch.h"
#include "Structures.h"

Vector::Vector() : x( 0 ), y( 0 ), z( 0 )
{
}
Vector::Vector( float x, float y, float z ) : x( x ), y( y ), z( z )
{
}

Complex::Complex( float a, float b /*= 0*/ ) : a( a ), b( b )
{
}
std::string Complex::ToString()
{
	return ( std::to_string( a ) + " + " + std::to_string( b ) + "i" );
}


Complex operator +( Complex a, Complex b )
{
	return Complex( a.a + b.a, a.b + b.b );
}
Complex operator -( Complex a, Complex b )
{
	return Complex( a.a - b.a, a.b - b.b );
}
Complex operator *( Complex a, Complex b )
{
	return Complex( a.a * b.a - a.b * b.b, a.b * b.a + a.a * b.b );
}
Complex operator /( Complex a, Complex b )
{
	return Complex( ( a.a * b.a + a.b * b.b ) / ( b.a * b.a + b.b * b.b ), ( a.b * b.a - a.a * b.b ) / ( b.a * b.a + b.b * b.b ) );
}


Complex operator "" i( long double d )
{
	return Complex( 0, d );
}
Complex operator "" i( unsigned long long i )
{
	return Complex( 0, i );
}