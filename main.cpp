#include <stdio.h>
#include <math.h>
#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

//Colors
GLfloat goldenrod[] = {0.855f,  0.647f,  0.125f, 1.0f};
//GLfloat goldenrod[] = {1.0f,  0.0f,  0.0f, 1.0f};
GLfloat saddlebrown[] = {0.545f,  0.271f,  0.075f, 1.0f};
GLfloat green[] = {0.0f, 0.502f, 0.0f};
GLfloat blue[] = {0.0f, 0.0f, 1.0f};
GLfloat red[] = {1.0f, 0.0f, 0.0f};
GLfloat orange[] = {1.0f, 0.65f, 0.0f};
GLfloat purple[] = {0.63f, 0.13f, 0.94f};
GLfloat cyan[] = {0.0f, 1.0f, 1.0f};

//Mouse Click variables
double prevX = 0.0;
double prevY = 0.0;
double deltaX = 0.0;
double deltaY = 0.0;

//Animation variables
int anim = 0;

//Light Source Position
GLfloat lightpos[] = {0.0, 10.0, 0.0, 0};

//Cube settings
float const cubeScaleX = 0.75;
float const cubeScaleY = 0.75;
float const cubeScaleZ = 0.75;

//Eave settings
float const eaveWidth = (cubeScaleY*2) * 0.1; /*Sets percentage of face eave should cover*/
float const eaveDepth = (cubeScaleZ*2) * 0.1; /*Sets percentage of cube depth eave should be*/

//Camera settings
float cameraAngle = 0.0;
float cameraPosX = 0.0;
float cameraPosY = 5.0;
float cameraPosZ = 15.0;
float const cameraLookAtX = 0.0;
float const cameraLookAtY = 0.0;
float const cameraLookAtZ = 0.0;
float const cameraIsUpX = 0.0;
float const cameraIsUpY = 1.0;
float const cameraIsUpZ = 0.0;

//Define PI
double const PI = 3.14159265358979;

//Utility functions
double degToRad( double degrees ) {
    
    double radians = degrees * (PI/180);
    
    return radians;
    
}

//Drawing Functions
void drawGrid(int size) {
    
    glLineWidth(3.0);
    glColor3f(0.0f, 0.0f, 1.0f);
    for(int i = -size; i <= size; i++)
    {
        glBegin(GL_LINES);
        glNormal3d(0.0, 1.0, 0.0);
        glVertex3f((float)i, 0, (float)-size);
        glVertex3f((float)i, 0, (float)size);
        glEnd();
        
        glBegin(GL_LINES);
        glNormal3d(0.0, 1.0, 0.0);
        glVertex3f((float)-size, 0, (float)i);
        glVertex3f((float)size, 0, (float)i);
        glEnd();
    }
    
}

void draw3DTriangle(void) {
    //Front triangle
    glBegin(GL_TRIANGLES);
    glNormal3d(0.0, 0.0, 1.0);
    //glColor3f(0.862, 0.078, 0.235); /*Crimson: rgb(220,20,60)*/
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(0.0, 1.0, 1.0);
    glEnd();
    
    //Back Triangle
    glBegin(GL_TRIANGLES);
    glNormal3d(0.0, 0.0, -1.0);
    //glColor3f(0.0, 0.392, 0.0); /*Darkgreen: rgb(0,100,0)*/
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(0.0, 1.0, -1.0);
    glEnd();
    
    //Right rectangle
    glBegin(GL_POLYGON);
    glNormal3d(0.5, 0.5, 0.0);
    //glColor3f(0.125, 0.698, 0.667); /*lightseagreen: rgb(32,178,170)*/
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(0.0, 1.0, -1.0);
    glVertex3f(0.0, 1.0, 1.0);
    glEnd();
    
    //Left rectangle
    glBegin(GL_POLYGON);
    glNormal3d(-0.5, -0.5, 0.0);
    //glColor3f(0.125, 0.698, 0.667); /*lightseagreen: rgb(32,178,170)*/
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(0.0, 1.0, -1.0);
    glVertex3f(0.0, 1.0, 1.0);
    glEnd();
    
    //Bottom rectangle
    glBegin(GL_POLYGON);
    glNormal3d(0.0, -1.0, 0.0);
    //glColor3f(0.125, 0.698, 0.667); /*lightseagreen: rgb(32,178,170)*/
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glEnd();

}

void drawCube() {
    
    //Front side
    glBegin(GL_POLYGON);
    glNormal3d(0.0, 0.0, 1.0);
    glVertex3f(  1, -1, 1 );
    glVertex3f(  1,  1, 1 );
    glVertex3f( -1,  1, 1 );
    glVertex3f( -1, -1, 1 );
    glEnd();

    //Back side
    glBegin(GL_POLYGON);
    glNormal3d(0.0, 0.0, -1.0);
    glVertex3f(  1, -1, -1 );
    glVertex3f(  1,  1, -1 );
    glVertex3f( -1,  1, -1 );
    glVertex3f( -1, -1, -1 );
    glEnd();

    //Right side
    glBegin(GL_POLYGON);
    glNormal3d(1.0, 0.0, 0.0);
    glVertex3f( 1, -1, -1 );
    glVertex3f( 1,  1, -1 );
    glVertex3f( 1,  1,  1 );
    glVertex3f( 1, -1,  1 );
    glEnd();
    
    //Left side
    glBegin(GL_POLYGON);
    glNormal3d(-1.0, 0.0, 0.0);
    glVertex3f( -1, -1,  1 );
    glVertex3f( -1,  1,  1 );
    glVertex3f( -1,  1, -1 );
    glVertex3f( -1, -1, -1 );
    glEnd();

    //Top side
    glBegin(GL_POLYGON);
    glNormal3d(0.0, 1.0, 0.0);
    glVertex3f(  1,  1,  1 );
    glVertex3f(  1,  1, -1 );
    glVertex3f( -1,  1, -1 );
    glVertex3f( -1,  1,  1 );
    glEnd();

    //Bottom side
    glBegin(GL_POLYGON);
    glNormal3d(0.0, -1.0, 0.0);
    glVertex3f(  1, -1, -1 );
    glVertex3f(  1, -1,  1 );
    glVertex3f( -1, -1,  1 );
    glVertex3f( -1, -1, -1 );
    glEnd();
    
}

void drawEavesOnFace() {
    
    //Top eave
    glPushMatrix();
    glTranslatef(0.0, cubeScaleY - (eaveWidth/2), cubeScaleZ + eaveDepth/2);
    glScalef(cubeScaleX + 0.05, eaveWidth, eaveDepth);
    drawCube();
    glPopMatrix();
    
    //Left eave
    glPushMatrix();
    glTranslatef(-cubeScaleX + eaveDepth/2, 0.0, cubeScaleZ + eaveDepth/2);
    glRotatef(90, 0.0, 0.0, 1);
    glScalef(cubeScaleX + 0.05, eaveWidth, eaveDepth);
    drawCube();
    glPopMatrix();
        
    //Bottom eave
    glPushMatrix();
    glTranslatef(0.0, -cubeScaleY + (eaveWidth/2), cubeScaleZ + eaveDepth/2);
    glScalef(cubeScaleX + 0.05, eaveWidth, eaveDepth);
    drawCube();
    glPopMatrix();
    
    //Right eave
    glPushMatrix();
    glTranslatef(cubeScaleX - (eaveWidth/2), 0.0, cubeScaleZ + eaveDepth/2);
    glRotatef(90, 0.0, 0.0, -1);
    glScalef(cubeScaleX + 0.05, eaveWidth, eaveDepth);
    drawCube();
    glPopMatrix();
    
}

void drawEavesOnCube() {
    //Front face
    drawEavesOnFace();
    
    //Top face
    glPushMatrix();
    glRotatef(90, -1.0, 0.0, 0.0);
    drawEavesOnFace();
    glPopMatrix();
    
    //Back face
    glPushMatrix();
    glRotatef(180, -1, 0.0, 0.0);
    drawEavesOnFace();
    glPopMatrix();
    
    //Bottom face
    glPushMatrix();
    glRotatef(90, 1, 0.0, 0.0);
    drawEavesOnFace();
    glPopMatrix();
    
    //Left face
    glPushMatrix();
    glRotatef(90, 0.0, -1, 0.0);
    drawEavesOnFace();
    glPopMatrix();
    
    //Right face
    glPushMatrix();
    glRotatef(90, 0.0, 1, 0.0);
    drawEavesOnFace();
    glPopMatrix();
}

void draw3Dcircle(double innerRad, double outerRad, double depth, double beginAngle, double endAngle) {
    
    //Front face
    glBegin(GL_TRIANGLE_STRIP);
    glNormal3d(0.0, 0.0, 1.0);
    glVertex3d(cos(degToRad(beginAngle)) * innerRad, sin(degToRad(beginAngle)) * innerRad, 0.0);
    
    for(int i = beginAngle+1; i <= endAngle+1; i+=2)
    {
        
        glVertex3d(cos(degToRad(i)) * outerRad, (float)sin(degToRad(i)) * outerRad, 0.0);
        glVertex3d(cos(degToRad(i+1)) * innerRad, (float)sin(degToRad(i+1)) * innerRad, 0.0);
        
    }
    glEnd();
    
    //Back face
    glBegin(GL_TRIANGLE_STRIP);
    glNormal3d(0.0, 0.0, -1.0);
    glVertex3d(cos(degToRad(beginAngle)) * innerRad, sin(degToRad(beginAngle)) * innerRad, 0.0-depth);
    
    for(int i = beginAngle+1; i <= endAngle+1; i+=2)
    {
        
        glVertex3d(cos(degToRad(i)) * outerRad, (float)sin(degToRad(i)) * outerRad, 0.0-depth);
        glVertex3d(cos(degToRad(i+1)) * innerRad, (float)sin(degToRad(i+1)) * innerRad, 0.0-depth);
        
    }
    glEnd();
    
    //Connecting front and back face
    glBegin(GL_TRIANGLE_STRIP);
    glNormal3d(0.0, 1.0, 0.0);
    glVertex3d(cos(degToRad(beginAngle)) * innerRad, sin(degToRad(beginAngle)) * innerRad, 0.0);
    
    for(int i = beginAngle+1; i <= endAngle+1; i+=2)
    {
        
        glVertex3d(cos(degToRad(i)) * outerRad, (float)sin(degToRad(i)) * outerRad, 0.0-depth);
        glVertex3d(cos(degToRad(i+1)) * outerRad, (float)sin(degToRad(i+1)) * outerRad, 0.0);
        
    }
    glEnd();
    
}

void drawZero() {
    glPushMatrix();
    
    glScaled(1.0, 1.25, 1.0);
    glTranslated(0.0, 1.0 + 0.4, 0.0);
    draw3Dcircle(1.0, 1.4, 0.3, 0.0, 360);
    
    glPopMatrix();
}

void drawOne() {
    glPushMatrix();
    
    glScaled(3.0, 3.0, 1.0);

    glPushMatrix();
    glTranslated(-0.1, 0.6, 0.0);
    glRotated(45, 0.0, 0.0, 1.0);
    glScaled(0.2, 0.075, 0.125);
    glTranslated(0.0, 1.0, 0.0);
    drawCube();
    glPopMatrix();
    
    
    glPushMatrix();
    glTranslated(0.125, 0.5, 0.0);
    glRotated(90, 0.0, 0.0, 1.0);
    glScaled(0.3, 0.125, 0.125);
    glTranslated(0.0, 1.0, 0.0);
    drawCube();
    glPopMatrix();
    
    glPushMatrix();
    glScaled(0.33, 0.1, 0.125);
    glTranslated(0.0, 1.0, 0.0);
    drawCube();
    glPopMatrix();
    
    glPopMatrix();
}

void drawTwo() {
    glPushMatrix();
    
    glPushMatrix();
    glScaled(1.0, 1.25, 1.0);
    glTranslated(-1.0, 1.2, 0.12);
    glRotated(90, 0.0, 0.0, -1.0);
    draw3Dcircle(1.0, 1.2, 0.3, 0, 210);
    glPopMatrix();
    
    glPushMatrix();
    glScaled(1.0, 0.125, 0.125);
    glTranslated(0.0, 1.0, 0.0);
    drawCube();
    glPopMatrix();
    
    glPopMatrix();
}

void drawThree() {
    glPushMatrix();
    
    glPushMatrix();
    glTranslated(0.0, 3.4, 0.0);
    glRotated(90, 0.0, 0.0, -1.0);
    draw3Dcircle(1.0, 1.2, 0.2, 0.0, 180.0);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(0.0, 1.2, 0.0);
    glRotated(90, 0.0, 0.0, -1.0);
    draw3Dcircle(1.0, 1.2, 0.2, 0.0, 180.0);
    glPopMatrix();
    
    glPopMatrix();
}

void drawFour() {
    glPushMatrix();
    
    glPushMatrix();
    glTranslated(0.5, 0.0, 0.0);
    glScaled(0.2, 1.5, 0.2);
    glTranslated(0.0, 1.0, 0.0);
    drawCube();
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(0.0, 1.0, 0.0);
    glScaled(1.0, 0.2, 0.2);
    glTranslated(0.0, 1.0, 0.0);
    drawCube();
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(0.0, 2.0, 0.0);
    glRotated(45, 0.0, 0.0, 1.0);
    glScaled(1.0, 0.2, 0.2);
    glTranslated(0.0, 1.0, 0.0);
    drawCube();
    glPopMatrix();


    glPopMatrix();
}

void drawFive() {
    glPushMatrix();
    
    glScaled(1.0, 0.75, 1.0);
    glTranslated(0.0, 1.2, 0.0);
    
    glPushMatrix();
    glRotated(90, 0.0, 0.0, -1.0);
    draw3Dcircle(1.0, 1.2, 0.3, 0, 180);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(0.0, 2.0, 0.0);
    glRotated(90, 0.0, 0.0, 1.0);
    glTranslated(0.0, 0.0, -0.15);
    glScaled(1.0, 0.1, 0.15);
    drawCube();
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(0.5, 3.0, -0.15);
    glScaled(0.6, 0.1, 0.15);
    drawCube();
    glPopMatrix();

    glPopMatrix();
}

void drawSix() {
    glPushMatrix();
    
    glPushMatrix();
    glTranslated(0.0, 2.8, -0.1);
    glRotated(45, 0.0, 0.0, 1.0);
    glScaled(1.5, 0.15, 0.105);
    drawCube();
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(0.0, 1.2, 0.0);
    draw3Dcircle(1.0, 1.2, 0.2, 0, 360);
    glPopMatrix();
    
    glPopMatrix();
}

void drawSeven() {
    glPushMatrix();
    
    glPushMatrix();
    glTranslated(0.0, 2.25, 0.0);
    glScaled(1.0, 0.2, 0.2);
    drawCube();
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(0.2, 1.25, 0.0);
    glRotated(60, 0.0, 0.0, 1.0);
    glScaled(1.25, 0.2, 0.2);
    drawCube();
    glPopMatrix();

    glPopMatrix();
}

void drawEight() {
    glPushMatrix();
    
    glTranslated(0.0, 1.2, 0.0);
    
    glPushMatrix();
    glTranslated(0.0, 2.2, 0.0);
    draw3Dcircle(1.0, 1.2, 0.2, 0, 360);
    glPopMatrix();
    
    glPushMatrix();
    draw3Dcircle(1.0, 1.2, 0.2, 0, 360);
    glPopMatrix();

    glPopMatrix();
}

void drawNine() {
    glPushMatrix();
    
    glPushMatrix();
    glScaled(0.75, 0.75, 1.0);
    glTranslated(0.0, 3.2, 0.0);
    draw3Dcircle(1.0, 1.2, 0.2, 0, 360);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(0.0, 1.0, -0.1);
    glRotated(50, 0.0, 0.0, 1.0);
    glScaled(1.25, 0.1, 0.075);
    drawCube();
    glPopMatrix();
    
    glPopMatrix();
}

void drawUppercaseC() {
    glPushMatrix();
    
    glTranslated(0.0, 1.2, 0.0);
    glRotated(60, 0.0, 0.0, 1.0);
    draw3Dcircle(1.0, 1.2, 0.2, 0, 240);
    
    glPopMatrix();
}

void drawUppercaseE() {
    glPushMatrix();
    
    glTranslated(0.0, 1.5, 0.0);
    
    glPushMatrix();
    glTranslated(-0.5, 0.0, 0.0);
    glRotated(90, 0.0, 0.0, 1.0);
    glScaled(1.5, 0.1, 0.1);
    glTranslated(0.0, 1.0, 0.0);
    drawCube();
    glPopMatrix();
    
    glPushMatrix();
    glScaled(0.5, 0.1, 0.1);
    drawCube();
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(0.0, 1.4, 0.0);
    glScaled(0.5, 0.1, 0.1);
    drawCube();
    glPopMatrix();

    glPushMatrix();
    glTranslated(0.0, -1.4, 0.0);
    glScaled(0.5, 0.1, 0.1);
    drawCube();
    glPopMatrix();

    glPopMatrix();
}

void drawUppercaseT() {
    glPushMatrix();
    
    glTranslated(0.0, 1.5, 0.0);
    
    glPushMatrix();
    glTranslated(0.0, 1.5, 0.0);
    glScaled(0.75, 0.1, 0.1);
    drawCube();
    glPopMatrix();
    
    glPushMatrix();
    glRotated(90, 0.0, 0.0, 1.0);
    glScaled(1.5, 0.1, 0.1);
    drawCube();
    glPopMatrix();
    
    glPopMatrix();
}

void drawUppercaseX() {
    glPushMatrix();
    
    glTranslated(0.0, 1.25, 0.0);
    
    glPushMatrix();
    glRotated(45, 0.0, 0.0, 1.0);
    glScaled(1.5, 0.1, 0.1);
    drawCube();
    glPopMatrix();
    
    glPushMatrix();
    glRotated(45, 0.0, 0.0, -1.0);
    glScaled(1.5, 0.1, 0.1);
    drawCube();
    glPopMatrix();

    glPopMatrix();
}

void drawUppercaseZ() {
    glPushMatrix();
    
    glTranslated(0.0, 0.1, 0.0);
    
    glPushMatrix();
    glScaled(0.75, 0.1, 0.1);
    drawCube();
    glPopMatrix();
   
    glPushMatrix();
    glTranslated(0.0, 0.75, 0.0);
    glRotated(45, 0.0, 0.0, 1.0);
    glScaled(1.0, 0.1, 0.1);
    drawCube();
    glPopMatrix();

    glPushMatrix();
    glScaled(0.75, 1.0, 1.0);
    glTranslated(0.0, 1.41, 0.0);
    glScaled(1.0, 0.1, 0.1);
    drawCube();
    glPopMatrix();

    glPopMatrix();
}

void drawCube1() {
    glPushMatrix();
    
    glTranslated(3.0, 0.0 + eaveWidth*2, -1.0);
    glRotated(45 + anim, 0.0, -1.0, 0.0);
    glRotated(45 + anim, 1.0, 0.0, 0.0);
    
    //Draw cube
    glColor3d(0.855, 0.647, 0.125);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, goldenrod);
    glTranslated(0.0, cubeScaleY, 0.0);
    glPushMatrix();
    glScalef(cubeScaleX, cubeScaleY, cubeScaleZ);
    drawCube();
    glPopMatrix();
    
    //Draw eaves on each face
    glColor3d(0.545, 0.271, 0.075);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, saddlebrown);
    drawEavesOnCube();
    
    //Draw shapes and number on faces
    glColor3d(0.0, 0.502, 0.0);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, green);

    //One on front face
    glPushMatrix();
    glTranslated(0.0, -0.3, -0.2);
    glScaled(0.3, 0.3, 1.0);
    glTranslated(0.0, 0.0, 1.0);
    drawOne();
    glPopMatrix();
    
    //Triangle on back face
    glPushMatrix();
    glScaled(0.4, 0.4, 0.25);
    glTranslated(0.0, 0.0, -2.5);
    draw3DTriangle();
    glPopMatrix();
    
    //Three on right face
    glPushMatrix();
    glRotated(90, 0.0, 1.0, 0.0);
    glTranslated(0.0, -0.5, 1.0);
    glScaled(0.2, 0.2, 1.0);
    drawThree();
    glPopMatrix();
    
    //Cube on left face
    glPushMatrix();
    glRotated(90, 0.0, -1.0, 0.0);
    glTranslated(0.0, 0.0, 0.8);
    glScaled(0.3, 0.3, 0.2);
    drawCube();
    glPopMatrix();
    
    //E on top face
    glPushMatrix();
    glRotated(90, -1.0, 0.0, 0.0);
    glTranslated(0.0, -0.5, 0.8);
    glScaled(0.3, 0.3, 1.0);
    drawUppercaseE();
    glPopMatrix();
    
    //T on bottom face
    glPushMatrix();
    glRotated(90, 1.0, 0.0, 0.0);
    glTranslated(0.0, -0.5, 0.8);
    glScaled(0.3, 0.3, 1.0);
    drawUppercaseT();
    glPopMatrix();
    
    glPopMatrix();
}

void drawCube2() {
    glPushMatrix();
    
    glTranslated(5.0, 0.0 + eaveWidth*2, 3.0);
    glRotated(45 - anim, 0.0, -1.0, 0.0);
    
    //Draw cube
    glColor3d(0.855, 0.647, 0.125);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, goldenrod);
    glTranslated(0.0, cubeScaleY, 0.0);
    glPushMatrix();
    glScalef(cubeScaleX, cubeScaleY, cubeScaleZ);
    drawCube();
    glPopMatrix();
    
    //Draw eaves on each face
    glColor3d(0.545, 0.271, 0.075);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, saddlebrown);
    drawEavesOnCube();
    
    //Draw shapes and numbers on faces
    glColor3d(0.0, 0.0, 1.0);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);

    //Two on front face
    glPushMatrix();
    glTranslated(0.0, -0.25, 1.0);
    glScaled(0.25, 0.25, 1.0);
    drawTwo();
    glPopMatrix();
    
    //7 on bottom face
    glPushMatrix();
    glRotated(180, 0.0, 1.0, 0.0);
    glTranslated(0.0, -0.35, 0.7);
    glScaled(0.25, 0.25, 1.0);
    drawSeven();
    glPopMatrix();
    
    //X on right face
    glPushMatrix();
    glRotated(90, 0.0, 1.0, 0.0);
    glTranslated(0.0, -0.25, 0.8);
    glScaled(0.25, 0.25, 1.0);
    drawUppercaseX();
    glPopMatrix();
    
    //6 on left face
    glPushMatrix();
    glRotated(90, 0.0, -1.0, 0.0);
    glTranslated(0.0, -0.4, 0.8);
    glScaled(0.2, 0.2, 1.0);
    drawSix();
    glPopMatrix();
    
    //Z on top face
    glPushMatrix();
    glRotated(90, -1.0, 0.0, 0.0);
    glTranslated(0.0, -0.2, 0.8);
    glScaled(0.3, 0.3, 1.0);
    drawUppercaseZ();
    glPopMatrix();
    
    //Four on bottom face
    glPushMatrix();
    glRotated(90, 1.0, 0.0, 0.0);
    glTranslated(0.0, -0.2, 0.7);
    glScaled(0.2, 0.2, 1.0);
    drawFour();
    glPopMatrix();
    
    glPopMatrix();
}

void drawCube3() {
    glPushMatrix();
    
    glTranslated(-3.0, 0.0 + eaveWidth*2, 1.0);
    glRotated(45 + anim, 0.0, -1.0, 0.0);
    
    //Draw cube
    glColor3d(0.855, 0.647, 0.125);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, goldenrod);
    glTranslated(0.0, cubeScaleY, 0.0);
    glPushMatrix();
    glScalef(cubeScaleX, cubeScaleY, cubeScaleZ);
    drawCube();
    glPopMatrix();
    
    //Draw eaves on each face
    glColor3d(0.545, 0.271, 0.075);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, saddlebrown);
    drawEavesOnCube();
    
    //Draw shapes and numbers on on faces
    glColor3d(1.0, 0.0, 0.0);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
    
    //3 on front face
    glPushMatrix();
    glTranslated(0.0, -0.45, 1.0);
    glScaled(0.2, 0.2, 1.0);
    drawThree();
    glPopMatrix();
    
    //C on back face
    glPushMatrix();
    glRotated(180, 0.0, 1.0, 0.0);
    glTranslated(0.0, -0.4, 0.8);
    glScaled(0.3, 0.3, 1.0);
    drawUppercaseC();
    glPopMatrix();
    
    //8 on right face
    glPushMatrix();
    glRotated(90, 0.0, 1.0, 0.0);
    glTranslated(0.0, -0.5, 0.8);
    glScaled(0.2, 0.2, 1.0);
    drawEight();
    glPopMatrix();
    
    //9 on left face
    glPushMatrix();
    glRotated(90, 0.0, -1.0, 0.0);
    glTranslated(0.0, -0.5, 0.8);
    glScaled(0.3, 0.3, 1.0);
    drawNine();
    glPopMatrix();
    
    //T on top face
    glPushMatrix();
    glRotated(90, -1.0, 0.0, 0.0);
    glTranslated(0.0, -0.3, 0.8);
    glScaled(0.2, 0.2, 1.0);
    drawUppercaseT();
    glPopMatrix();
    
    //6 on bottom face
    glPushMatrix();
    glRotated(90, 1.0, 0.0, 0.0);
    glTranslated(0.0, -0.4, 0.8);
    glScaled(0.2, 0.2, 1.0);
    drawSix();
    glPopMatrix();
    
    glPopMatrix();
}

void drawCube4() {
    glPushMatrix();
    
    glTranslated(0.0, 0.0 + eaveWidth*2, -4.0);
    glRotated(30 + anim, 0.0, 1.0, 0.0);
    
    //Draw cube
    glColor3d(0.855, 0.647, 0.125);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, goldenrod);
    glTranslated(0.0, cubeScaleY, 0.0);
    glPushMatrix();
    glScalef(cubeScaleX, cubeScaleY, cubeScaleZ);
    drawCube();
    glPopMatrix();
    
    //Draw eaves on each face
    glColor3d(0.545, 0.271, 0.075);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, saddlebrown);
    drawEavesOnCube();
    
    //Draw shapes and numbers on faces
    glColor3d(1.0, 0.65, 0.0);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, orange);
    
    //Four on front face
    glPushMatrix();
    glTranslated(0.0, -0.5, 0.8);
    glScaled(0.3, 0.3, 1.0);
    drawFour();
    glPopMatrix();
    
    //T on back face
    glPushMatrix();
    glRotated(180, 0.0, 1.0, 0.0);
    glTranslated(0.0, -0.3, 0.8);
    glScaled(0.2, 0.2, 1.0);
    drawUppercaseT();
    glPopMatrix();
    
    //7 on right face
    glPushMatrix();
    glRotated(90, 0.0, 1.0, 0.0);
    glTranslated(0.0, -0.35, 0.7);
    glScaled(0.25, 0.25, 1.0);
    drawSeven();
    glPopMatrix();

    //X on left face
    glPushMatrix();
    glRotated(90, 0.0, -1.0, 0.0);
    glTranslated(0.0, -0.25, 0.8);
    glScaled(0.25, 0.25, 1.0);
    drawUppercaseX();
    glPopMatrix();

    //8 on top face
    glPushMatrix();
    glRotated(90, -1.0, 0.0, 0.0);
    glTranslated(0.0, -0.5, 0.8);
    glScaled(0.2, 0.2, 1.0);
    drawEight();
    glPopMatrix();

    //1 on bottom face
    glPushMatrix();
    glRotated(90, 1.0, 0.0, 0.0);
    glTranslated(0.0, -0.3, -0.2);
    glScaled(0.3, 0.3, 1.0);
    glTranslated(0.0, 0.0, 1.0);
    drawOne();
    glPopMatrix();

    glPopMatrix();
}

void drawCube5() {
    glPushMatrix();
    
    glTranslated(0.0, 0.0 + eaveWidth*2, 5.0);
    glRotated(25 + anim*3, 1.0, 0.0, 0.0);
    
    //Draw cube
    glColor3d(0.855, 0.647, 0.125);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, goldenrod);
    glTranslated(0.0, cubeScaleY, 0.0);
    glPushMatrix();
    glScalef(cubeScaleX, cubeScaleY, cubeScaleZ);
    drawCube();
    glPopMatrix();
    
    //Draw eaves on each face
    glColor3d(0.545, 0.271, 0.075);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, saddlebrown);
    drawEavesOnCube();
    
    //Draw shapes and numbers on faces
    glColor3d(0.63, 0.13, 0.94);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, orange);
    
    //5 on front face
    glPushMatrix();
    glTranslated(-0.1, -0.5, 0.8);
    glScaled(0.3, 0.3, 1.0);
    drawFive();
    glPopMatrix();
    
    //2 on back face
    glPushMatrix();
    glRotated(180, 0.0, 1.0, 0.0);
    glTranslated(0.0, -0.25, 1.0);
    glScaled(0.25, 0.25, 1.0);
    drawTwo();
    glPopMatrix();
    
    //X on right face
    glPushMatrix();
    glRotated(90, 0.0, 1.0, 0.0);
    glTranslated(0.0, -0.25, 0.8);
    glScaled(0.25, 0.25, 1.0);
    drawUppercaseX();
    glPopMatrix();

    //3 on left face
    glPushMatrix();
    glRotated(90, 0.0, -1.0, 0.0);
    glTranslated(0.0, -0.45, 1.0);
    glScaled(0.2, 0.2, 1.0);
    drawThree();
    glPopMatrix();

    //Triangle on top face
    glPushMatrix();
    glRotated(90, -1.0, 0.0, 0.0);
    glTranslated(0.0, 0.0, 0.8);
    glScaled(0.4, 0.4, 0.2);
    draw3DTriangle();
    glPopMatrix();

    //C on bottom face
    glPushMatrix();
    glRotated(90, 1.0, 0.0, 0.0);
    glTranslated(0.0, -0.4, 0.8);
    glScaled(0.3, 0.3, 1.0);
    drawUppercaseC();
    glPopMatrix();

    glPopMatrix();
}

void drawNumbers() {
    glPushMatrix();
    glColor3d(0.0, 1.0, 1.0);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, cyan);
    
    glPushMatrix();
    glTranslated(-18.0, 0.0, -10.0);
    glRotated(anim, 0.0, 1.0, 0.0);
    drawZero();
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(anim*0.05, 0.0, anim*0.05);
    glTranslated(-14.0, 0.0, -10.0);
    glScaled(1.5, 1.5, 1.0);
    drawOne();
    glPopMatrix();

    glPushMatrix();
    glTranslated(anim*0.01, anim*0.01, anim*0.01);
    glTranslated(-10.0, 0.0, -10.0);
    glScaled(1.3, 1.3, 1.0);
    drawTwo();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-6.0, 0.0, -10.0);
    glScaled(1.0, 0.8, 1.0);
    glRotated(-anim, 1.0, 0.0, 0.0);
    drawThree();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-2.0, 0.0, -10.0 - anim*0.05);
    glScaled(1.25, 1.25, 1.0);
    drawFour();
    glPopMatrix();

    glPushMatrix();
    glTranslated(2.0, 0.0, -10.0);
    glScaled(1.1, 1.1, 1.0);
    glRotated(-anim, -1.0, 0.0, 0.0);
    drawFive();
    glPopMatrix();

    glPushMatrix();
    glTranslated(6.0-anim*0.01, 0.0+anim*0.01, -10.0+anim*0.01);
    glScaled(0.9, 0.9, 1.0);
    drawSix();
    glPopMatrix();

    glPushMatrix();
    glTranslated(10.0-anim*0.05, 0.0, -10.0);
    glScaled(1.0, 1.3, 1.0);
    drawSeven();
    glPopMatrix();

    glPushMatrix();
    glTranslated(14.0-anim*0.05, 0.0, -10.0+anim*0.03);
    glScaled(1.0, 0.75, 1.0);
    drawEight();
    glPopMatrix();

    glPushMatrix();
    glTranslated(18.0-anim*0.03, 0.0+anim*0.01, -10.0+anim*0.03);
    drawNine();
    glPopMatrix();

    glPopMatrix();
}

/*void drawFace(int face) {
    
    glPushMatrix();
    
    if(face == 0) {
        glTranslatef(0.0, 0.0, cubeScaleZ);
        glScalef(faceShapeScaleX, faceShapeScaleY, faceShapeScaleZ);
        draw3DTriangle();
    }
    
    else if(face == 1) {
        glTranslatef(0.0, 0.0, cubeScaleZ);
        glScalef(faceShapeScaleX, faceShapeScaleY, faceShapeScaleZ);
        drawCube(2);
    }
    
    glPopMatrix();

}*/
                                 
//Display Function
void display(void){
    
    //For animation
    anim++;
    
    //Clear screen and Z-buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //Set matrix mode
    glMatrixMode(GL_MODELVIEW);
    
    //Reset transformations
    glLoadIdentity();
    
    //Set camera
    gluLookAt(cameraPosX, cameraPosY, cameraPosZ,
              cameraLookAtX, cameraLookAtY, cameraLookAtZ,
              cameraIsUpX, cameraIsUpY,  cameraIsUpZ);
    
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    
    //Draw grid
    drawGrid(25);
    
   //Draw all cubes
    drawCube1();
    drawCube2();
    drawCube3();
    drawCube4();
    drawCube5();
    
    //Draw numbers in scene
    drawNumbers();
    
    glFlush();
    glutSwapBuffers();
    
}

//Callback functions

//Function is taken from the following source:
//http://www.lighthouse3d.com/tutorials/glut-tutorial/preparing-the-window-for-a-reshape/
void reshape(int w, int h) {
    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if(h == 0)
        h = 1;
    float ratio = 1.0* w / h;
    
    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);
    
    // Reset Matrix
    glLoadIdentity();
    
    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);
    
    // Set the correct perspective.
    gluPerspective(60,ratio,1,60);
    
    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);

}

void keyCB(unsigned char key, int x, int y) {
    if (key == 'q')
        exit(0);
}

void mouse_click(int button, int state, int x, int y) {

    if(button == GLUT_LEFT_BUTTON) {
        prevX = x;
        prevY = y;
    }
    
}

void mouse_drag(int x, int y) {

    deltaX = (x - prevX) * 0.05;
    deltaY = (y - prevY) * 0.05;
    
    cameraPosX -= deltaX;
    cameraPosY += deltaY;
    
    prevX = x;
    prevY = y;
    
}

// ----------------------------------------------------------
// main() function
// ----------------------------------------------------------
int main(int argc, char* argv[]){
    
    // init GLUT and create Window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(1024,1024);
    glutCreateWindow("Homework 2 - Ishjot Walia");
    
    glClearDepth(1);
    //Hide hidden surfaces
    glEnable(GL_DEPTH_TEST);
    //Turn on anti aliasing
    glEnable( GL_MULTISAMPLE );
    //Turn on lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    
    //Turn on colors
    glEnable(GL_COLOR_MATERIAL);
    //glClearColor(1.0f, 1.0f, 1.0f, 0.0f);	// White Background
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);   // Black Background
    
    // Callback functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(display);
    glutMotionFunc(mouse_drag);
    glutMouseFunc(mouse_click);
    glutKeyboardFunc(keyCB);
    
    glutMainLoop();
    
    return 0;
    
}
