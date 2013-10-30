#pragma once
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Block
{
public:
	Block(void);
	~Block(void);
	void renderCube(float x, float y, float z);
	void renderCubes();
	void renderGround();
	float red = 1.0f, green = 0.0f, blue = 0.0f;
private:
	float blockSize;
	//float red = 1.0f, green = 0.0f, blue = 0.0f;
	bool ground;
};

