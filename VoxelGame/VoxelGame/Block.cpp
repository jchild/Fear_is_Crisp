#include "Block.h"

Block::Block(void){
	blockSize = 0.25f;
	ground = false;
}

Block::~Block(){}

void Block:: renderCube(float x, float y, float z)
{
	glPushMatrix();
	glBegin(GL_QUADS);
	if (ground == true){
		glColor3f(0.5f, 0.5f, 0.5f);
	}
	else{
		glColor3f(red, green, blue);
	}
	
	glVertex3f(x, y, -z);          // Top Right Of The Quad (Top)
	glVertex3f(-x, y, -z);          // Top Left Of The Quad (Top)
	glVertex3f(-x, y, z);          // Bottom Left Of The Quad (Top)
	glVertex3f(x, y, z);          // Bottom Right Of The Quad (Top)

	glVertex3f(x, -y, z);          // Top Right Of The Quad (Bottom)
	glVertex3f(-x, -y, z);          // Top Left Of The Quad (Bottom)
	glVertex3f(-x, -y, -z);          // Bottom Left Of The Quad (Bottom)
	glVertex3f(x, -y, -z);          // Bottom Right Of The Quad (Bottom)

	glVertex3f(x, y, z);          // Top Right Of The Quad (Front)
	glVertex3f(-x, y, z);          // Top Left Of The Quad (Front)
	glVertex3f(-x, -y, z);          // Bottom Left Of The Quad (Front)
	glVertex3f(x, -y, z);          // Bottom Right Of The Quad (Front)

	glVertex3f(x, -y, -z);          // Bottom Left Of The Quad (Back)
	glVertex3f(-x, -y, -z);          // Bottom Right Of The Quad (Back)
	glVertex3f(-x, y, -z);          // Top Right Of The Quad (Back)
	glVertex3f(x, y, -z);          // Top Left Of The Quad (Back)

	glVertex3f(-x, y, z);          // Top Right Of The Quad (Left)
	glVertex3f(-x, y, -z);          // Top Left Of The Quad (Left)
	glVertex3f(-x, -y, -z);          // Bottom Left Of The Quad (Left)
	glVertex3f(-x, -y, z);          // Bottom Right Of The Quad (Left)

	glVertex3f(x, y, -z);          // Top Right Of The Quad (Right)
	glVertex3f(x, y, z);          // Top Left Of The Quad (Right)
	glVertex3f(x, -y, z);          // Bottom Left Of The Quad (Right)
	glVertex3f(x, -y, -z);          // Bottom Right Of The Quad (Right)
	glEnd();
	glPopMatrix();
}
void Block:: renderCubes()
{
	glTranslatef(0, 1, 0);
	renderCube(blockSize, blockSize, blockSize);
}

void Block::renderGround(){
	ground = true;
	for (int x = 0; x < 32; x++){
		for (int z = 0; z < 32; z++){
			renderCube((GLfloat)x * blockSize, blockSize, (GLfloat)z*blockSize);
		}
	}
	ground = false;
}