#ifndef DEFINITIONS_H
#define DEFINITIONS_H
#pragma once

#ifdef MATHLIB_EXPORTS
#define MATH_API __declspec( dllexport )
#else
#define MATH_API __declspec( dllimport )
#endif

#define INFINITY_DEFAULT 100

#endif