// Filename: Spherical.cpp
// Description: See header file for structural information  
// Author: Scott McDermott
// Date Modified: 10/30/2017
//


#include "Spherical.h"
#include "Vector.h"
#if defined __APPLE__
    #include <GLUT/glut.h>
#elif defined _WIN32 || defined _WIN64
    #include <GL\glut.h>
#elif defined __linux__
    #include <GL/freeglut.h>
#endif

#include <iostream>
using namespace std;

Spherical::Spherical()
{
	reset();
}

Spherical::Spherical(real const *pElements)
{
	assert(pElements);
	this->aElements[THETA] = pElements[THETA];
	this->aElements[PHI] = pElements[PHI];
	this->aElements[DIST] = fabs(pElements[DIST]);

}


Spherical::Spherical(real theta, real phi, real dist)
{
	this->aElements[THETA] = theta;
	this->aElements[PHI] = phi;
	this->aElements[DIST] = fabs(dist);
}

Spherical::~Spherical()
{
}

void Spherical::print()
{
	cout << "T=" << aElements[THETA] << ", P=" << aElements[PHI] << ", D=" << aElements[DIST] << endl;
}

void Spherical::rotateGraphics(void)
{
	glRotatef(this->P(), RIGHTV);	// Up and down
	glRotatef(-this->T(), UPV);	// side to side
//	glRotatef( 90, SIDEV );		// Initial rotation

}

Spherical &Spherical::operator=(Vector const &vec)
{
	Vector v;
	v = vec;
	v.normalize();
	this->D(vec.length());
	this->P(asin(v.y()) * RADIANS_TO_DEGREES);
	this->T(atan2(v.x(), v.z()) * RADIANS_TO_DEGREES);
	return(*this);
}

Spherical operator+(Spherical const &Operand1, Spherical const &Operand2)
{
	Spherical revsph;
	revsph.T(Operand1.T() + Operand2.T());
	revsph.P(Operand1.P() + Operand2.P());
	revsph.D(1.0); //fabs(Operand1.D() + Operand2.D()));
	return revsph;
}

Spherical operator-( Spherical const &Operand1, Spherical const &Operand2 )
{
	Spherical revsph;
	revsph.T(Operand1.T() - Operand2.T());
	revsph.P(Operand1.P() - Operand2.P());
	revsph.D(1.0); //fabs(Operand1.D() - Operand2.D()));
	return revsph;
}
