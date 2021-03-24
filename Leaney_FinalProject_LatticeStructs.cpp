//Project Name: Leaney_FinalProject_LatticeStructs.cpp
//Description: Developing openGL to display Unit Cells!
//Author: Joshua Leaney
//Date Last Modified: 03/24/21

#include "GLUtilities.h"
#include "Camera.h"
#include "Material.h"
#include "PlaceableSpheres.h"

//Function Prototypes
void resetScene();
void enableLights();
void display(void);
void drawCubic(GLUquadric *q, Material sMaterials[], GLfloat radius);
void drawBCC(GLUquadric *q, Material sMaterials[], GLfloat radius);
void drawFCC(GLUquadric *q, Material sMaterials[], GLfloat radius);
void drawZnBlnd(GLUquadric *q, Material sMaterials[], GLfloat radius);
void drawHeusler(GLUquadric *q, Material sMaterials[], GLfloat radius);
void placeCubic(GLUquadric *q, Material sMaterials[], GLfloat radius);
void reshape(GLsizei width, GLsizei height);            // use GLsizei makes it consistent across all platforms
void keyboardClick(unsigned char key, int x, int y);    // callback function with multiple arguments for keyboard pressed
void specialInput(int key, int x, int y);               // callback for special inputs that are not recognized in GLUT
void mouseClick(int button, int state, int x, int y);
void mouseMotion(int x, int y);
void timer(int ms);                                     // unit is integer for milliseconds


bool blEnableLights;    // Are the lights on or off?
bool cubicEnable;       // Are we displaying the Simple Cubic structure?
bool bccEnable;         // Are we displaying the BCC structure?
bool fccEnable;         // Are we displaying the FCC structure?
bool dmndEnable;        // Are we displaying the Diamond (Zinc-blende) crystal lattice?
bool heuslerEnable;     // Are we displaying the Heusler Alloy crystal structure?
bool placeSpheres;      // Are we going to place the spheres instead of see them in correct positions?
bool pauseRotation;     // Check for paused rotation
bool blMouseLeftDown;   // Current State of the Left button 
bool blMouseCenterDown; // Current State of the Center button
bool blMouseRightDown;  // Current State of the Right button

GLfloat radius;                             // radius of the spheres being used
GLfloat locationX, locationY, locationZ;    // Current Location of the object
GLfloat rotationX, rotationY;               // Current rotation of the object

int objectRotation; // Rotation in degrees
int currentID;      // which structure is being selected for placing objects



GLsizei prevMouseX, prevMouseY; // Current mouse location in the window
GLsizei windowWidth = 640;      // set the window width
GLsizei windowHeight = 400;     // set the window height

Material ground;                // material for the ground displayed in scene
Material sky;                   // material for the sky displayed in scene
Material sphereMaterials[3];    // material for the spheres displayed in scene
GLUquadric *q;                  // used for designing spheres

Camera avatarPOV;               // add a class for camera movement
PlaceableSpheres spheres[3];    // add a class in order to control placing spheres

int main(int argc, char** argv)
{
    //initialization functions
    glutInit(&argc, argv);                              // Tell GLUT that I'm about to create a window
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);      // Set the window's initial width and height
    glutInitWindowPosition(50, 50);                     // Position the window initial top
    glutCreateWindow("Material Physics Research Project!!");             // Go ahead and create the window

    //Callback Functions
    glutDisplayFunc(&display);          // Set the display function to use 
    glutReshapeFunc(&reshape);          // Set the resize window function to use
    glutKeyboardFunc(&keyboardClick);   // Handle the keyboard
    glutSpecialFunc(&specialInput);     // Handle the arrow keys
    glutMouseFunc(&mouseClick);         // Handle the mouse clicks
    glutMotionFunc(&mouseMotion);       // Handle the mouse motion - callback for mouse movement
    glutTimerFunc(20, &timer, 20);      // redraw every 20ms (50 times per second) 

    ground.load("Textures/Concrete1.tga");
    sky.load("Textures/Sky1.tga");
    sphereMaterials[0].load("Textures/Wood1.tga");
    sphereMaterials[1].load("Textures/Marble1.tga");
    sphereMaterials[2].load("Textures/Ground3.tga");

    q = gluNewQuadric();                // Allocates the memory for a new quadric
    gluQuadricNormals(q, GLU_SMOOTH);   // Generate smooth normals for the quadric
    gluQuadricTexture(q, GL_TRUE);      // Enable Texture coords for the quadric 
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);  // Setup sphere mapping
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);  // Setup sphere mapping

    resetScene();
    glutMainLoop();                     // Start your engines
    return 0;
}

void resetScene()
{
    avatarPOV.reset();
    avatarPOV.setLocation(0.0f, 0.0f, -7.0f);
    avatarPOV.setRotation(0.0f, 0.0f, 1.0f);
    blEnableLights = false;
    cubicEnable = false;
    bccEnable = false;
    fccEnable = false;
    dmndEnable = false;
    heuslerEnable = false;
    pauseRotation = false;
    placeSpheres = false;
    spheres[0].reset();
    spheres[1].reset();
    spheres[2].reset(); 

    radius = 0.0f;
    locationX = 0.0;
    locationY = 0.0;
    rotationX = 0.0;
    rotationY = 0.0;
    objectRotation = 0;
    currentID = 0;
    prevMouseX = 0;
    prevMouseY = 0;
    blMouseLeftDown = false;        
    blMouseCenterDown = false;     
    blMouseRightDown = false; 
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // set the background color to black and opaque

    glClearDepth(1.0f);                     // Set the background to farthest away
    glEnable(GL_DEPTH_TEST);                // Enable depth test for z-culling
    glDepthFunc(GL_LEQUAL);                 // Set the depth to be in front of the background
    glShadeModel(GL_SMOOTH);                // Set to smooth shading (or flat!)
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Use the best perspective correction

    glFrontFace(GL_CCW);                    // Use the right-hand rule for the front face (normal) 
    reshape(windowWidth, windowHeight);
    glutPostRedisplay();
}

void enableLights()
{
    if(blEnableLights)
    {
        glEnable(GL_LIGHTING);          // enables lighting as user defines it
        glEnable(GL_COLOR_MATERIAL);    // any faces with color can be displayed

        GLfloat lightKa[] = {0.4f, 0.4f, 0.4f, 1.0f};   // ambient light - generic lighting
        GLfloat lightKd[] = {0.8f, 0.8f, 0.8f, 1.0f};   // diffuse light - spread out light from a source
        GLfloat lightKs[] = {0.4f, 0.4f, 0.4f, 1.0f};   // specular light - similar to the flashlight effect

        glLightfv(GL_LIGHT0, GL_AMBIENT, lightKa);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightKd);
        glLightfv(GL_LIGHT0, GL_SPECULAR, lightKs);

        GLfloat lightPos[] = {-2.5f, -1.0f, -9.0f, 1.0f};    // location of the light source
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
        glEnable(GL_LIGHT0);
    }
    else {
        glDisable(GL_LIGHTING);
    }
}

void reshape(GLsizei width, GLsizei height)
{
    if (height <= 0) height = 1;        // Sanity
    if (width <= 0) width = 1;          // Sanity
    windowWidth = width;
    windowHeight = height;

    avatarPOV.setupCamera(CAM_PROJ_PERSPECTIVE, windowWidth, windowHeight, 45.0f, 0.1f, 2000.0f);

    // Set the viewport to cover the entire window
    glViewport(0, 0, width, height);

    glutPostRedisplay();    
}  

void display(void)
{
    reshape(windowWidth, windowHeight);
    avatarPOV.runCamera();
    enableLights();
    char text[81];
    GLfloat textWidth = 0.0f;

    // Clear out the color and bufferbit 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // sets the color and use it to draw backdrop of virtual space
    glMatrixMode(GL_MODELVIEW);     // Go into model mode
    glEnable(GL_CULL_FACE);         // Draw or don't draw the back side
    glLoadIdentity();               // Reset stuff in the current mode

    // draw the base (ground) underneath
    glPushMatrix();
    GLfloat groundSize = 1000.0f;
    GLfloat groundHeight = -15.0f;
    GLfloat repeatNum = groundSize / 5.0f;
    ground.setupMaterial();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, repeatNum);
    glVertex3f(-groundSize/2.0f, groundHeight,  groundSize/2.0f);
    glTexCoord2f(repeatNum, repeatNum);
    glVertex3f( groundSize/2.0f, groundHeight,  groundSize/2.0f);
    glTexCoord2f(repeatNum, 0.0f);
    glVertex3f( groundSize/2.0f, groundHeight, -groundSize/2.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-groundSize/2.0f, groundHeight, -groundSize/2.0f);
    glEnd();
    ground.stopMaterial();
    glPopMatrix();

    // draw the sky
    glPushMatrix();
    gluQuadricOrientation(q, GLU_INSIDE);
    glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    sky.setupMaterial();
    gluSphere(q, groundSize/2.0, 10, 5);
    sky.stopMaterial();
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glPopMatrix();
    
    if(cubicEnable) 
    {
        // added to allow placement of cubic
        if(placeSpheres)
        {
            glPushMatrix();
            spheres[currentID-1].placeCubic(q, sphereMaterials, radius);
            glPopMatrix();

            // Now draw corner texts
            glPushMatrix();
            glMatrixMode(GL_PROJECTION);        // referencing the screen. Projection = screen = Rasta 
            glLoadIdentity();
            glViewport(0, 0, windowWidth, windowHeight);
            gluOrtho2D(0.0f, (GLfloat)windowWidth, 0.0f, (GLfloat)windowHeight);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glColor3f(1.0f, 1.0f, 1.0f);
            
            strcpy(text, "Placing the Simple Cubic Lattice");
            textWidth = getBitmapTextWidth(text, GLUT_BITMAP_TIMES_ROMAN_24);
            drawBitmapText(text, GLUT_BITMAP_TIMES_ROMAN_24, windowWidth-textWidth-6.0f, windowHeight-24.0f);
            glPopMatrix();
        } else {
            glPushMatrix();
            glRotatef(objectRotation, 0.0f, 1.0f, 0.0f);
            drawCubic(q, sphereMaterials, radius);
            glPopMatrix();
            
            // Now draw corner texts
            glPushMatrix();
            glMatrixMode(GL_PROJECTION);        // referencing the screen. Projection = screen = Rasta 
            glLoadIdentity();
            glViewport(0, 0, windowWidth, windowHeight);
            gluOrtho2D(0.0f, (GLfloat)windowWidth, 0.0f, (GLfloat)windowHeight);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glColor3f(1.0f, 1.0f, 1.0f);
            
            strcpy(text, "Simple Cubic Lattice Displayed");
            textWidth = getBitmapTextWidth(text, GLUT_BITMAP_TIMES_ROMAN_24);
            drawBitmapText(text, GLUT_BITMAP_TIMES_ROMAN_24, windowWidth-textWidth-6.0f, windowHeight-24.0f);
            glPopMatrix();
        }
    }

    if(bccEnable) 
    {
        // added to allow placement of bcc
        if(placeSpheres)
        {
            glPushMatrix();
            spheres[currentID-1].placeBCC(q, sphereMaterials, radius);
            glPopMatrix();

            // Now draw corner texts
            glPushMatrix();
            glMatrixMode(GL_PROJECTION);        // referencing the screen. Projection = screen = Rasta 
            glLoadIdentity();
            glViewport(0, 0, windowWidth, windowHeight);
            gluOrtho2D(0.0f, (GLfloat)windowWidth, 0.0f, (GLfloat)windowHeight);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glColor3f(1.0f, 1.0f, 1.0f);
            
            strcpy(text, "Placing the Body-Centered Cubic Lattice");
            textWidth = getBitmapTextWidth(text, GLUT_BITMAP_TIMES_ROMAN_24);
            drawBitmapText(text, GLUT_BITMAP_TIMES_ROMAN_24, windowWidth-textWidth-6.0f, windowHeight-24.0f);
            glPopMatrix();
        } else {
            glPushMatrix();
            glRotatef(objectRotation, 0.0f, 1.0f, 0.0f);
            drawBCC(q, sphereMaterials, radius);
            glPopMatrix();
            
            // Now draw corner texts
            glPushMatrix();
            glMatrixMode(GL_PROJECTION);        // referencing the screen. Projection = screen = Rasta 
            glLoadIdentity();
            glViewport(0, 0, windowWidth, windowHeight);
            gluOrtho2D(0.0f, (GLfloat)windowWidth, 0.0f, (GLfloat)windowHeight);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glColor3f(1.0f, 1.0f, 1.0f);
            
            strcpy(text, "Body-Centered Cubic Lattice Displayed");
            textWidth = getBitmapTextWidth(text, GLUT_BITMAP_TIMES_ROMAN_24);
            drawBitmapText(text, GLUT_BITMAP_TIMES_ROMAN_24, windowWidth-textWidth-6.0f, windowHeight-24.0f);
            glPopMatrix();
        }
        
    }

    if(fccEnable) 
    {
        // added to allow placement of fcc
        if(placeSpheres)
        {
            glPushMatrix();
            spheres[currentID-1].placeFCC(q, sphereMaterials, radius);
            glPopMatrix();

            // Now draw corner texts
            glPushMatrix();
            glMatrixMode(GL_PROJECTION);        // referencing the screen. Projection = screen = Rasta 
            glLoadIdentity();
            glViewport(0, 0, windowWidth, windowHeight);
            gluOrtho2D(0.0f, (GLfloat)windowWidth, 0.0f, (GLfloat)windowHeight);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glColor3f(1.0f, 1.0f, 1.0f);
            
            strcpy(text, "Placing the Face-Centered Cubic Lattice");
            textWidth = getBitmapTextWidth(text, GLUT_BITMAP_TIMES_ROMAN_24);
            drawBitmapText(text, GLUT_BITMAP_TIMES_ROMAN_24, windowWidth-textWidth-6.0f, windowHeight-24.0f);
            glPopMatrix();
        } else {
            glPushMatrix();
            glRotatef(objectRotation, 0.0f, 1.0f, 0.0f);
            drawFCC(q, sphereMaterials, radius);
            glPopMatrix();

            // Now draw corner texts
            glPushMatrix();
            glMatrixMode(GL_PROJECTION);        // referencing the screen. Projection = screen = Rasta 
            glLoadIdentity();
            glViewport(0, 0, windowWidth, windowHeight);
            gluOrtho2D(0.0f, (GLfloat)windowWidth, 0.0f, (GLfloat)windowHeight);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glColor3f(1.0f, 1.0f, 1.0f);
            
            strcpy(text, "Face-Centered Cubic Lattice Displayed");
            textWidth = getBitmapTextWidth(text, GLUT_BITMAP_TIMES_ROMAN_24);
            drawBitmapText(text, GLUT_BITMAP_TIMES_ROMAN_24, windowWidth-textWidth-6.0f, windowHeight-24.0f);
            glPopMatrix();
        }
    }

    if(dmndEnable) 
    {
        glPushMatrix();
        glRotatef(objectRotation, 0.0f, 1.0f, 0.0f);
        drawZnBlnd(q, sphereMaterials, radius);
        glPopMatrix();

        // Now draw corner texts
        glPushMatrix();
        glMatrixMode(GL_PROJECTION);        // referencing the screen. Projection = screen = Rasta 
        glLoadIdentity();
        glViewport(0, 0, windowWidth, windowHeight);
        gluOrtho2D(0.0f, (GLfloat)windowWidth, 0.0f, (GLfloat)windowHeight);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glColor3f(1.0f, 1.0f, 1.0f);
        
        strcpy(text, "Diamond (Zinc-blende) Lattice Displayed");
        textWidth = getBitmapTextWidth(text, GLUT_BITMAP_TIMES_ROMAN_24);
        drawBitmapText(text, GLUT_BITMAP_TIMES_ROMAN_24, windowWidth-textWidth-6.0f, windowHeight-24.0f);
        glPopMatrix();
    }

    if(heuslerEnable) 
    {
        glPushMatrix();
        glRotatef(objectRotation, 0.0f, 1.0f, 0.0f);
        glTranslatef(-2.0*radius, -2.0*radius, -2.0*radius);
        glTranslatef(0.0f, 1.5 * radius, 0.0f);
        drawHeusler(q, sphereMaterials, radius);
        glPopMatrix();
        
        // Now draw corner texts
        glPushMatrix();
        glMatrixMode(GL_PROJECTION);        // referencing the screen. Projection = screen = Rasta 
        glLoadIdentity();
        glViewport(0, 0, windowWidth, windowHeight);
        gluOrtho2D(0.0f, (GLfloat)windowWidth, 0.0f, (GLfloat)windowHeight);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glColor3f(1.0f, 1.0f, 1.0f);
        
        strcpy(text, "Heusler Alloy Displayed");
        textWidth = getBitmapTextWidth(text, GLUT_BITMAP_TIMES_ROMAN_24);
        drawBitmapText(text, GLUT_BITMAP_TIMES_ROMAN_24, windowWidth-textWidth-6.0f, windowHeight-24.0f);
        glPopMatrix();
    }
    
    glutSwapBuffers();    
} 

void keyboardClick(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 'q': case 'Q': case 27:
            exit(EXIT_SUCCESS);
            break;
        case 'L':
            blEnableLights = !blEnableLights;
            break; 
        case 'r': case 'R':
            resetScene();
            break;
        case 'w': case 'W':
            avatarPOV.moveForward(0.5f);
            break;
        case 's': case 'S':
            avatarPOV.moveBackward(0.5f);
            break;
        case 'a': case 'A':
            avatarPOV.strafeLeft(0.5f);
            break;
        case 'd': case 'D':
            avatarPOV.strafeRight(0.5f);
            break;
        case 'h': case 'H':
            avatarPOV.moveUp(0.1f);
            break;
        case 'n': case 'N':
            avatarPOV.moveDown(0.1f);
            break;
        case 'b': case 'B':
            avatarPOV.turnLeft();
            break;
        case 'm': case 'M':
            avatarPOV.turnRight();
            break;
        case 'u':
            spheres[currentID-1].movePosX(0.1f);
            break;
        case 'j':
            spheres[currentID-1].movePosX(-0.1f);
            break;
        case 'i':
            spheres[currentID-1].movePosY(0.1f);
            break;
        case 'k': 
            spheres[currentID-1].movePosY(-0.1);
            break;
        case 'o':
            spheres[currentID-1].movePosZ(0.1);
            break;
        case 'l':
            spheres[currentID-1].movePosZ(-0.1);
            break;
        case '1': // 1 will be used for the BCC structure
            cubicEnable = !cubicEnable;
            bccEnable = false;
            fccEnable = false;
            dmndEnable = false;
            heuslerEnable = false;
            placeSpheres = false;
            currentID = 1;
            radius = 0.5f;
            break;
        case '2': // 2 will be used for the BCC structure
            cubicEnable = false;
            bccEnable = !bccEnable;
            fccEnable = false;
            dmndEnable = false;
            heuslerEnable = false;
            placeSpheres = false;
            currentID = 2;
            radius = 0.5f;
            break;
        case '3': // 3 will be used for the FCC structure
            cubicEnable = false;
            bccEnable = false;
            fccEnable = !fccEnable;
            dmndEnable = false;
            heuslerEnable = false;
            placeSpheres = false;
            currentID = 3;
            radius = 0.5f;
            break;
        case '4': // 4 will be used for the Diamond structure
            cubicEnable = false;
            bccEnable = false;
            fccEnable = false;
            dmndEnable = !dmndEnable;
            heuslerEnable = false;
            placeSpheres = false;
            radius = 0.5f;
            break;
        case '5': // 5 will be used for the Diamond structure
            cubicEnable = false;
            bccEnable = false;
            fccEnable = false;
            dmndEnable = false;
            heuslerEnable = !heuslerEnable;
            placeSpheres = false;
            radius = 0.5f;
            break;
        case 'e':
            radius = 0.5f;
            placeSpheres = !placeSpheres;
            spheres[currentID].reset();
            break;
        case 'p': case 'P': // p is used to pause the rotation of the lattice structures to make better observations
            pauseRotation = !pauseRotation;
            break;
        case 'x':
            radius = radius + 0.1;
            if (radius > 5.0) radius = 5.0;
            break;
        case 'z':
            radius = radius - 0.1;
            if (radius < 0.1) radius = 0.1;
            break;
    }
    
    glutPostRedisplay();    // update at earliest convenience, call dispay function callback and redraw the glut shapes // basically asks it to redraw the screen
}  

void specialInput(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_UP:
            avatarPOV.moveForward(0.5f);
            break;
        case GLUT_KEY_DOWN:
            avatarPOV.moveBackward(0.5f);
            break;
        case GLUT_KEY_LEFT:
            avatarPOV.strafeLeft(0.5f);
            break;
        case GLUT_KEY_RIGHT:
            avatarPOV.strafeRight(0.5f);
            break;
    }
    glutPostRedisplay();
}


void mouseClick(int button, int state, int x, int y)
{
    prevMouseX = x;
    prevMouseY = y;

    // Left Click Test
    if(button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN) blMouseLeftDown = true;
        else blMouseLeftDown = false;
    }
    // Middle Button Test
    if(button == GLUT_MIDDLE_BUTTON)
    {
        if(state == GLUT_DOWN) blMouseCenterDown = true;
        else blMouseCenterDown = false;
    }
    
    // adding in scrolling for scaling of the unit cells
    if(button == 3)
    {
        if(placeSpheres == false)
        {
            radius = radius - 0.1;
            if (radius < 0.1) radius = 0.1;
        }
    }
    if(button == 4)
    {
        if(placeSpheres == false)
        {
            radius = radius + 0.1;
            if (radius > 5.0) radius = 5.0;
        }
    }
    
    // Right Button Test
    if(button == GLUT_RIGHT_BUTTON)
    {
        if(state == GLUT_DOWN) blMouseRightDown = true;
        else blMouseRightDown = false;
    }
    glutPostRedisplay();
}

void mouseMotion(int x, int y)
{
    if (blMouseLeftDown)
    {
        if(prevMouseX > x) avatarPOV.turnLeft(1.0f);  
        if(prevMouseX < x) avatarPOV.turnRight(1.0f);
        if(prevMouseY > y) avatarPOV.lookUp(1.0f);   
        if(prevMouseY < y) avatarPOV.lookDown(1.0f);   

        rotationX += (x-prevMouseX);
        rotationY -= (y-prevMouseY);
    }
    if (blMouseRightDown)
    {
        if(prevMouseX > x) avatarPOV.strafeLeft(0.3f);  
        if(prevMouseX < x) avatarPOV.strafeRight(0.3f);
        if(prevMouseY > y) avatarPOV.moveForward(0.3f);   
        if(prevMouseY < y) avatarPOV.moveBackward(0.3f);

    }
    
    prevMouseX = x;
    prevMouseY = y;
    
    glutPostRedisplay();    // Update the screen
}

void timer(int ms)
{
    if(!pauseRotation) objectRotation += 1;

    if (objectRotation >= 360) objectRotation = 0;

    glutTimerFunc(ms, &timer, ms);      // redraw every 20ms (50 times per second) 
    glutPostRedisplay();    
}