//Project Name: GLUtilities.cpp
//Description: See header for description
//Author: Joshua Leaney
//Date Last Modified: 12/14/2020

#include "GLUtilities.h"

void drawStrokeText(char *text, void *font, GLfloat x, GLfloat y, GLfloat z)
{
    glPushMatrix();
    glTranslatef(x, y, z);
    char *c;
    for(c=text; *c; c++)
    {
        //glColor3f((*c)/255.0f, (*c)/255.0f, (*c)/255.0f);
        glColor3f(rand()/(float)RAND_MAX, rand()/(float)RAND_MAX, rand()/(float)RAND_MAX);
        glutStrokeCharacter(font, *c);
    }
    glPopMatrix();
}

GLfloat getStrokeTextWidth(char *text, void *font)
{
    GLfloat w = 0.0f;
    char *c;
    for(c=text; *c; c++)
    {
        w += (GLfloat)glutStrokeWidth(font, *c);
    }
    return w;
}

void drawBitmapText(char *text, void *font, GLfloat x, GLfloat y)
{

    glPushMatrix();
    glRasterPos2f(x, y);
    char *c;
    for(c=text; *c; c++)
    {
        glutBitmapCharacter(font, *c);
    }
    glPopMatrix();
}

GLfloat getBitmapTextWidth(char *text, void *font)
{
    GLfloat w = 0.0f;
    char *c;
    for(c=text; *c; c++)
    {
        w += (GLfloat)glutBitmapWidth(font, *c);
    }
    return w;
}

// function for drawing the Simple Cubic lattice
void drawCubic(GLUquadric *q, Material sMaterials[], GLfloat radius)
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
        sMaterials[0].setupMaterial();
        gluSphere(q, radius, 50, 25);
        sMaterials[0].stopMaterial();
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
        glPopMatrix();
    }
}

// function for drawing the Body-Centered cubic lattice
void drawBCC(GLUquadric *q, Material sMaterials[], GLfloat radius)
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

    // draw the wire cube to show connection for vertices of unit cell
    glPushMatrix();
    glutWireCube(2*r);
    glPopMatrix();

    // draw the middle body centered sphere
    glPushMatrix();
    gluQuadricOrientation(q, GLU_OUTSIDE);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    sMaterials[1].setupMaterial();
    gluSphere(q, radius, 50, 25);
    sMaterials[1].stopMaterial();
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
        sMaterials[0].setupMaterial();
        gluSphere(q, radius, 50, 25);
        sMaterials[0].stopMaterial();
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
}

// function for drawing the Face-Centered Cubic lattice
void drawFCC(GLUquadric *q, Material sMaterials[], GLfloat radius)
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
        sMaterials[0].setupMaterial();
        gluSphere(q, radius, 50, 25);
        sMaterials[0].stopMaterial();
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
        sMaterials[1].setupMaterial();
        gluSphere(q, radius, 50, 25);
        sMaterials[1].stopMaterial();
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
}

// function for drawing the Diamond (Zinc-blende) cubic lattice
void drawZnBlnd(GLUquadric *q, Material sMaterials[], GLfloat radius)
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
                                    {  0, -r,  0 }  // f5 
                                };

    // multi-dimensional array for all atoms contained within the unit cell
    GLfloat insideCoords[4][3] =    {   {  r/2, -r/2, -r/2 },   // i0
                                        {  r/2,  r/2,  r/2 },   // i1
                                        { -r/2, -r/2,  r/2 },   // i2
                                        { -r/2,  r/2, -r/2 }    // i3
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
        sMaterials[0].setupMaterial();
        gluSphere(q, radius*3/4, 50, 25);
        sMaterials[0].stopMaterial();
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
        glPopMatrix();
    }

    for(int j=0; j<6; j++)
    {   
        // Commands for Face-Centered atoms
        glPushMatrix();
        gluQuadricOrientation(q, GLU_OUTSIDE);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glTranslatef(faceCoords[j][0], faceCoords[j][1], faceCoords[j][2]);
        sMaterials[0].setupMaterial();
        gluSphere(q, radius*3/4, 50, 25);
        sMaterials[0].stopMaterial();
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
        glPopMatrix();
    }
    
    for(int k=0; k<4; k++)
    {
        // Commands for inside atoms
        glPushMatrix();
        gluQuadricOrientation(q, GLU_OUTSIDE);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glTranslatef(insideCoords[k][0], insideCoords[k][1], insideCoords[k][2]);
        sMaterials[1].setupMaterial();
        gluSphere(q, radius/2, 50, 25);
        sMaterials[1].stopMaterial();
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
        glPopMatrix();

        // Display the connections between inside atoms and their partnering atoms. Can separate all the inside atoms 
        // by looking at their x and y positions so the comparisons below correspond to these locations
        if (insideCoords[k][0] > 0)         // ( r, +/- r, +/- r)
        {
            if (insideCoords[k][1] < 0)     // ( +r, -r, -r)
            {
                glPushMatrix();
                glBegin(GL_LINES);
                glVertex3f(insideCoords[k][0], insideCoords[k][1], insideCoords[k][2]);
                glVertex3f(faceCoords[5][0], faceCoords[5][1], faceCoords[5][2]);
                glEnd();
                glPopMatrix();

                glPushMatrix();
                glBegin(GL_LINES);
                glVertex3f(insideCoords[k][0], insideCoords[k][1], insideCoords[k][2]);
                glVertex3f(faceCoords[2][0], faceCoords[2][1], faceCoords[2][2]);
                glEnd();
                glPopMatrix();

                glPushMatrix();
                glBegin(GL_LINES);
                glVertex3f(insideCoords[k][0], insideCoords[k][1], insideCoords[k][2]);
                glVertex3f(faceCoords[4][0], faceCoords[4][1], faceCoords[4][2]);
                glEnd();
                glPopMatrix();

                glPushMatrix();
                glBegin(GL_LINES);
                glVertex3f(insideCoords[k][0], insideCoords[k][1], insideCoords[k][2]);
                glVertex3f(vertices[4][0], vertices[4][1], vertices[4][2]);
                glEnd();
                glPopMatrix();
            }
            if (insideCoords[k][1] > 0)     // ( +r, +r, +r)
            {
                glPushMatrix();
                glBegin(GL_LINES);
                glVertex3f(insideCoords[k][0], insideCoords[k][1], insideCoords[k][2]);
                glVertex3f(faceCoords[0][0], faceCoords[0][1], faceCoords[0][2]);
                glEnd();
                glPopMatrix();

                glPushMatrix();
                glBegin(GL_LINES);
                glVertex3f(insideCoords[k][0], insideCoords[k][1], insideCoords[k][2]);
                glVertex3f(faceCoords[1][0], faceCoords[1][1], faceCoords[1][2]);
                glEnd();
                glPopMatrix();

                glPushMatrix();
                glBegin(GL_LINES);
                glVertex3f(insideCoords[k][0], insideCoords[k][1], insideCoords[k][2]);
                glVertex3f(faceCoords[2][0], faceCoords[2][1], faceCoords[2][2]);
                glEnd();
                glPopMatrix();

                glPushMatrix();
                glBegin(GL_LINES);
                glVertex3f(insideCoords[k][0], insideCoords[k][1], insideCoords[k][2]);
                glVertex3f(vertices[0][0], vertices[0][1], vertices[0][2]);
                glEnd();
                glPopMatrix();
            }
        }
        if (insideCoords[k][0] < 0)         // (-r, +/- r, +/-r)
        {
            if (insideCoords[k][1] < 0)     // (-r, - r, r)
            {
                glPushMatrix();
                glBegin(GL_LINES);
                glVertex3f(insideCoords[k][0], insideCoords[k][1], insideCoords[k][2]);
                glVertex3f(faceCoords[1][0], faceCoords[1][1], faceCoords[1][2]);
                glEnd();
                glPopMatrix();

                glPushMatrix();
                glBegin(GL_LINES);
                glVertex3f(insideCoords[k][0], insideCoords[k][1], insideCoords[k][2]);
                glVertex3f(faceCoords[3][0], faceCoords[3][1], faceCoords[3][2]);
                glEnd();
                glPopMatrix();

                glPushMatrix();
                glBegin(GL_LINES);
                glVertex3f(insideCoords[k][0], insideCoords[k][1], insideCoords[k][2]);
                glVertex3f(faceCoords[5][0], faceCoords[5][1], faceCoords[5][2]);
                glEnd();
                glPopMatrix();

                glPushMatrix();
                glBegin(GL_LINES);
                glVertex3f(insideCoords[k][0], insideCoords[k][1], insideCoords[k][2]);
                glVertex3f(vertices[2][0], vertices[2][1], vertices[2][2]);
                glEnd();
                glPopMatrix();
            }
            if (insideCoords[k][1] > 0)     // (-r, r,-r)
            {
                glPushMatrix();
                glBegin(GL_LINES);
                glVertex3f(insideCoords[k][0], insideCoords[k][1], insideCoords[k][2]);
                glVertex3f(faceCoords[0][0], faceCoords[0][1], faceCoords[0][2]);
                glEnd();
                glPopMatrix();

                glPushMatrix();
                glBegin(GL_LINES);
                glVertex3f(insideCoords[k][0], insideCoords[k][1], insideCoords[k][2]);
                glVertex3f(faceCoords[3][0], faceCoords[3][1], faceCoords[3][2]);
                glEnd();
                glPopMatrix();

                glPushMatrix();
                glBegin(GL_LINES);
                glVertex3f(insideCoords[k][0], insideCoords[k][1], insideCoords[k][2]);
                glVertex3f(faceCoords[4][0], faceCoords[4][1], faceCoords[4][2]);
                glEnd();
                glPopMatrix();

                glPushMatrix();
                glBegin(GL_LINES);
                glVertex3f(insideCoords[k][0], insideCoords[k][1], insideCoords[k][2]);
                glVertex3f(vertices[6][0], vertices[6][1], vertices[6][2]);
                glEnd();
                glPopMatrix();
            }
        }
            
    }
}

// function for drawing the Simple Cubic lattice
void drawHeusler(GLUquadric *q, Material sMaterials[], GLfloat radius)
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
    // draw the wire cube to show connection for vertices of unit cell
    glPushMatrix();
    glutWireCube(2*r);
    glPopMatrix();

    // Using a loop to draw all the spheres at the vertices to simplify program
    // bottom front left 
    for(int i=0; i<8; i++)
    {
        glPushMatrix();
        gluQuadricOrientation(q, GLU_OUTSIDE);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glTranslatef(vertices[i][0], vertices[i][1], vertices[i][2]);
        sMaterials[0].setupMaterial();
        gluSphere(q, radius, 50, 25);
        sMaterials[0].stopMaterial();
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
        glPopMatrix();
    }

    // draw the wire cube to show connection for vertices of unit cell
    glPushMatrix();
    glTranslatef(2*r, 0, 0);
    glutWireCube(2*r);
    glPopMatrix();

    // bottom front right 
    for(int i=0; i<8; i++)
    {
        glPushMatrix();
        gluQuadricOrientation(q, GLU_OUTSIDE);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glTranslatef(vertices[i][0] + 2*r, vertices[i][1], vertices[i][2]);
        sMaterials[0].setupMaterial();
        gluSphere(q, radius, 50, 25);
        sMaterials[0].stopMaterial();
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
        glPopMatrix();
    }

    // draw the wire cube to show connection for vertices of unit cell
    glPushMatrix();
    glTranslatef(0, 0, 2*r);
    glutWireCube(2*r);
    glPopMatrix();

    // bottom back left
    for(int i=0; i<8; i++)
    {
        glPushMatrix();
        gluQuadricOrientation(q, GLU_OUTSIDE);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glTranslatef(vertices[i][0], vertices[i][1], vertices[i][2] + 2*r);
        sMaterials[0].setupMaterial();
        gluSphere(q, radius, 50, 25);
        sMaterials[0].stopMaterial();
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
        glPopMatrix();
    }

    // draw the wire cube to show connection for vertices of unit cell
    glPushMatrix();
    glTranslatef(2*r, 0, 2*r);
    glutWireCube(2*r);
    glPopMatrix();

    // bottom back right
    for(int i=0; i<8; i++)
    {
        glPushMatrix();
        gluQuadricOrientation(q, GLU_OUTSIDE);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glTranslatef(vertices[i][0] + 2*r, vertices[i][1], vertices[i][2] + 2*r);
        sMaterials[0].setupMaterial();
        gluSphere(q, radius, 50, 25);
        sMaterials[0].stopMaterial();
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
        glPopMatrix();
    }

    // draw the wire cube to show connection for vertices of unit cell
    glPushMatrix();
    glTranslatef(0, 2*r, 0);
    glutWireCube(2*r);
    glPopMatrix();

    // top front left 
    for(int i=0; i<8; i++)
    {
        glPushMatrix();
        gluQuadricOrientation(q, GLU_OUTSIDE);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glTranslatef(vertices[i][0], vertices[i][1] + 2*r, vertices[i][2]);
        sMaterials[0].setupMaterial();
        gluSphere(q, radius, 50, 25);
        sMaterials[0].stopMaterial();
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
        glPopMatrix();
    }

    // draw the wire cube to show connection for vertices of unit cell
    glPushMatrix();
    glTranslatef(2*r, 2*r, 0);
    glutWireCube(2*r);
    glPopMatrix();

    // top front right 
    for(int i=0; i<8; i++)
    {
        glPushMatrix();
        gluQuadricOrientation(q, GLU_OUTSIDE);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glTranslatef(vertices[i][0] + 2*r, vertices[i][1] + 2*r, vertices[i][2]);
        sMaterials[0].setupMaterial();
        gluSphere(q, radius, 50, 25);
        sMaterials[0].stopMaterial();
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
        glPopMatrix();
    }

    // draw the wire cube to show connection for vertices of unit cell
    glPushMatrix();
    glTranslatef(0, 2*r, 2*r);
    glutWireCube(2*r);
    glPopMatrix();

    // top back left
    for(int i=0; i<8; i++)
    {
        glPushMatrix();
        gluQuadricOrientation(q, GLU_OUTSIDE);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glTranslatef(vertices[i][0], vertices[i][1] + 2*r, vertices[i][2] + 2*r);
        sMaterials[0].setupMaterial();
        gluSphere(q, radius, 50, 25);
        sMaterials[0].stopMaterial();
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
        glPopMatrix();
    }

    // draw the wire cube to show connection for vertices of unit cell
    glPushMatrix();
    glTranslatef(2*r, 2*r, 2*r);
    glutWireCube(2*r);
    glPopMatrix();

    // top back right
    for(int i=0; i<8; i++)
    {
        glPushMatrix();
        gluQuadricOrientation(q, GLU_OUTSIDE);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glTranslatef(vertices[i][0] + 2*r, vertices[i][1] + 2*r, vertices[i][2] + 2*r);
        sMaterials[0].setupMaterial();
        gluSphere(q, radius, 50, 25);
        sMaterials[0].stopMaterial();
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
        glPopMatrix();
    }

    // draw the wire cube to show connection for vertices of unit cell
    glPushMatrix();
    glTranslatef(r, r, r);
    glColor3f(1.0, 0.0, 0.0);
    glutWireCube(2*r);
    glPopMatrix();

    // middle 
    for(int i=0; i<8; i++)
    {
        glPushMatrix();
        gluQuadricOrientation(q, GLU_OUTSIDE);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glTranslatef(vertices[i][0] + r, vertices[i][1] + r, vertices[i][2] + r);
        sMaterials[1].setupMaterial();
        gluSphere(q, radius, 50, 25);
        sMaterials[1].stopMaterial();
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
        glPopMatrix();
    }
}