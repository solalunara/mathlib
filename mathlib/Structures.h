#ifndef STRUCTURES_H
#define STRUCTURES_H
#pragma once

#include "Definitions.h"
#include <vector>
#include <string>
#include <functional>


typedef double float64;
class MATH_API Complex
{
public:
	Complex( float64 a, float64 b = 0, float64 c = 0, float64 d = 0 );

	float64 a;
	float64 b;
	float64 c;
	float64 d;

	std::string ToString();
};

MATH_API Complex operator +( Complex a );
MATH_API Complex operator -( Complex a );
MATH_API Complex operator +( Complex a, Complex b );
MATH_API Complex operator -( Complex a, Complex b );
MATH_API Complex operator *( Complex a, Complex b );
MATH_API Complex operator /( Complex a, Complex b );

MATH_API void operator +=( Complex &a, Complex b );
MATH_API void operator -=( Complex &a, Complex b );
MATH_API void operator *=( Complex &a, Complex b );
MATH_API void operator /=( Complex &a, Complex b );

MATH_API Complex operator "" i( long double d );
MATH_API Complex operator "" i( unsigned long long i );
MATH_API Complex operator "" j( long double d );
MATH_API Complex operator "" j( unsigned long long i );
MATH_API Complex operator "" k( long double d );
MATH_API Complex operator "" k( unsigned long long i );

class MATH_API Function
{
public:
	Function( std::function<Complex(Complex)> Data );

private:
	std::function<Complex(Complex)> Data;

public:
	Complex Derivative( Complex z, Complex dz = .1 + .1i + .1j + .1k );
	Function Derivative();

	Complex Integral( Complex b, Complex a, Complex dz = .1 );

	Complex Fourier( Complex w, float64 Infinity = INFINITY_DEFAULT );
	Function Fourier();
	Complex InverseFourier( Complex x, float64 Infinity = INFINITY_DEFAULT );
	Function InverseFourier();

	Function Convolution( Function &g, float64 Infinity = INFINITY_DEFAULT );

	Complex operator[]( Complex z )
	{
		return Data( z );
	}
};


#endif