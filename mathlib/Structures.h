#ifndef STRUCTURES_H
#define STRUCTURES_H
#pragma once

#include "Definitions.h"
#include <vector>


class MATH_API Vector
{
public:
	Vector();
	Vector( float x, float y, float z );

private:
	float x;
	float y;
	float z;

public:
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
			r[ i ] = a[ i ] + (*this)[ i ];
		return r;
	}
};

#endif