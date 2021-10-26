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

void operator +=( Complex &a, Complex b )
{
	a = a + b;
}
void operator -=( Complex &a, Complex b )
{
	a = a - b;
}
void operator *=( Complex &a, Complex b )
{
	a = a * b;
}
void operator /=( Complex &a, Complex b )
{
	a = a / b;
}


Complex operator "" i( long double d )
{
	return Complex( 0, d );
}
Complex operator "" i( unsigned long long i )
{
	return Complex( 0, i );
}



Function::Function( std::function<Complex(Complex)> Data ) : Data( Data )
{
}
Complex Function::Derivative( Complex z, Complex dz /*= .1 + .1i*/)
{
	return ( Data( z + dz ) - Data( z ) ) / dz;
}
Function Function::Derivative()
{
	return Function( [this]( Complex z ) { return Derivative( z ); } );
}
Complex Function::Integral( Complex b, Complex a, Complex dz /*= .1*/ )
{
	Complex ret = 0;
	for ( Complex i = b; i.a <= a.a && i.b <= a.b; i += dz )
	{
		ret += dz * Data( i );
	}
	return ret;
}

//this needs to be down here, otherwise you won't be able to use 'i' above (it thinks it'll be the Complex(0,1) macro)
#include "Mathlib_Interface.h"
Complex Function::Fourier( Complex w, float Infinity /*= 100*/ )
{
	return Function( [this, w]( Complex z ) { return Data( z ) * epow( 2 * pi * i * z * w ); } ).Integral( -Infinity, Infinity );
}
Function Function::Fourier()
{
	return Function( [this]( Complex z ) { return Fourier( z ); } );
}