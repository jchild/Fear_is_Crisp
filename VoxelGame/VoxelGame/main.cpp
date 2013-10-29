#include <stdlib.h>
#include <stdio.h>
#include <math.h>
//#include "Block.h"
#include "Camera.h"

#ifdef __APPLE__
#include <GLUT/freeglut.h>
#else
#include <GL/freeglut.h>
#endif

float red = 1.0f, green = 0.0f, blue = 0.0f;

//Vertex-Buffer Object
GLuint vboId= 0;
GLfloat* vertices;

const int DESIRED_FPS = 60;
//DisplayStatistics displayUtil;

// MENU DEFINITION
#define RED 1
#define GREEN 2
#define BLUE 3
#define ORANGE 4

#define FILL 1
#define LINE 2

#define SHRINK 1
#define NORMAL 2

//Popup Menu Identifiers
int fillMenu, shrinkMenu, mainMenu, colorMenu;

//scale of snowman
float scale = 1.0f;

//Menu status
int menuFlag = 0;

//default font
void *font = GLUT_BITMAP_TIMES_ROMAN_24;

#define INT_GLUT_BITMAP_8_BY_13 1
#define INT_GLUT_BITMAP_9_BY_15 2
#define INT_GLUT_BITMAP_TIMES_ROMAN_10  3
#define INT_GLUT_BITMAP_TIMES_ROMAN_24  4
#define INT_GLUT_BITMAP_HELVETICA_10  5
#define INT_GLUT_BITMAP_HELVETICA_12  6
#define INT_GLUT_BITMAP_HELVETICA_18  7

//Orthographics
int width = 1024, height = 768;

float blockSize = 0.25f;
//Block* m_pBlocks[32][32][32];

/*TEST*/
Camera camera;

void drawSnowMan(){
	glScalef(scale, scale, scale);
	glColor3f(1.0f, 1.0f, 1.0f);

	//Draw Body
	glTranslatef(0.0f, 0.75f, 0.0f);
	glutSolidSphere(0.75f, 20, 20);

	//Draw Head
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f, 20, 20);

	//Draw Eyes
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f, 10, 10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f, 10, 10);
	glPopMatrix();

	//Draw Nose
	glColor3f(red, green, blue);
	glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
	glutSolidCone(0.08f, 0.5f, 10, 2);
}

void renderCube()
{	
	glPushMatrix();
		glBegin(GL_QUADS);
			glColor3f(red, green, blue);
			glVertex3f( blockSize, blockSize,-blockSize);          // Top Right Of The Quad (Top)
			glVertex3f(-blockSize, blockSize,-blockSize);          // Top Left Of The Quad (Top)
			glVertex3f(-blockSize, blockSize, blockSize);          // Bottom Left Of The Quad (Top)
			glVertex3f( blockSize, blockSize, blockSize);          // Bottom Right Of The Quad (Top)

			glVertex3f( blockSize,-blockSize, blockSize);          // Top Right Of The Quad (Bottom)
			glVertex3f(-blockSize,-blockSize, blockSize);          // Top Left Of The Quad (Bottom)
			glVertex3f(-blockSize,-blockSize,-blockSize);          // Bottom Left Of The Quad (Bottom)
			glVertex3f( blockSize,-blockSize,-blockSize);          // Bottom Right Of The Quad (Bottom)

			glVertex3f( blockSize, blockSize, blockSize);          // Top Right Of The Quad (Front)
			glVertex3f(-blockSize, blockSize, blockSize);          // Top Left Of The Quad (Front)
			glVertex3f(-blockSize,-blockSize, blockSize);          // Bottom Left Of The Quad (Front)
			glVertex3f( blockSize,-blockSize, blockSize);          // Bottom Right Of The Quad (Front)

			glVertex3f( blockSize,-blockSize,-blockSize);          // Bottom Left Of The Quad (Back)
			glVertex3f(-blockSize,-blockSize,-blockSize);          // Bottom Right Of The Quad (Back)
			glVertex3f(-blockSize, blockSize,-blockSize);          // Top Right Of The Quad (Back)
			glVertex3f( blockSize, blockSize,-blockSize);          // Top Left Of The Quad (Back)

			glVertex3f(-blockSize, blockSize, blockSize);          // Top Right Of The Quad (Left)
			glVertex3f(-blockSize, blockSize,-blockSize);          // Top Left Of The Quad (Left)
			glVertex3f(-blockSize,-blockSize,-blockSize);          // Bottom Left Of The Quad (Left)
			glVertex3f(-blockSize,-blockSize, blockSize);          // Bottom Right Of The Quad (Left)

			glVertex3f( blockSize, blockSize,-blockSize);          // Top Right Of The Quad (Right)
			glVertex3f( blockSize, blockSize, blockSize);          // Top Left Of The Quad (Right)
			glVertex3f( blockSize,-blockSize, blockSize);          // Bottom Left Of The Quad (Right)
			glVertex3f( blockSize,-blockSize,-blockSize);          // Bottom Right Of The Quad (Right)
		glEnd();
	glPopMatrix();
}

void renderCubes()
{
	/*
	for(int x = 0; x < 32; x++)
	{
		for(int y = 0; y < 32; y++)
		{
			for(int z = 0; z < 32; z++)
			{
				glTranslatef((GLfloat)x * blockSize, (GLfloat)y * blockSize, (GLfloat)z * blockSize);
				renderCube();				
			}
		}
	}*/
	glTranslatef(0,1,0);
	renderCube();
}
// ------------------------------------------
//					TEXT
// ------------------------------------------
void renderBitmapString(float x, float y, float z, void *font, char *string){
	char *c;
	glRasterPos3f(x,y,z);
	for(c = string; *c != '\0'; c++){
		glutBitmapCharacter(font, *c);
	}
}

void renderSpacedBitmapString(float x, float y, int spacing, void *font, char *string){
	char *c;
	float x1=x;

	for(c = string; *c != '\0'; c++){
		glRasterPos2f(x1, y);
		glutBitmapCharacter(font, *c);
		x1 = x1 + glutBitmapWidth(font, *c) + spacing;
	}
}

void renderVerticalBitmapString(float x, float y, int bitmapHeight, void *font, char *string){
	char *c;
	int i;

	for(c = string, i = 0; *c != '\0'; i++, c++){
		glRasterPos2f(x, y+bitmapHeight * i);
		glutBitmapCharacter(font, *c);
	}
}

void renderStrokeFontString(float x, float y, float z, void *font, char *string){
	char *c;
	glPushMatrix();
	
	glTranslatef(x,y,z);

	for(c = string; *c != '\0'; c++){
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
	}

	glPopMatrix();
}

// ------------------------------------------
//				KEYBOARD
// ------------------------------------------
void processNormalKeys(unsigned char key, int x, int y){
	switch(key){
	case 27:
		glutDestroyMenu(mainMenu);
		glutDestroyMenu(fillMenu);
		glutDestroyMenu(colorMenu);
		glutDestroyMenu(shrinkMenu);
		exit(0);
		break;
	case 's':
		if(!menuFlag)
			glutChangeToSubMenu(2, "Shrink", shrinkMenu);
		break;
	case 'c':
		if(!menuFlag)
			glutChangeToSubMenu(2, "Color", colorMenu);
		break;
	case 'f':
		if(!menuFlag)
			glutChangeToSubMenu(3, "Fill", fillMenu);
		break;
	}
	if(key == 27)
		exit(0);	
}

// ------------------------------------------
//					MENUS
// ------------------------------------------
void processMenuStatus(int status, int x, int y){
	if(status == GLUT_MENU_IN_USE){
		menuFlag = 1;
	}
	else{
		menuFlag = 0;
	}
}

void processMainMenu(int option){
	//Nothing here
	//All actions are for submenus
}

void processFillMenu(int option){
	switch(option){
		case FILL:
			glPolygonMode(GL_FRONT,GL_FILL);
			break;
		case LINE:
			glPolygonMode(GL_FRONT, GL_LINE);
			break;
	}
}

void processShrinkMenu(int option){
	switch(option){
		case SHRINK:
			scale = 0.5f;
			break;
		case NORMAL:
			scale = 1.0f;
			break;
	}
}

void processColorMenu(int option){
	switch(option){
		case RED :
			red = 1.0f;
			green = 0.0f;
			blue = 0.0f;
			break;	
		case GREEN :
			red = 0.0f;
			green = 1.0f;
			blue = 0.0f;
			break;
		case BLUE :
			red = 0.0f;
			green = 0.0f;
			blue = 1.0f;
			break;	
		case ORANGE :
			red = 1.0f;
			green = 0.5f;
			blue = 0.5f;
			break;
	}
}

void createPopupMenus(){
	shrinkMenu = glutCreateMenu(processShrinkMenu);
	glutAddMenuEntry("SHRINK", SHRINK);
	glutAddMenuEntry("NORMAL", NORMAL);

	fillMenu = glutCreateMenu(processFillMenu);
	glutAddMenuEntry("FILL", FILL);
	glutAddMenuEntry("Line", LINE);

	colorMenu = glutCreateMenu(processColorMenu);
	glutAddMenuEntry("RED", RED);
	glutAddMenuEntry("GREEN", GREEN);
	glutAddMenuEntry("BLUE", BLUE);
	glutAddMenuEntry("ORANGE", ORANGE);

	mainMenu = glutCreateMenu(processMainMenu);
	glutAddSubMenu("Scale Mode", shrinkMenu);
	glutAddSubMenu("Polygon Mode", fillMenu);
	glutAddSubMenu("Color", colorMenu);
	//attach the menu to the right button
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	//this will allow us to know if the menu is active
	glutMenuStatusFunc(processMenuStatus);
}

void renderScene(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	camera.UpdateCamera();

	//Draw Ground
	glColor3f(0.5f, 0.5f, 0.5f);
	glBegin(GL_QUADS);
		glVertex3f(-100.f, 0.0f, -100.0f);
		glVertex3f(-100.f, 0.0f, 100.0f);
		glVertex3f(100.f, 0.0f, 100.0f);
		glVertex3f(100.f, 0.0f, -100.0f);
	glEnd();

	renderCubes();

	glutSwapBuffers();
}

void changeSize(int w, int h)
{
	camera.changeSize(w,h);
}

void mouseButton(int button, int state, int x, int y)
{
	camera.mouseButton(button, state, x, y);
}

void mouseMove(int x, int y)
{
	camera.mouseMove(x, y);
}

void pressKey(int key, int xx, int yy)
{
	camera.pressKey(key, xx, yy);
}
void releaseKey(int key, int x, int y)
{
	camera.releaseKey(key, x, y);
}

int main(int argc, char **argv) {

	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(1024,768);
	glutCreateWindow("Lighthouse3D - GLUT Tutorial");
	
	camera = Camera();
	
	// register callbacks
	glutDisplayFunc(renderScene);

	//Reshape window
	glutReshapeFunc(changeSize);

	//Called when application is idle
	glutIdleFunc(renderScene);

	//Keyboard
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(pressKey);

	glutIgnoreKeyRepeat(1);
	glutSpecialUpFunc(releaseKey);

	//Mouse
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	//init Menus
	createPopupMenus();
	
	// enter GLUT event processing cycle
	glutMainLoop();
	
	return 1;
}