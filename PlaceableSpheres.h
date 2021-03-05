// Filename: PlaceableSpheres.h
// Description: Classes for placeable spheres
// Author: Joshua Leaney
// Date Modified: 03/04/2021
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
        int sphereID;
    public:        
        // Default constructor.
	    PlaceableSpheres();

	    // Default destructor.
	    ~PlaceableSpheres();
	
	    // Set the sphere defaults.
	    void reset();

        // set the default materials
        void loadMaterials();

        // accessor functions
        inline void movePosX(GLfloat x) {positionX += x;}
        inline void movePosY(GLfloat y) {positionY += y;}
        inline void movePosZ(GLfloat z) {positionZ += z;}
        inline void setSphereID(int a) {sphereID = a;}
        inline void setRadius(int r) {radius = r;}

        inline GLfloat getPosX() {return positionX;}
        inline GLfloat getPosY() {return positionY;}
        inline GLfloat getPosZ() {return positionZ;}
        inline GLfloat getRadius() {return radius;}
        inline bool getCorrectLocation() {return correctLocation;}
        inline int getSphereID() {return sphereID;}

        // drawing functions
        void placeCubic(GLUquadric *q, Material sMaterials[], GLfloat radius, int id);
        void placeSphere(GLUquadric *q, Material sMaterials[], GLfloat radius, int id);
        bool checkLocation();
};

#endif //_PLACEABLESPHERES_H_