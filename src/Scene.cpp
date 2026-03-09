#include <GL/freeglut.h>

using namespace std;

float *x, *y, *z;					//vertex coordinates
int *nv, *t1, *t2, *t3, *t4;		//number of vertices and vertex indices of each face
int nvert, nface;					//total number of vertices and faces
float angle_x = 10., angle_y = -20.;//Rotation angles about x, y axes
float xmin, xmax, ymin, ymax;

void display() {
	float lpos[4] = {10., 10., 10., 1.};		//light's position

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	//GL_LINE = Wireframe;   GL_FILL = Solid
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0., 1., 20., 0., 0., 0., 0., 1., 0.);
	glLightfv(GL_LIGHT0, GL_POSITION, lpos);	//set light position

	glRotatef(angle_x, 1., 0., 0.);				//rotate the object about the x-axis
	glRotatef(angle_y, 0., 1., 0.);				//rotate the object about the y-axis

	glColor3f(0., 1., 1.);

	

	glFlush();
}

//-- Initialize OpenGL parameters ------------------------------------------
void initialize()
{
	float model_wid, model_hgt;
		//Specify mesh file name here
	glClearColor(1., 1., 1., 1.);	//Background colour

	glEnable(GL_LIGHTING);	//Enable OpenGL states
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(xmin, xmax, ymin, ymax, 10., 1000.);  //The camera view volume  
}


void special(int key, int x, int y) {
	if 		(key == GLUT_KEY_LEFT) 	angle_y--;
	else if (key == GLUT_KEY_RIGHT) angle_y++;
	else if (key == GLUT_KEY_UP) 	angle_x--;
	else if (key == GLUT_KEY_DOWN) 	angle_x++;
	glutPostRedisplay();
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_DEPTH);
	glutInitWindowSize(600, 600); 
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Super Duper Alien Theme Park!");
	initialize();

	glutDisplayFunc(display);
	glutSpecialFunc(special); 
	glutMainLoop();
	return 0;
}