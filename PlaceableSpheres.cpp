// Filename: PlaceableSpheres.cpp
// Description: See header file for structural information  
// Author: Joshua Leaney
// Date Modified: 03/04/2020
//


#include "PlaceableSpheres.h"
 
#include <iostream>
#include <cmath>
using namespace std;

PlaceableSpheres::PlaceableSpheres()
{
    positionX = 0.0f;
    positionY = 0.0f;
    positionZ = 0.0f;
    correctLocation = false;
    sphereID = 0;
}

PlaceableSpheres::~PlaceableSpheres()
{
}

void PlaceableSpheres::reset()
{
    positionX = 0.0f;
    positionY = 0.0f;
    positionZ = 0.0f;
    correctLocation = false;
    sphereID = 0;
}

// function for drawing the Simple Cubic lattice
void PlaceableSpheres::placeCubic(GLUquadric *q, Material sMaterials[], GLfloat radius)
{
    GLfloat r = radius*2.0f;
    setRadius(r);
    
    // assign the vertices of a cube to a multidimensional array to be used for drawing
    GLfloat vertices[8][3] =    {   {  r,  r,  r }, // v0 
                                    { -r,  r,  r }, // v1 
                                    { -r, -r,  r }, // v2 
                                    {  r, -r,  r }, // v3 
                                    {  r, -r, -r }, // v4 
                                    {  r,  r, -r }, // v5 
                                    { -r,  r, -r }, // v6 
                                    { -r, -r, -r }  // v7
                                };

    static GLfloat checkVertices[8][3] =   {    {  0,  0,  0 }, // v0 
                                                {  0,  0,  0 }, // v1 
                                                {  0,  0,  0 }, // v2 
                                                {  0,  0,  0 }, // v3 
                                                {  0,  0,  0 }, // v4 
                                                {  0,  0,  0 }, // v5 
                                                {  0,  0,  0 }, // v6 
                                                {  0,  0,  0 }  // v7
                                            };

    // draw the wire cube to show connection for vertices of unit cell
    glPushMatrix();
    glutWireCube(2*r);
    glPopMatrix();

    // Using a loop to draw all the spheres at the vertices to simplify program
    for(int i=0; i<8; i++)
    {
        glPushMatrix();
        gluQuadricOrientation(q, GLU_OUTSIDE);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glTranslatef(vertices[i][0], vertices[i][1], vertices[i][2]);
        glutWireSphere(radius, 24, 48);
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
        glPopMatrix();
    }

    placeSphere(q, sMaterials, radius);
    checkLocation(vertices);
    storeLocation(checkVertices); 

    // Using a loop to draw all the spheres at the vertices to simplify program
    for(int i=0; i<8; i++)
    {
        if(checkVertices[i][0] != 0)
        {
            glPushMatrix();
            gluQuadricOrientation(q, GLU_OUTSIDE);
            glEnable(GL_TEXTURE_GEN_S);
            glEnable(GL_TEXTURE_GEN_T);
            glTranslatef(checkVertices[i][0], checkVertices[i][1], checkVertices[i][2]);
            sMaterials[0].setupMaterial();
            gluSphere(q, radius+0.05, 50, 25);
            sMaterials[0].stopMaterial();
            glDisable(GL_TEXTURE_GEN_S);
            glDisable(GL_TEXTURE_GEN_T);
            glPopMatrix();
        }
    }
}

// function for drawing spheres on to scene
void PlaceableSpheres::placeSphere(GLUquadric *q, Material sMaterials[], GLfloat radius)
{    
    glPushMatrix();
    gluQuadricOrientation(q, GLU_OUTSIDE);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glTranslatef(getPosX(), getPosY(), getPosZ());
    sMaterials[0].setupMaterial();
    gluSphere(q, radius, 50, 25);
    sMaterials[0].stopMaterial();
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glPopMatrix();

    // add the highlighting ring here so that it is easier for the user to observe their placements
}

void PlaceableSpheres::checkLocation(GLfloat myArray[][3])
{
    bool correctL = false;
    
    GLfloat xLoc = round(10*getPosX())/10;
    GLfloat yLoc = round(10*getPosY())/10;
    GLfloat zLoc = round(10*getPosZ())/10;
    GLfloat xStoreLoc;
    GLfloat yStoreLoc;
    GLfloat zStoreLoc;
    
    setCorrectLocation(correctL);

    if(getCorrectLocation() == false)
    {
        for(int iterate=0; iterate<8; iterate++)
        {
            xStoreLoc = round(10*myArray[iterate][0])/10;
            yStoreLoc = round(10*myArray[iterate][1])/10;
            zStoreLoc = round(10*myArray[iterate][2])/10;

            if(xLoc == xStoreLoc && yLoc == yStoreLoc && zLoc == zStoreLoc)
            {
                correctL = true;
                setCorrectLocation(correctL);
                iterate = 8;
            } else {
                correctL = false;
                setCorrectLocation(correctL);
            }
        }
    }
}

void PlaceableSpheres::storeLocation(GLfloat newArray[][3])
{
    int index = 0;
    static bool alreadyIncluded = false;

    GLfloat xLoc = round(10*getPosX())/10;
    GLfloat yLoc = round(10*getPosY())/10;
    GLfloat zLoc = round(10*getPosZ())/10;

    if(getCorrectLocation() == true)
    {
        for(int j=0; j<8; j++)
        {
            if(xLoc == newArray[j][0] && yLoc == newArray[j][1] && zLoc == newArray[j][2])
            {
                alreadyIncluded = true;
                j = 8;
            } 
        }
        
        if(alreadyIncluded == false)
        {
            for(int i=0; i<8; i++)
            {
                if(newArray[i][0] == 0)
                {
                    index = i;
                    i = 8;
                }
            }

            newArray[index][0] = round(xLoc);
            newArray[index][1] = round(yLoc);
            newArray[index][2] = round(zLoc);

            reset();
        }
    } else {
        alreadyIncluded = false;
    }
}

