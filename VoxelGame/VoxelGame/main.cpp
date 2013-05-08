#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glBegin(GL_QUADS);
		glVertex3f(-0.7f, -1.5f, -5.0f);
		glVertex3f(0.7f, -1.5f, -5.0f);
		glVertex3f(0.4f,-0.5f,-5.0f);
		glVertex3f(-0.4f,-0.5f,-5.0f);
	glEnd();
	glBegin(GL_TRIANGLES); //Begin triangle coordinates
    
		//Pentagon
		glVertex3f(0.5f, 0.5f, -5.0f);
		glVertex3f(1.5f, 0.5f, -5.0f);
		glVertex3f(0.5f, 1.0f, -5.0f);
    
		glVertex3f(0.5f, 1.0f, -5.0f);
		glVertex3f(1.5f, 0.5f, -5.0f);
		glVertex3f(1.5f, 1.0f, -5.0f);
    
		glVertex3f(0.5f, 1.0f, -5.0f);
		glVertex3f(1.5f, 1.0f, -5.0f);
		glVertex3f(1.0f, 1.5f, -5.0f);
		//Triangle
		glVertex3f(-0.5f, 0.5f, -5.0f);
		glVertex3f(-1.0f, 1.5f, -5.0f);
		glVertex3f(-1.5f, 0.5f, -5.0f);
	glEnd(); //End triangle coordinates

        glutSwapBuffers();
}
void initRendering() {
    //Makes 3D drawing work when something is in front of something else
    glEnable(GL_DEPTH_TEST);
}
void handleKeypress(unsigned char key, //The key that was pressed
                    int x, int y) {    //The current mouse coordinates
    switch (key) {
        case 27: //Escape key
            exit(0); //Exit the program
    }
}
void handleResize(int w, int h) {
    //Tell OpenGL how to convert from coordinates to pixel values
    glViewport(0, 0, w, h);
    
    glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective
    
    //Set the camera perspective
    glLoadIdentity(); //Reset the camera
    gluPerspective(45.0,                  //The camera angle
                   (double)w / (double)h, //The width-to-height ratio
                   1.0,                   //The near z clipping coordinate
                   200.0);                //The far z clipping coordinate
}

int main(int argc, char **argv) {

	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("Tacos - GLUT");
	initRendering();
	// register callbacks
	glutDisplayFunc(renderScene);
	glutKeyboardFunc(handleKeypress);
    glutReshapeFunc(handleResize);

	// enter GLUT event processing cycle
	glutMainLoop();
	
	return 1;
}
