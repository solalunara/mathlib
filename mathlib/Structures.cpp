#include "pch.h"
#include "Structures.h"

Complex::Complex( float64 a, float64 b /*= 0*/ ) : a(a), b(b)
{
}
std::string Complex::ToString()
{
	return std::to_string( a ) + " + " + std::to_string( b ) + "i";
}

Complex operator +( Complex a )
{
	return a;
}
Complex operator -( Complex a )
{
	return 0 - a;
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
	//quaternion multiplication
	//return Complex( a.a * b.a - a.b * b.b - a.c * b.c - a.d * b.d, 
	//				a.a * b.b + a.b * b.a + a.c * b.d - a.d * b.c,
	//				a.a * b.c - a.b * b.d + a.c * b.a + a.d * b.b,
	//				a.a * b.d + a.b * b.c - a.c * b.b + a.d * b.a );
	return Complex( a.a * b.a - a.b * b.b, a.b * b.a + a.a * b.b );
}
Complex operator /( Complex a, Complex b )
{
	Complex Inverse = Complex( b.a, -b.b ) * ( 1 / ( b.a * b.a + b.b * b.b ) );
	return a * Inverse;
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

Line::Line( std::function<Complex( float )> l ) : l( l )
{
}

//this needs to be down here, otherwise you won't be able to use 'i' above (it thinks it'll be the Complex(0,1) macro)
#include "Mathlib_Interface.h"

Function::Function( std::function<Complex(Complex)> Data ) : Data( Data )
{
}
Complex Function::Derivative( Complex z, Complex dz /*= .1 + .1i + .1j + .1k*/)
{
	return ( Data( z + dz ) - Data( z ) ) / dz;
}
Function Function::Derivative()
{
	return Function( [this]( Complex z ) { return Derivative( z ); } );
}
Complex Function::Integral( Line l, float b, float a, Complex C, float dz /*= .1*/ )
{
	Complex ret = C;
	for ( float z = b; z < a; z += dz )
	{
		ret += Data( l( z ) ) * ( l( z + dz ) - l( z ) );
	}
	return ret;
}
Complex Function::Fourier( Complex w, Complex C, float64 Infinity /*= INFINITY_DEFAULT*/ )
{
	return Function( [this, w, C]( Complex z ) { return Data( z ) * epow( -2 * pi * i * z * w ); } ).Integral( RealLine, -Infinity, Infinity, C );
}
Function Function::Fourier( Complex C )
{
	return Function( [this, C]( Complex z ) { return Fourier( z, C ); } );
}
Complex Function::InverseFourier( Complex x, Complex C, float64 Infinity /*= INFINITY_DEFAULT*/ )
{
	return Function( [this, x, C]( Complex z ) { return Data( z ) * epow( 2 * pi * i * z * x ); } ).Integral( RealLine, -Infinity, Infinity, C );
}
Function Function::InverseFourier( Complex C )
{
	return Function( [this, C]( Complex z ) { return InverseFourier( z, C ); } );
}
Function Function::Convolution( Function *g, Complex C, float64 Infinity /*= INFINITY_DEFAULT*/ )
{
	//see: https://en.wikipedia.org/wiki/Convolution#Definition
	return Function( [this, g, Infinity, C]( Complex t )
	{
		return Function( [this, g, t]( Complex ta )
		{
			return Data( ta ) * (*g)( t - ta );
		} ).Integral( RealLine, -Infinity, Infinity, C );
	} );
}