#ifndef STRUCTURES_H
#define STRUCTURES_H
#pragma once

#include "Definitions.h"
#include <vector>
#include <string>


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

	Vector operator +( Vector &a )
	{
		Vector r;
		for ( int i = 0; i < 3; ++i )
			r[ i ] = a[ i ] + ( *this )[ i ];
		return r;
	}
	Vector operator -( Vector &a )
	{
		Vector r;
		for ( int i = 0; i < 3; ++i )
			r[ i ] = a[ i ] - ( *this )[ i ];
		return r;
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

MATH_API Complex operator "" i( long double d );
MATH_API Complex operator "" i( unsigned long long i );


#endif