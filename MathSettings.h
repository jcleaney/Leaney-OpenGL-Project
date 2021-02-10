// Filename: MathSettings.h
// Description: This file contains all of the necessary defines for all math. 
// Author: Scott McDermott
// Date Modified: 11/3/2017
//
// All math files must include this eventually.
//





#ifndef _MATH_SETTINGS_H_
#define _MATH_SETTINGS_H_
//#pragma once

// explicit dependencies
#include <math.h>       // for sqrt
#include <assert.h>
//#pragma warning (disable:4244)      // int to float conversion
#include <float.h>      // for min/max






/////////////////////////
// Type definitions... //
/////////////////////////

//class Quad;
//class Color;
class Vector;
class Spherical;
//class Matrix;

/////////////////////////////////////////
// Fundamentals of the math objects... //
/////////////////////////////////////////


// real type
typedef float real;


real const REAL_MAX = FLT_MAX;
real const REAL_MIN = FLT_MIN;


real const PI = real( 3.14159265358979323846 );
real const PIunder360 = real( 114.59155902616464175369272868838 );
real const Epsilon = real( 0.00001 );

////////////////////
// Math basics... //
////////////////////

#ifndef SQRT_OF_TWO
#define SQRT_OF_TWO	1.414213562373
#endif

#ifndef TWO_PI
#define TWO_PI      2.0*PI
#endif

#ifndef HALF_PI
#define HALF_PI     0.5*PI
#endif

#ifndef QUARTER_PI
#define QUARTER_PI	0.25*PI
#endif

#ifndef ONE_DEGREE
#define ONE_DEGREE	(1.0/180.0)*PI
#endif

#ifndef ANGLE_EPSILON
#define	ANGLE_EPSILON		ONE_DEGREE*0.05
#endif

#ifndef DEGREES_TO_RADIANS
#define DEGREES_TO_RADIANS  PI/180.0
#endif

#ifndef RADIANS_TO_DEGREES
#define RADIANS_TO_DEGREES  180.0/PI
#endif

#ifndef POS_INFINITY
#define POS_INFINITY        3.0E+37
#endif

#ifndef NEG_INFINITY
#define NEG_INFINITY       -3.0E+37
#endif

#ifndef char_PTR
typedef char * char_PTR;
#endif

#ifndef int_PTR
typedef int * int_PTR;
#endif

#ifndef long_PTR
typedef long * long_PTR;
#endif

#ifndef UByte
typedef unsigned char UByte;
#endif

#ifndef UByte_PTR
typedef UByte * UByte_PTR;
#endif

#ifndef UInt
typedef unsigned int UInt;
#endif

#ifndef UInt_PTR
typedef UInt * UInt_PTR;
#endif

// Macro to convert from degrees to radians.
#ifndef RAD
#define RAD(x) (((x)*PI)/180.0)
#endif

// Macro to convert from radians to degrees.
#ifndef DEG
#define DEG(x) (((x)*180.0)/PI)
#endif

// Note: ABS does not work correctly with unsigned integer values.
#define ABS(A)  (((A) < 0) ? -(A) : (A))
#define IMAX(A,B) ((A) > (B) ? (0) : (1))

///////////////////////////////////////////
// Indexes for internal array objects... //
///////////////////////////////////////////

// for RGBA Color arrays (use quad class)
#define	RED_INDEX				0
#define	GREEN_INDEX				1
#define	BLUE_INDEX				2
#define	ALPHA_INDEX				3


// for XYZW Cartesian vectors
#define X_AXIS                  0
#define Y_AXIS                  1
#define Z_AXIS                  2
#define W_AXIS                  3


#define	REDV		0.8, 0.0, 0.0, 0.0
#define GREENV		0.0, 0.8, 0.0, 0.0
#define BLUEV		0.0, 0.0, 0.8, 0.0
#define BROWNV		0.6, 0.3, 0.0, 0.0
#define PURPLEV		0.8, 0.0, 0.8, 0.0
#define CYANV		0.0, 0.8, 0.8, 0.0
#define WHITEV		0.8, 0.8, 0.8, 0.0
#define BLACKV		0.0, 0.0, 0.0, 0.0

#define	ORIGINV	 0.0,  0.0,  0.0
#define RIGHTV	 1.0,  0.0,  0.0
#define LEFTV	-1.0,  0.0,  0.0
#define AHEADV	 0.0,  0.0, -1.0
#define BACKV	 0.0,  0.0,  1.0
#define UPV		 0.0,  1.0,  0.0
#define DOWNV	 0.0, -1.0,  0.0


const real ORIGINARRAY[3] = {ORIGINV};
const real RIGHTARRAY[3] =	{RIGHTV	};
const real LEFTARRAY[3] =	{LEFTV	};
const real AHEADARRAY[3] =	{AHEADV	};
const real BACKARRAY[3] =	{BACKV	};
const real UPARRAY[3] =		{UPV	};
const real DOWNARRAY[3] =	{DOWNV	};



// for Spherical coordinates stored in vectors's
// (distance, theta, phi)
// distance >= 0.0
// 0 <= theta < 2PI
// 0 <= phi < PI

#define SPH_THETA               0
#define SPH_PHI                 1
#define SPH_DIST                2
#define THETA		            SPH_THETA
#define PHI						SPH_PHI
#define DIST					SPH_DIST





#endif // #ifndef _MATH_SETTINGS_H_
