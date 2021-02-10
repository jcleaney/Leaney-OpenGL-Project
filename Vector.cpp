// Filename: Vector.cpp
// Description: See header file for structural information  
// Author: Scott McDermott
// Date Modified: 10/30/2017
//


#include "Vector.h"
#include "Spherical.h"
 
#include <iostream>
using namespace std;

Vector::Vector()
{
	reset();
}

Vector::Vector(real const *pElements)
{
	assert(pElements);
	this->aElements[X_AXIS] = pElements[X_AXIS];
	this->aElements[Y_AXIS] = pElements[Y_AXIS];
	this->aElements[Z_AXIS] = pElements[Z_AXIS];
}

Vector::Vector(real x, real y, real z)
{
	this->aElements[X_AXIS] = z;
	this->aElements[Y_AXIS] = y;
	this->aElements[Z_AXIS] = z;
}

Vector::~Vector()
{
}

void Vector::print()
{
	cout << "X=" << aElements[X_AXIS] << ", Y=" << aElements[Y_AXIS] << ", Z=" << aElements[Z_AXIS] << endl;
}

real Vector::length(void) const
{
	return sqrt(x()*x() + y()*y() + z()*z());
}

Vector& Vector::normalize(void)
{
	real myLength = this->length();
	if (myLength != 0)
	{
		this->x(this->x() / myLength);
		this->y(this->y() / myLength);
		this->z(this->z() / myLength);
	}
	this->cleanVector();
	return(*this);
}

void Vector::cleanVector()
{
	for (int i=0; i<3; i++)
	{
		if (aElements[i] == -0.0) aElements[i] = 0.0;
		else if (aElements[i] == 0.0) ;
		else if (aElements[i] <  0.00001 && aElements[i] > -0.00001) aElements[i] = 0.0;
		else if (aElements[i] >  0.99999 && aElements[i] <  1.00001) aElements[i] = 1.0;
		else if (aElements[i] < -0.99999 && aElements[i] > -1.00001) aElements[i] = -1.0;
	}
}

bool Vector::operator==(Vector const &compare)
{
	if(this->x() == compare.x() && this->y() == compare.y() && this->z() == compare.z())
		return true;
	return false;
}

Vector &Vector::operator+=(Vector const &addvec)
{
	this->x(this->x() + addvec.x());
	this->y(this->y() + addvec.y());
	this->z(this->z() + addvec.z());
	this->cleanVector();
	return(*this);
}

Vector &Vector::operator+=(real const &addend)
{
	this->x(this->x() + addend);
	this->y(this->y() + addend);
	this->z(this->z() + addend);
	this->cleanVector();
	return(*this);
}

Vector &Vector::operator-=(Vector const &lessor)
{
	this->x(this->x() - lessor.x());
	this->y(this->y() - lessor.y());
	this->z(this->z() - lessor.z());
	this->cleanVector();
	return(*this);
}

Vector &Vector::operator-=(real const &lessor)
{
	this->x(this->x() - lessor);
	this->y(this->y() - lessor);
	this->z(this->z() - lessor);
	this->cleanVector();
	return(*this);
}

Vector &Vector::operator*=(real const multiplier)
{
//	cout << "m=" << multiplier << endl;
	this->x(this->x() * multiplier);
	this->y(this->y() * multiplier);
	this->z(this->z() * multiplier);
	this->cleanVector();
	return(*this);
}

Vector &Vector::operator/=(real const divisor)
{
	if(divisor == 0)
	{
		this->reset();
		return(*this);
	}
	this->x(this->x() / divisor);
	this->y(this->y() / divisor);
	this->z(this->z() / divisor);
	this->cleanVector();
	return(*this);
}

Vector &Vector::operator=(float const vc[])
{
	this->x(vc[X_AXIS]);
	this->y(vc[Y_AXIS]);
	this->z(vc[Z_AXIS]);
	this->cleanVector();
	return(*this);
}

Vector &Vector::operator=(Spherical const sph)
{		// Convert Vector to Shperical
	double r;
	r = sph.D() * cos(sph.P() * DEGREES_TO_RADIANS);

	// Laid down projections
	this->x(r * sin(sph.T() * DEGREES_TO_RADIANS));
	this->z(r * cos(sph.T() * DEGREES_TO_RADIANS));
	this->y(sph.D() * sin(sph.P() * DEGREES_TO_RADIANS));

	this->cleanVector();
	return *this;
}

Vector operator*(Vector const &Operand1, Vector const &Operand2)
{
	return crossProduct(Operand1, Operand2);
}

Vector operator+(Vector const &Operand1, Vector const &Operand2)
{
	Vector ret;
	ret.x(Operand1.x() + Operand2.x());
	ret.y(Operand1.y() + Operand2.y());
	ret.z(Operand1.z() + Operand2.z());
	return ret;
}

real dotProduct(Vector const &Operand1, Vector const &Operand2)
{
	return Operand1.x() * Operand2.x() +
		   Operand1.y() * Operand2.y() +
		   Operand1.z() * Operand2.z();
}

Vector crossProduct(Vector const &Operand1, Vector const &Operand2)
{
	Vector retvec;
	retvec.x(Operand1.y() * Operand2.z() - Operand1.z() * Operand2.y());
	retvec.y(Operand1.z() * Operand2.x() - Operand1.x() * Operand2.z());
	retvec.z(Operand1.x() * Operand2.y() - Operand1.y() * Operand2.x());
	retvec.cleanVector();
	return retvec;
}
