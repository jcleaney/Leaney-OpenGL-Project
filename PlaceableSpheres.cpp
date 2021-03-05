// Filename: PlaceableSpheres.cpp
// Description: See header file for structural information  
// Author: Joshua Leaney
// Date Modified: 03/04/2020
//


#include "PlaceableSpheres.h"
 
#include <iostream>
using namespace std;

PlaceableSpheres::PlaceableSpheres()
{
    reset();
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

    loadMaterials();
}

void PlaceableSpheres::loadMaterials()
{
    //shapeMaterials[0].load("Textures/Wood1.tga");
    //shapeMaterials[1].load("Textures/Marble1.tga");
    //shapeMaterials[2].load("Textures/Ground3.tga");
}

// function for drawing the Simple Cubic lattice
void PlaceableSpheres::placeCubic(GLUquadric *q, Material sMaterials[], GLfloat radius, int id)
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

    placeSphere(q, sMaterials, radius, id);
    
}

// function for drawing spheres on to scene
void PlaceableSpheres::placeSphere(GLUquadric *q, Material sMaterials[], GLfloat radius, int id)
{
    setSphereID(id);
    
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
}

bool PlaceableSpheres::checkLocation()
{
    GLfloat r = getRadius();

    if(getPosX() == r || getPosX() == -r)
    {
        if(getPosY() == r || getPosY() == -r)
        {
            if(getPosZ() == r || getPosZ() == -r)
            {
                correctLocation = true;
            }
        }
    }

    return getCorrectLocation();
}