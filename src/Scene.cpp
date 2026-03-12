#include <GL/freeglut.h>
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <cmath> 
#include "Alien.h"


float angle = 0, look_x, look_z = -1, eye_x, eye_z;
int turnDirection = 0;
int moveDirection = 0;

void drawFloor() {
	bool flag = false;

	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	for (int x = -400; x <= 400; x += 20) {
		for (int z = -400; z <= 400; z += 20) {
			if (flag) glColor3f(0.6, 1.0, 0.8);
			else 	  glColor3f(0.8, 1.0, 0.6);
			glVertex3f(x, 0, z);
			glVertex3f(x, 0, z+20);
			glVertex3f(x+20, 0, z+20);
			glVertex3f(x+20, 0, z);
			flag = !flag;
		}
	}
	glEnd();
}

void special(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT) turnDirection = -1;
	else if (key == GLUT_KEY_RIGHT) turnDirection = 1;
	
	if (key == GLUT_KEY_DOWN) moveDirection = -1;	
	else if (key == GLUT_KEY_UP) moveDirection = 1;
}

void normal(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT or key == GLUT_KEY_RIGHT) turnDirection = 0;
	if (key == GLUT_KEY_UP or key == GLUT_KEY_DOWN) turnDirection = 0;
}

void moveCamera() {
	if (turnDirection == -1) {
		angle -=0.1;
	}
	else if (turnDirection == 1) {
		angle +=0.1;
	}
	if (moveDirection == 1) {
		eye_x += 0.1*sin(angle);
		eye_z -= 0.1*cos(angle);
	}
	else if (moveDirection == -1) {
		eye_x -= 0.1*sin(angle);
		eye_z += 0.1*cos(angle);
	}
	look_x = eye_x + 100*sin(angle);
	look_z = eye_z - 100*cos(angle);
	glutPostRedisplay();
}

void display() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	//GL_LINE = Wireframe;   GL_FILL = Solid
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,1,1,100);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye_x, 3., eye_z, look_x, 3, look_z, 0., 1., 0.);
	
	float lpos[4] = {10., 10., 10., 1.};		//light's position
	glLightfv(GL_LIGHT0, GL_POSITION, lpos);	//set light position
	moveCamera();
	drawFloor();
	drawAlien();
	glutSwapBuffers();
}

void initialise()
{
	glClearColor(0., 1., 1., 1.);	//Background colour
	
	glEnable(GL_LIGHTING);	//Enable OpenGL states
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1280, 720); 
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Super Duper Alien Theme Park!");
	initialise();

	glutDisplayFunc(display);
	glutSpecialFunc(special); 
	glutSpecialUpFunc(normal);
	glutMainLoop();
	return 0;
}