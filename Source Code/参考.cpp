#include <iostream>
#include <cstdlib>
#include <fstream>
#include <GL/glut.h>
#include "misc.h"

using namespace std;

#define NAME  "ComputerGraphic Hw3_Ex2"

#define X_AXIS  0
#define Y_AXIS  1
#define Z_AXIS  2

#define MAP_WIDTH 48
#define MAP_HEIGHT 26
#define GRID_SIZE 20
#define MARGIN_BOTTOM 20
GLsizei winW = MAP_WIDTH*GRID_SIZE; 
GLsizei winH = MAP_HEIGHT*GRID_SIZE+MARGIN_BOTTOM+10;

//Mouse Varizbles
typedef float vec3_t[3]; 
enum {
    UP = 1, 
    DOWN, 
};

static float Xangle = 90.0, Yangle = 0.0, Zangle = 0.0; 
int mouseOldX = -13;
int mouseOldY = -13;
int mState = UP;
int axisRot = X_AXIS;
float rotate = 0.0f;
vec3_t gRot = {0,0,0};

GLfloat camera = -10.0; //Translate distance for camera

float points[4][3] = { \
    {0, 0, 0},{0, 0, 0}, {0, 0, 0},{0, 0, 0}};
Texture texBrick;
Texture texFloor;

void resize (int w, int h)
{
	winW = w;
	winH = h;

    glViewport(0, 0, winW, winH);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)winW / (double)winH, 1, 800.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void setup() 
{
     glEnable(GL_DEPTH_TEST);
     glClearColor(1.0, 1.0, 1.0, 0.0);
	 glColor3f(0.0,0.0,0.0);

	 glDisable(GL_TEXTURE_2D);
     glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL); //只考慮Texture 顏色
     texBrick.Load("Textures//brick.ppm");
     texFloor.Load("Textures//floor.ppm");
}

void drawScene()
{
	glViewport(0,0,winW,winH);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef (0.0,0.0, camera);

	// Rotate scene.
    glRotatef (Zangle, 0.0, 0.0, 1.0);
    glRotatef (Yangle, 0.0, 1.0, 0.0);
    glRotatef (Xangle, 1.0, 0.0, 0.0);
    glRotatef (gRot[0], 1.0, 0.0, 0.0);
    glRotatef (gRot[1], 0.0, 1.0, 0.0);

	//地板
	glPushAttrib(GL_ENABLE_BIT);
       glEnable(GL_TEXTURE_2D);
       glBindTexture( GL_TEXTURE_2D, texFloor.id);
		   glBegin(GL_QUADS);
			   glTexCoord2f(0, 0); glVertex3f(1.0,1.0,-1.0);
			   glTexCoord2f(1, 0); glVertex3f(-1.0f, 1.0f, -1.0f);
			   glTexCoord2f(1, 1); glVertex3f(-1.0f, 1.0f,  1.0f);
			   glTexCoord2f(0, 1); glVertex3f(1.0f, 1.0f,  1.0f);
		   glEnd();
	glPopAttrib();

	//磚牆
	glPushAttrib(GL_ENABLE_BIT);
       glEnable(GL_TEXTURE_2D);
       glBindTexture( GL_TEXTURE_2D, texBrick.id);
		   glBegin(GL_QUADS);
			   glTexCoord2f(0, 0); glVertex3f(1.0,-1.0,-1.0);
			   glTexCoord2f(1, 0); glVertex3f(-1.0f, -1.0f, -1.0f);
			   glTexCoord2f(1, 1); glVertex3f(-1.0f, 1.0f,  -1.0f);
			   glTexCoord2f(0, 1); glVertex3f(1.0f, 1.0f,  -1.0f);
		   glEnd();
	glPopAttrib();

	glBegin(GL_QUADS);          
      glColor3f(1.0f, 0.5f, 0.0f);     // Orange
      glVertex3f( 1.0f, -1.0f,  1.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f( 1.0f, -1.0f, -1.0f);
 
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f( 1.0f,  1.0f, 1.0f);
      glVertex3f(-1.0f,  1.0f, 1.0f);
      glVertex3f(-1.0f, -1.0f, 1.0f);
      glVertex3f( 1.0f, -1.0f, 1.0f);
 
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(-1.0f,  1.0f,  1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);
 
      glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
      glVertex3f(1.0f,  1.0f, -1.0f);
      glVertex3f(1.0f,  1.0f,  1.0f);
      glVertex3f(1.0f, -1.0f,  1.0f);
      glVertex3f(1.0f, -1.0f, -1.0f);
   glEnd();  

	glutPostRedisplay();
    glutSwapBuffers();
}

void clamp (vec3_t v)
{
    int i;

    for (i = 0; i < 3; i ++)
        if (v[i] > 360 || v[i] < -360)
            v[i] = 0.0f;
}

void motion(int x, int y) 
{
    if (mState == DOWN) 
    {
		gRot[0] -= mouseOldY - y;
        gRot[1] -= mouseOldX - x;
        //gRot[0] -= ((mouseOldY - y) * 180.0f) / 100.0f;
        //gRot[1] -= ((mouseOldX - x) * 180.0f) / 100.0f;
        clamp (gRot);
        glutPostRedisplay ();
    } 
    mouseOldX = x; 
    mouseOldY = y;
}

void mouse(int button, int state, int x, int y) 
{
	if(state == GLUT_DOWN) 
    {
        switch(button) 
        {
            case GLUT_LEFT_BUTTON: 
            case GLUT_RIGHT_BUTTON:
                mState = DOWN;
                mouseOldX = x;
                mouseOldY = y;
            break;
        }
    } 
}

void keyInput (unsigned char key, int x, int y)
{
    switch (key) 
	{
      //ESC to Exit
      case 27:
          exit(0);
		  break;
      default:
          break;
    }
}

int main2(int argc, char **argv)
{
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(winW,winH);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-winW)/2,(glutGet(GLUT_SCREEN_HEIGHT)-winH)/2); 
    glutCreateWindow(NAME);

    setup();

	glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
	glutMouseFunc (mouse);
    glutMotionFunc (motion);
	glutKeyboardFunc(keyInput);
    glutMainLoop();
    return 0;
}