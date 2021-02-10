// Filename: Camera.cpp
// Description: See header file for structural information  
// Author: Scott McDermott
// Date Modified: 8/18/2020
//


#include "Camera.h"
 
#include <iostream>
using namespace std;

Camera::Camera()
{
	reset();
}

Camera::~Camera()
{
}

void Camera::reset()
{
//	eyeheight = 2.0;
	projType = CAM_PROJ_PERSPECTIVE;
	fovAngle = 45.0; //60.0f
	nearClip = 0.1f; //1.0f
	farClip = 100.0f; //1000.0f
	vpWidth = 640;
	vpHeight = 480;
	location.reset();
	rotation.reset();
	calculationsUpToDate = false;
}

void Camera::setupCamera(Camera3DProjType pt, int w, int h, real fov, real nearC, real farC)
{
	projType = pt;
	vpWidth = w;
	vpHeight = h;
	fovAngle = fov;
	nearClip = nearC;
	farClip = farC;
	calculationsUpToDate = false;
}



void Camera::turnLeft(real degrees)
{
	rotation += degrees;
	calculationsUpToDate = false;
}

void Camera::lookUp(real degrees)
{
	rotation *= degrees;
	calculationsUpToDate = false;
}

void Camera::strafeLeft(real units)
{
	Vector step;
	step = rotation;
	Vector cross;
	step.y(0.0);
	step.normalize();
	cross = crossProduct(step, UP);
	cross *= -units; // flip the cross product!
	location += cross;
	calculationsUpToDate = false;
}

void Camera::moveForward(real units)
{
	Vector step;
	step = rotation;
	step.y(0.0);
	step.normalize();
	step *= units;
	location += step;
	calculationsUpToDate = false;
}


void Camera::moveUp(real units)
{
	units += location.y();
	location.y(units);
	calculationsUpToDate = false;
}


void Camera::runCamera()
{
	update();

	// Scale z-buffer precision to span range of near & far clip planes.
	//*** Undefined values to glDepthRange can cause strange z-buffer behavior.
	// glDepthRange(nearClip, farClip);
	
	// setup perspective/orthogonal projection... based on field of view.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	

	if(projType == CAM_PROJ_PERSPECTIVE)
		gluPerspective(fovAngle, aspectRatio, nearClip, farClip);
	else    
		glOrtho(-vpWidth, vpWidth, -vpHeight, vpHeight, nearClip, farClip);

	gluLookAt(location.x(), location.y(), location.z(), 
			  aimPoint.x(), aimPoint.y(), aimPoint.z(),
			  UP.x(), UP.y(), UP.z());
	
	// Viewing transformation next places the camera position.
	// Camera is at ptLocation and looks towards aimPoint.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

//	GLfloat light_position[] = {1.0, 1.0, 1.0, 1.0};
//	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	
}

void Camera::update()
{
	if (calculationsUpToDate)
		return;

	// First, update the aspect ratio.
	aspectRatio = vpWidth / vpHeight;

	// Next, update the aim point.
	rotation.D((farClip - nearClip)/2.0);
	aimPoint = rotation;		// (convert from spherical to point)
	aimPoint += location;
	// Find XYZ world coordinate (unit length vectors) that give the orientation
	// of the Camera3D (UVN vectors).
	//
	// N = rotation Camera3D is aimed in.
	// U = "right-hand" vector
	// V = "upwards" pointing vector perpendicular to U and N.  V is not necessarily
	//		equal to the upVec vector.  ("UP" vector will help determine the 
	//      orientation of the V axis.)
	N = rotation;	// N axis is the sphDirection, normalized.
	N.normalize();
	U = crossProduct(N, UP);
	U.normalize();
	V = crossProduct(U, N);
	V.normalize();

	calculationsUpToDate = true;

}
