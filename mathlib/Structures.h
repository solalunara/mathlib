#ifndef STRUCTURES_H
#define STRUCTURES_H
#pragma once

#include "Definitions.h"
#include <vector>
#include <string>
#include <functional>


class MATH_API Vector
{
public:
	Vector();
	Vector( float x, float y, float z );

	float x;
	float y;
	float z;

	float &operator[]( int i )
	{
		switch ( i )
		{
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return z;
		}
	}

};


class MATH_API Complex
{
public:
	Complex( float a, float b = 0 );

	float a;
	float b;


	std::string ToString();
};

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

class MATH_API Function
{
public:
	Function( std::function<Complex(Complex)> Data );

private:
	std::function<Complex(Complex)> Data;

public:
	Complex Derivative( Complex z, Complex dz = .1 + .1i );
	Function Derivative();

	Complex Integral( Complex b, Complex a, Complex dz = .1 );

	Complex Fourier( Complex w, float Infinity = 100 );
	Function Fourier();


	Complex operator[]( Complex z )
	{
		return Data( z );
	}
};


#endif