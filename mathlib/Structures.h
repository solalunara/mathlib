#ifndef STRUCTURES_H
#define STRUCTURES_H
#pragma once

#ifdef MATHLIB_EXPORTS
#define MATH_API __declspec( dllexport )
#else
#define MATH_API __declspec( dllimport )
#endif

struct Vector
{
	
	float x;
	float y;
	float z;

	float &operator[]( const int i )
	{
		switch ( i )
		{
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return z;
			default:
				return -1;
		}
	}

	Vector operator +( const Vector &a, const Vector &b )
	{

	}
};

#endif