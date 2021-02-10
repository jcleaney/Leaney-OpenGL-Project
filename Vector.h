// Filename: Vector.h
// Description: Class for 3D Vectors 
// Author: Scott McDermott
// Date Modified: 10/30/2017
//



#include "MathSettings.h"

#pragma once
#if !defined(_VECTOR_H_)
#define _VECTOR_H_

class Spherical;


class Vector
{
public:
	// Default constructor.
	Vector();
	// Copy constructor (from array).
	Vector(real const *pElements);
	// Simple constructor.
	Vector(real x, real y, real z);
	// Default destructor.
	~Vector();
	
	// Clear out the elements.
	inline void reset()	{aElements[X_AXIS]=0.0; aElements[Y_AXIS]=0.0; aElements[Z_AXIS]=0.0;}
	
	// Print the data using cout.
	void print();

	inline real x(void) const {return aElements[X_AXIS];}
	inline real y(void) const {return aElements[Y_AXIS];}
	inline real z(void) const {return aElements[Z_AXIS];}

	inline void x(real Value) {aElements[X_AXIS] = Value;}
	inline void y(real Value) {aElements[Y_AXIS] = Value;}
	inline void z(real Value) {aElements[Z_AXIS] = Value;}
	
	inline void set(real x, real y, real z) {aElements[X_AXIS] = x; aElements[Y_AXIS] = y; aElements[Z_AXIS] = z;}

	// Return an array of the elements.
	inline real* array() {return aElements;}

	// Return the length of the vector.
	real length() const;
	// Zero out any odd anomollies (like 0.00000000000004534 instead of just 0.0)
	void cleanVector();
	// Normalize the vector.
	Vector &normalize(void);

///////////////////////
// Overloaded Operators
	// Overloaded "Vector == Vector" operator (compare).
	bool operator==(Vector const &compare);

	// Overloaded "Vector += Vector" operator (combine).
	Vector &operator+=(Vector const &addend);

	// Overloaded "Vector += real" operator (move).
	Vector &operator+=(real const &addend);

	// Overloaded "Vector -= Vector" operator (combine).
	Vector &operator-=(Vector const &lessor);

	// Overloaded "Vector -= real" operator (move).
	Vector &operator-=(real const &lessor);

	// Overloaded "Vector *= real" operator (scale).
	Vector &operator*=(real const multiplier);

	// Overloaded "Vector /= real" operator (scale).
	Vector &operator/=(real const divisor);

	// Overloaded "Vector = float[]" operator (copy).
	Vector &operator=(float const vc[]);
	
	// Overloaded "Vector = Spherical" operator (convert).
	Vector &operator=(Spherical const sph);

protected:
	// The data elements [x, y, z]
	real aElements[3];
};
// Overloaded "Vector = Vector * Vector" operator (cross product).
Vector operator*(Vector const &Operand1, Vector const &Operand2);

// Overloaded "Vector = Vector + Vector" operator (combine).
Vector operator+(Vector const &Operand1, Vector const &Operand2);

typedef Vector Point;

// Calculate the dot product between two vectors.
real dotProduct(Vector const &Operand1, Vector const &Operand2);
// Calculate the cross product between two vectors.
Vector crossProduct(Vector const &Operand1, Vector const &Operand2);

// These all are globably used and MUST be set correctly here.
// UP, NORTH, and WEST must always be positive.
// All vectors are assumed to be unit length (just use axis).
// Correspond to the settings defined above

const Vector ORIGIN(	ORIGINARRAY	);
const Vector RIGHT(		RIGHTARRAY	);
const Vector LEFT(		LEFTARRAY	);
const Vector AHEAD(		AHEADARRAY	);
const Vector BACK(		BACKARRAY	);
const Vector UP(		UPARRAY		);
const Vector DOWN(		DOWNARRAY	);


#endif //_VECTOR_H_