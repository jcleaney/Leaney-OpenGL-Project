// Filename: Spherical.h
// Description: Class for 3D Sphericals 
// Author: Scott McDermott
// Date Modified: 10/30/2017
//
// Data abstraction of the Spherical object. 
//  Stored in degrees.
//  Theta = 90 is pointing down the X axis
//  Theta = 0 is pointing back the Z axis (positive Z)
//  PHI = 0 is pointing on the XZ plane
//  PHI = 90 is pointing up the Y axis
//
//  Angles increase clockwise and vertically



#include "MathSettings.h"

#pragma once
#if !defined(_SPHERICAL_H_)
#define _SPHERICAL_H_

#include "Vector.h"


class Spherical
{
public:
	// Default constructor.
	Spherical();
	// Copy constructor (from array).
	Spherical(real const *pElements);
	// Simple constructor.
	Spherical(real Theta, real Phi, real Radius = 1.0);
	// Default destructor.
	~Spherical();

	// Clear out the elements.
	inline void reset()	{aElements[THETA]=0.0; aElements[PHI]=0.0; aElements[DIST]=1.0;}
	
	// Print the data using cout.
	void print();
	
	inline real T(void) const {return aElements[THETA];}
	inline real P(void) const {return aElements[PHI];}
	inline real D(void) const {return aElements[DIST];}

	inline void T(real Value) {aElements[THETA] = Value;}
	inline void P(real Value) {aElements[PHI] = Value;}
	inline void D(real Value) {aElements[DIST] = Value;}
	
	inline void set(real t, real p, real d) {aElements[THETA] = t; aElements[PHI] = p; aElements[DIST] = d;}
	
	// Perform the rotation in the graphics API based on this spherical.
	// Note, assume that the object is drawn facing straight down.
	void rotateGraphics( void );

	// Overloaded "Spherical += real" operator (Theta++). Add changes Theta
	inline Spherical &operator+=(real const addend)	{aElements[THETA] += addend; return *this;}
	// Overloaded "Spherical -= real" operator (Theta--). Subtract changes Theta
	inline Spherical &operator-=(real const lessor) {aElements[THETA] -= lessor; return *this;}
	// Overloaded "Spherical *= real" operator (Phi++). Multiply changes Phi
	inline Spherical &operator*=(real const multiplier) {aElements[PHI] += multiplier; return *this;}
	// Overloaded "Spherical /= real" operator (Phi--). Divide changes Phi
	inline Spherical &operator/=(real const divisor) {aElements[PHI] -= divisor; return *this;}

	// Overloaded "Spherical = vector" operator (convert).
	Spherical &operator=(Vector const &);

protected:
	// The data elements [THETA, PHI, DIST]
	real aElements[3];
};

// Overloaded "Spherical = Spherical + Spherical" operator (combine).
Spherical operator+(Spherical const &Operand1, Spherical const &Operand2);

// Overloaded "Spherical = Spherical - Spherical" operator (combine).
Spherical operator-(Spherical const &Operand1, Spherical const &Operand2);



#endif //_SPHERICAL_H_