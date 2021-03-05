//Project Name: GLUtilities.h
//Description: Custom Utilities for OpenGL
//Author: Joshua Leaney
//Date Last Modified: 12/14/2020

#include "Material.h"

#pragma once
#if !defined(GL_UTILITIES_H_)
#define GL_UTILITIES_H_

#include <iostream>
using namespace std;

#if defined __APPLE__
    #include <GLUT/glut.h>
#elif defined _WIN32 || defined _WIN64
    #include <GL\glut.h>
#elif defined __linux__
    #include <GL\/freeglut.h>
#endif

void drawStrokeText(char *text, void *font, GLfloat x, GLfloat y, GLfloat z);
GLfloat getStrokeTextWidth(char *text, void *font);
void drawBitmapText(char *text, void *font, GLfloat x, GLfloat y);
GLfloat getBitmapTextWidth(char *text, void *font);

void drawCubic(GLUquadric *q, Material sMaterials[], GLfloat radius);
void drawBCC(GLUquadric *q, Material sMaterials[], GLfloat radius);
void drawFCC(GLUquadric *q, Material sMaterials[], GLfloat radius);
void drawZnBlnd(GLUquadric *q, Material sMaterials[], GLfloat radius);
void drawHeusler(GLUquadric *q, Material sMaterials[], GLfloat radius);
void placeCubic(GLUquadric *q, Material sMaterials[], GLfloat radius);

#endif //GL_UTILITIES_H_