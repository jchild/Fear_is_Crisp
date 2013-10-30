#include "Menu.h"

Menu::Menu(void){}
Menu::~Menu(void){}
void Menu:: processMenuStatus(int status, int x, int y){
	if (status == GLUT_MENU_IN_USE){
		menuFlag = 1;
	}
	else{
		menuFlag = 0;
	}
}

void Menu::processMainMenu(int option){
	//Nothing here
	//All actions are for submenus
}

void Menu::processFillMenu(int option){
	switch (option){
	case FILL:
		glPolygonMode(GL_FRONT, GL_FILL);
		break;
	case LINE:
		glPolygonMode(GL_FRONT, GL_LINE);
		break;
	}
}

void Menu::processShrinkMenu(int option){
	switch (option){
	case SHRINK:
		scale = 0.3f;
		break;
	case NORMAL:
		scale = 1.0f;
		break;
	}
}

void Menu::processColorMenu(int option){
	switch (option){
	case RED:
		red = 1.0f;
		green = 0.0f;
		blue = 0.0f;
		break;
	case GREEN:
		red = 0.0f;
		green = 1.0f;
		blue = 0.0f;
		break;
	case BLUE:
		red = 0.0f;
		green = 0.0f;
		blue = 1.0f;
		break;
	case ORANGE:
		red = 1.0f;
		green = 0.5f;
		blue = 0.5f;
		break;
	}
}

/*void Menu::createPopupMenus(){
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
}*/

