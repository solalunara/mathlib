#include "pch.h"
#include "Structures.h"

Complex::Complex( float64 a, float64 b /*= 0*/, float64 c /*= 0*/, float64 d /*= 0*/ ) : a(a), b(b), c(c), d(d)
{
}
std::string Complex::ToString()
{
	return std::to_string( a ) + " + " + std::to_string( b ) + "i + "  + std::to_string( c ) + "j + " + std::to_string( d ) + "k";
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
	return Complex( a.a + b.a, a.b + b.b, a.c + b.c, a.d + b.d );
}
Complex operator -( Complex a, Complex b )
{
	return Complex( a.a - b.a, a.b - b.b, a.c - b.c, a.d - b.d );
}
Complex operator *( Complex a, Complex b )
{
	return Complex( a.a * b.a - a.b * b.b - a.c * b.c - a.d * b.d, 
					a.a * b.b + a.b * b.a + a.c * b.d - a.d * b.c,
					a.a * b.c - a.b * b.d + a.c * b.a + a.d * b.b,
					a.a * b.d + a.b * b.c - a.c * b.b + a.d * b.a );
}
Complex operator /( Complex a, Complex b )
{
	Complex Inverse = Complex( b.a, -b.b, -b.c, -b.d ) * ( 1 / ( b.a * b.a + b.b * b.b + b.c * b.c + b.d * b.d ) );
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
Complex operator "" j( long double d )
{
	return Complex( 0, 0, d );
}
Complex operator "" j( unsigned long long i )
{
	return Complex( 0, 0, i );
}
Complex operator "" k( long double d )
{
	return Complex( 0, 0, 0, d );
}
Complex operator "" k( unsigned long long i )
{
	return Complex( 0, 0, 0, i );
}


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
Complex Function::Fourier( Complex w, float64 Infinity /*= INFINITY_DEFAULT*/ )
{
	return Function( [this, w]( Complex z ) { return Data( z ) * epow( -2 * pi * i * z * w ); } ).Integral( -Infinity, Infinity );
}
Function Function::Fourier()
{
	return Function( [this]( Complex z ) { return Fourier( z ); } );
}
Complex Function::InverseFourier( Complex x, float64 Infinity /*= INFINITY_DEFAULT*/ )
{
	return Function( [this, x]( Complex z ) { return Data( z ) * epow( 2 * pi * i * z * x ); } ).Integral( -Infinity, Infinity );
}
Function Function::InverseFourier()
{
	return Function( [this]( Complex z ) { return InverseFourier( z ); } );
}
Function Function::Convolution( Function *g, float64 Infinity /*= INFINITY_DEFAULT*/ )
{
	//see: https://en.wikipedia.org/wiki/Convolution#Definition
	return Function( [this, g, Infinity]( Complex t )
	{
		return Function( [this, g, t]( Complex ta )
		{
			return Data( ta ) * (*g)[ t - ta ];
		} ).Integral( -Infinity, Infinity );
	} );
}