// Filename: PlaceableSpheres.h
// Description: Classes for placeable spheres
// Author: Joshua Leaney
// Date Modified: 03/24/2021
//


#if defined __APPLE__
    #include <GLUT/glut.h>
#elif defined _WIN32 || defined _WIN64
    #include <GL\glut.h>
#elif defined __linux__
    #include <GL/freeglut.h>
#endif

#include "Material.h"

#pragma once
#if !defined(_PLACEABLESPHERES_H_)
#define _PLACEABLESPHERES_H_

class PlaceableSpheres
{
    private:
        GLfloat positionX, positionY, positionZ;
        GLfloat radius;
        bool correctLocation;
    public:       
        // Default constructor.
	    PlaceableSpheres();

	    // Default destructor.
	    ~PlaceableSpheres();
	
	    // Set the sphere defaults.
	    void reset();

        // accessor functions
        inline void movePosX(GLfloat x) {positionX += x;}
        inline void movePosY(GLfloat y) {positionY += y;}
        inline void movePosZ(GLfloat z) {positionZ += z;}
        inline void setRadius(GLfloat r) {radius = r;}
        inline void setCorrectLocation(bool yn) {correctLocation = yn;}

        inline GLfloat getPosX() {return positionX;}
        inline GLfloat getPosY() {return positionY;}
        inline GLfloat getPosZ() {return positionZ;}
        inline GLfloat getRadius() {return radius;}
        inline bool getCorrectLocation() {return correctLocation;}

        // drawing functions
        void placeCubic(GLUquadric *q, Material sMaterials[], GLfloat radius);
        void placeBCC(GLUquadric *q, Material sMaterials[], GLfloat radius);
        void placeFCC(GLUquadric *q, Material sMaterials[], GLfloat radius);
        void placeSphere(GLUquadric *q, Material sMaterials[], GLfloat radius);
        float rndf(float maxnum);
        
        // checking location functions
        void checkLocation(GLfloat myArray[][3], int arraySize);
        void storeLocation(GLfloat newArray[][3], int arraySize);
        void drawArray(GLUquadric *q, Material sMaterials[],  GLfloat radius, GLfloat myArray[][3], int arraySize);
};

#endif //_PLACEABLESPHERES_H_