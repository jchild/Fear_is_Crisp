#pragma once

#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Camera
{
public:
	Camera(void);
	~Camera(void);

	void UpdateCamera();
	void changeProjection(bool Perspective);
	void changeSize(int w, int h);

	void mouseButton(int button, int state, int x, int y);
	void mouseMove(int x, int y);
	void moveCamera();

	void pressKey(int key, int xx, int yy);
	void releaseKey(int key, int x, int y);
private:
	int width;
	int height;

	//Camera
	float angle;
	//Vector representing camera direction
	float lx, lz;
	//XZ position of camera
	float x, z;

	float deltaAngle;
	float deltaMove;
	int xOrigin;


	void computePos(float deltaMove);
	void computeDir(float deltaAngle);
};

