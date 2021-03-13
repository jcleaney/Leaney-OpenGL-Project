// Filename: PlaceableSpheres.cpp
// Description: See header file for structural information  
// Author: Joshua Leaney
// Date Modified: 03/14/21
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
}

PlaceableSpheres::~PlaceableSpheres()
{
}

void PlaceableSpheres::reset()
{
    positionX = getRadius() + 2.0f;
    positionY = getRadius() - 1.0f;
    positionZ = getRadius() - 3.0f;
    correctLocation = false;
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

    static GLfloat checkVertices[8][3] =   {    {  20,  0,  0 }, // v0 
                                                {  20,  0,  0 }, // v1 
                                                {  20,  0,  0 }, // v2 
                                                {  20,  0,  0 }, // v3 
                                                {  20,  0,  0 }, // v4 
                                                {  20,  0,  0 }, // v5 
                                                {  20,  0,  0 }, // v6 
                                                {  20,  0,  0 }  // v7
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
    checkLocation(vertices, 8);
    storeLocation(checkVertices, 8); 
    drawArray(q, sMaterials, radius, checkVertices, 8);
}

// function for drawing the Body-Centered cubic lattice
void PlaceableSpheres::placeBCC(GLUquadric *q, Material sMaterials[], GLfloat radius)
{
    GLfloat r = radius*2.0f;
    
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

    GLfloat internal[1][3] = {{  0,  0,  0 }}; // central atom


    static GLfloat checkVertices[8][3] =   {    {  20,  0,  0 }, // v0 
                                                {  20,  0,  0 }, // v1 
                                                {  20,  0,  0 }, // v2 
                                                {  20,  0,  0 }, // v3 
                                                {  20,  0,  0 }, // v4 
                                                {  20,  0,  0 }, // v5 
                                                {  20,  0,  0 }, // v6 
                                                {  20,  0,  0 }  // v7
                                            };

    static GLfloat checkInternal[1][3] = {{ 20, 0, 0 }}; // central atom
    
    // draw the wire cube to show connection for vertices of unit cell
    glPushMatrix();
    glutWireCube(2*r);
    glPopMatrix();

    // draw the middle body centered sphere
    glPushMatrix();
    gluQuadricOrientation(q, GLU_OUTSIDE);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glTranslatef(internal[0][0], internal[0][1], internal[0][2]);
    glutWireSphere(radius, 24, 48);
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glPopMatrix();

    // Using a loop to draw all the spheres at the vertices to simplify program
    for(int i=0; i<8; i++)
    {
        // drawing the spheres in the unit cell
        glPushMatrix();
        gluQuadricOrientation(q, GLU_OUTSIDE);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glTranslatef(vertices[i][0], vertices[i][1], vertices[i][2]);
        glutWireSphere(radius, 24, 48);
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
        glPopMatrix();

        // drawing the connections between the BC atom and the vertices
        glPushMatrix();
        glBegin(GL_LINES);
        glVertex3f(vertices[i][0], vertices[i][1], vertices[i][2]);
        glVertex3f(0, 0, 0);
        glEnd();
        glPopMatrix();
    }

    placeSphere(q, sMaterials, radius);
    checkLocation(vertices, 8);
    storeLocation(checkVertices, 8); 
    drawArray(q, sMaterials, radius, checkVertices, 8);

    checkLocation(internal, 1);
    storeLocation(checkInternal, 1);
    drawArray(q, sMaterials, radius, checkInternal, 1);
}

// function for drawing the Face-Centered cubic lattice
void PlaceableSpheres::placeFCC(GLUquadric *q, Material sMaterials[], GLfloat radius)
{
    GLfloat r = radius*2.0f;
    
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
    
    // multi-dimensional array for all atoms on the face of the unit cell
    GLfloat faceCoords[6][3] =  {   {  0,  r,  0 }, // f0 
                                    {  0,  0,  r }, // f1 
                                    {  r,  0,  0 }, // f2 
                                    { -r,  0,  0 }, // f3 
                                    {  0,  0, -r }, // f4 
                                    {  0, -r,  0 }, // f5 
                                };
    
    static GLfloat checkVertices[8][3] =   {    {  20,  0,  0 }, // v0 
                                                {  20,  0,  0 }, // v1 
                                                {  20,  0,  0 }, // v2 
                                                {  20,  0,  0 }, // v3 
                                                {  20,  0,  0 }, // v4 
                                                {  20,  0,  0 }, // v5 
                                                {  20,  0,  0 }, // v6 
                                                {  20,  0,  0 }  // v7
                                            };

    static GLfloat checkFaceCoords[6][3] =  {   {  20,  0,  0 }, // f0 
                                                {  20,  0,  0 }, // f1 
                                                {  20,  0,  0 }, // f2 
                                                {  20,  0,  0 }, // f3 
                                                {  20,  0,  0 }, // f4 
                                                {  20,  0,  0 }, // f5 
                                            };

    // draw the wire cube to show connection for vertices of unit cell
    glPushMatrix();
    glutWireCube(2*r);
    glPopMatrix();

    // Using a loop to draw all the spheres at the vertices to simplify program
    for(int i=0; i<8; i++)
    {
        // Commands for Vertices
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

    // Drawing the face centered atoms
    for(int j=0; j<6; j++)
    {
        // commands to draw the atoms
        glPushMatrix();
        gluQuadricOrientation(q, GLU_OUTSIDE);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glTranslatef(faceCoords[j][0], faceCoords[j][1], faceCoords[j][2]);
        glutWireSphere(radius, 24, 48);
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
        glPopMatrix();

        // draw the connections between face centered atoms and vertices
        for(int k=0; k<8; k++)
        {   
            // faces on x-axis
            if(faceCoords[j][0] == vertices[k][0])
            {
                glPushMatrix();
                glBegin(GL_LINES);
                glVertex3f(faceCoords[j][0], faceCoords[j][1], faceCoords[j][2]);
                glVertex3f(vertices[k][0], vertices[k][1], vertices[k][2]);
                glEnd();
                glPopMatrix();
            }
            // faces on y-axis
            if(faceCoords[j][1] == vertices[k][1])
            {
                glPushMatrix();
                glBegin(GL_LINES);
                glVertex3f(faceCoords[j][0], faceCoords[j][1], faceCoords[j][2]);
                glVertex3f(vertices[k][0], vertices[k][1], vertices[k][2]);
                glEnd();
                glPopMatrix();
            }
            // faces on z-axis
            if(faceCoords[j][2] == vertices[k][2])
            {
                glPushMatrix();
                glBegin(GL_LINES);
                glVertex3f(faceCoords[j][0], faceCoords[j][1], faceCoords[j][2]);
                glVertex3f(vertices[k][0], vertices[k][1], vertices[k][2]);
                glEnd();
                glPopMatrix();
            }
        }
    }

    placeSphere(q, sMaterials, radius);
    checkLocation(vertices, 8);
    storeLocation(checkVertices, 8); 
    drawArray(q, sMaterials, radius, checkVertices, 8);

    checkLocation(faceCoords, 6);
    storeLocation(checkFaceCoords, 6);
    drawArray(q, sMaterials, radius, checkFaceCoords, 6);
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

void PlaceableSpheres::checkLocation(GLfloat myArray[][3], int arraySize)
{
    bool correctL = false;
    
    GLfloat xLoc = round(10*getPosX())/10;
    GLfloat yLoc = round(10*getPosY())/10;
    GLfloat zLoc = round(10*getPosZ())/10;
    GLfloat xStoreLoc = 0;
    GLfloat yStoreLoc = 0;
    GLfloat zStoreLoc = 0;
    
    setCorrectLocation(correctL);

    if(getCorrectLocation() == false)
    {
        for(int i=0; i<arraySize; i++)
        {
            xStoreLoc = round(10*myArray[i][0])/10;
            yStoreLoc = round(10*myArray[i][1])/10;
            zStoreLoc = round(10*myArray[i][2])/10;

            if(xLoc == xStoreLoc && yLoc == yStoreLoc && zLoc == zStoreLoc)
            {
                correctL = true;
                setCorrectLocation(correctL);
                i = arraySize;
            } else {
                correctL = false;
                setCorrectLocation(correctL);
            }
        }
    }
}

void PlaceableSpheres::storeLocation(GLfloat newArray[][3], int arraySize)
{
    int index = 0;
    static bool alreadyIncluded = false;

    GLfloat xLoc = round(10*getPosX())/10;
    GLfloat yLoc = round(10*getPosY())/10;
    GLfloat zLoc = round(10*getPosZ())/10;

    if(getCorrectLocation() == true)
    {
        for(int j=0; j<arraySize; j++)
        {
            if(xLoc == newArray[j][0] && yLoc == newArray[j][1] && zLoc == newArray[j][2])
            {
                alreadyIncluded = true;
                j = arraySize;
            } 
        }
        
        if(alreadyIncluded == false)
        {
            for(int i=0; i<arraySize; i++)
            {
                if(newArray[i][0] == 20)
                {
                    index = i;
                    i = arraySize;
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

void PlaceableSpheres::drawArray(GLUquadric *q, Material sMaterials[],  GLfloat radius, GLfloat myArray[][3], int arraySize)
{
    // Using a loop to draw all the spheres at the vertices to simplify program
    for(int i=0; i<arraySize; i++)
    {
        if(myArray[i][0] != 20)
        {
            glPushMatrix();
            gluQuadricOrientation(q, GLU_OUTSIDE);
            glEnable(GL_TEXTURE_GEN_S);
            glEnable(GL_TEXTURE_GEN_T);
            glTranslatef(myArray[i][0], myArray[i][1], myArray[i][2]);
            sMaterials[0].setupMaterial();
            gluSphere(q, radius+0.05, 50, 25);
            sMaterials[0].stopMaterial();
            glDisable(GL_TEXTURE_GEN_S);
            glDisable(GL_TEXTURE_GEN_T);
            glPopMatrix();
        }
    }
}