#pragma once
#include <stdlib.h>
#include <stdio.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#define RED 1
#define GREEN 2
#define BLUE 3
#define ORANGE 4

#define FILL 1
#define LINE 2

#define SHRINK 1
#define NORMAL 2

class Menu
{
public:
	Menu(void);
	~Menu(void);
	void processMenuStatus(int status, int x, int y);
	void processMainMenu(int option);
	void processFillMenu(int option);
	void processShrinkMenu(int option);
	void processColorMenu(int option);
	//void createPopupMenus();
	
private:
	
	float red = 1.0f, green = 0.0f, blue = 0.0f;
	int menuFlag = 0;
	float scale = 1.0f;
};

