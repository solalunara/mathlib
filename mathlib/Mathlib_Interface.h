#ifndef INTERFACE_H
#define INTERFACE_H
#pragma once

#include "Structures.h"

#define e 2.7182818284590452353602874713526624977572470936999595749669676277
#define pi 3.1415926535897932384626433832795028841971693993751058209749445923
#define i Complex( 0, 1 )

MATH_API Complex epow( Complex z );
MATH_API Complex pow( float64 a, Complex b );
MATH_API Complex pow( Complex a, Complex b );


#endif