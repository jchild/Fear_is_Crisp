#include "Camera.h"
#include <iostream>

Camera::Camera(void)
{
	width = 1024;
	height = 768;

	angle = 0.0f;
	lx = 0.0f, lz = -1.0f;
	x=0.0f, z=5.0f;

	deltaAngle = 0.0f;
	deltaMoveX = 0.0f;
	deltaMovez = 0.0f;
	xOrigin = -1;


	glMatrixMode(GL_PROJECTION);

}


Camera::~Camera(void)
{
}

void Camera::UpdateCamera()
{
	if(deltaMoveX)
		computePosX(deltaMoveX);
	if (deltaMovez)
		computePosz(deltaMovez);
	//if(deltaAngle)
	//	computeDir(deltaAngle);

	glLoadIdentity();

	gluLookAt(x, 1.0f, z,
			  x + lx, 1.0f, z + lz,
			  0.0f, 1.0f, 0.0f);	
}

void Camera:: changeProjection(bool perspective)
{
	if(perspective)
	{
		glMatrixMode(GL_PROJECTION);

		glPopMatrix();

		glMatrixMode(GL_MODELVIEW);
	}
	else
	{
		//switch to projection mode
		glMatrixMode(GL_PROJECTION);

		//save previous matrix which contains
		//the settings for the perspective projection
		glPushMatrix();

		//reset matrix
		glLoadIdentity();

		//set 2D orthographics projection
		gluOrtho2D(0, width, height, 0);

		//switch back to modelview mode
		glMatrixMode(GL_MODELVIEW);
	}
}

void Camera:: changeSize(int w, int h){
	//Prevent a divide by zero, when window is too short
	//(you cant make a window of zero width)
	if(h == 0)
		h = 1;

	float ratio = w * 1.0f/h;

	//Use the projection matrix
	glMatrixMode(GL_PROJECTION);

	//Reset matrix
	glLoadIdentity();

	//Set the viewport to be theentire window
	glViewport(0,0,w,h);

	width = w;
	height = h;

	//Set the correct perspective
	gluPerspective(45, ratio, 0.1f, 100.0f);

	//Get back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}


/*
*
*	Controls
*
*/

//Mouse

void Camera:: mouseButton(int button, int state, int x, int y){
	//only start motion if the left button is pressed
	if(button == GLUT_LEFT_BUTTON){
		//when the button is released
		if(state == GLUT_UP){
			angle += deltaAngle;
			xOrigin = -1;
		}
		else{ //When left button is pressed
			xOrigin = x;
		}
	}
}

void Camera:: mouseMove(int x, int y){
	//this will only be true when the left button is down
	if(xOrigin >= 0){
		//update deltaAngle
		deltaAngle = ((x - xOrigin) * 0.001f);

		//update camera's direction
		lx = sin(angle + deltaAngle);
		lz = -cos(angle + deltaAngle);
	}
}

//Keyboard
//compute position when walking foward and back
void Camera:: computePosX(float deltaMoveX){
	x += deltaMoveX * lx * 0.1f;
	z += deltaMoveX * lz * 0.1f;
}
void Camera::computePosz(float deltaMovez){
// compute the position when straifing
}

void Camera:: pressKey(int key, int xx, int yy){
	switch(key){
		case GLUT_KEY_UP: 
			deltaMoveX = 0.5f; 
			break;
		case GLUT_KEY_DOWN: 
			deltaMoveX = -0.5f;
			break;
		case GLUT_KEY_LEFT: 
			deltaMovez = 0.5f;
			break;
		case GLUT_KEY_RIGHT: 
			deltaMovez = -0.5f;
			break;

	}
}

void Camera:: releaseKey(int key, int x, int y){
	switch(key){
	case GLUT_KEY_UP:
		deltaMoveX = 0.0f;
		break;
	case GLUT_KEY_DOWN: 
		deltaMoveX = 0; 
		break;
	case GLUT_KEY_LEFT:
		deltaMovez = 0.0f;
		break;
	case GLUT_KEY_RIGHT:
		deltaMovez = 0.0f;
		break;
	}
}

