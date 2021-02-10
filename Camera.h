// Filename: Camera.h
// Description: Classes for 3D Camera 
// Author: Scott McDermott
// Date Modified: 10/30/2017
//


#if defined __APPLE__
    #include <GLUT/glut.h>
#elif defined _WIN32 || defined _WIN64
    #include <GL\glut.h>
#elif defined __linux__
    #include <GL/freeglut.h>
#endif

#include "Vector.h"
#include "Spherical.h"

#pragma once
#if !defined(_CAMERA_H_)
#define _CAMERA_H_

// Projection type is either orthographic(parallel) or perspective.
enum Camera3DProjType { CAM_PROJ_ORTHO, CAM_PROJ_PERSPECTIVE };




class Camera
{
public:
	// Default constructor.
	Camera();

	// Default destructor.
	~Camera();
	
	// Set the camera defaults.
	void reset();
	
public:
///////////////////////////
// Variable accessors... //
///////////////////////////

	// Set the camera projection type.
	inline void setProjectionType(Camera3DProjType pt) {projType = pt; calculationsUpToDate = false;}

	// Move it to the specified location.
	inline void setLocation(Point pt) {location = pt; calculationsUpToDate = false;}

	// Move it to the specified location.
	inline void setLocation(real x, real y, real z) {location.x(x), location.y(y), location.z(z); calculationsUpToDate = false;}
	
	// Rotate it to the specified direction.
	inline void setRotation(Spherical sph) {rotation = sph; calculationsUpToDate = false;}

	// Rotate it to the specified direction.
	inline void setRotation(real t, real p, real d=1.0) {rotation.T(t), rotation.P(p), rotation.D(d); calculationsUpToDate = false;}
	
	// Change the camera defaults.
	void setupCamera(Camera3DProjType pt, int w, int h, real fov = 45.0f, real nearC = 0.1f, real farC = 1000.0f);

	// Turn to the left the specified number of degrees.
	void turnLeft(real degrees = 1.0f);

	// Turn to the right the specified number of degrees.
	inline void turnRight(real degrees = 1.0f) {turnLeft(-degrees);}

	// Turn to the left the specified number of degrees.
	void lookUp(real degrees = 1.0f);

	// Turn to the right the specified number of degrees.
	inline void lookDown(real degrees = 1.0f) {lookUp(-degrees);}

	// Move to the left the specified number of units, without turning.
	void strafeLeft(real units = 1.0f);

	// Move to the right the specified number of units, without turning.
	inline void strafeRight(real units = 1.0f) {strafeLeft(-units);}

	// Move forward the specified number of units.
	void moveForward(real units = 1.0f);

	// Move backward the specified number of units.
	inline void moveBackward(real units = 1.0f) {moveForward(-units);}

	// Move up the specified number of units.
	void moveUp(real units = 1.0f);

	// Move down the specified number of units.
	inline void moveDown(real units = 1.0f) {moveUp(-units);}
	
protected:
	// Flag indicating if any calulated variables are not updated.
	// These include UVN vectors, psAimPoint, and any sound calculation.
	// Any change to the position, aim point/direction, or up direction will
	// invalidate them all.
	bool calculationsUpToDate;
	
	// The height of the avatar (actually the height of it's eyes).
//	real eyeheight;

/////////////////////////////////////////////////////
//            Specified Camera vaiables            //
/////////////////////////////////////////////////////

	// Parallel or perspective projection.
	Camera3DProjType projType;
	
	// The actual location of the camera
	Point location;
	
	// Direction the camera is point
	Spherical rotation;

	// Perspective field of view angles in degrees span whole field of view in
	// the horizontal direction.
	real fovAngle;
	
	// Placement of the clipping planes.  Distances are measured > 0 along the aimDir.
	// nearClip must be less than farClip.
	real nearClip;
	real farClip;
		
	// Dimensions of viewport camera view is rendered into (given in window pixels).
	int vpWidth, vpHeight;

	
///////////////////////////////////////////////////////
//            Calculated Camera variables            //
///////////////////////////////////////////////////////

	// Calculated XYZ location of aim point (note: this is not kept up to date).
	Point aimPoint;
	
	// Viewport width / height.
	real aspectRatio;

	// Camera coordinate system axes expressed in XYZ WCS.
	Vector		U, V, N;
	
public:
	// Call OpenGL functions to setup current camera view projection.
	// Your code is responsible for calling glViewport.
	void runCamera();

	// Update the various calculated camera variables.
	void update();

	// Force the update of all of the calulated variales.
	inline void forceUpdate() {calculationsUpToDate = false; update();}

};


#endif //_CAMERA_H_