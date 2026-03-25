#include "alien.h"
#include "peopleSpinner.h"
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <cmath>

// objects to draw-------------------------------------------------------------

void drawFloor() {
  bool flag = false;

  glBegin(GL_QUADS);
  glNormal3f(0, 1, 0);
  for (int x = -400; x <= 400; x += 20) {
    for (int z = -400; z <= 400; z += 20) {
      if (flag)
        glColor3f(0.6, 1.0, 0.8);
      else
        glColor3f(0.8, 1.0, 0.6);
      glVertex3f(x, 0, z);
      glVertex3f(x, 0, z + 20);
      glVertex3f(x + 20, 0, z + 20);
      glVertex3f(x + 20, 0, z);
      flag = !flag;
    }
  }
  glEnd();
}

// movement funcs-------------------------------------------------------------

float angle = 0, look_x, look_z = -1, eye_x, eye_z, height = 2.5;
int turnDirection = 0;
int moveDirection = 0;
int speedUp = 1;
int fly = 0;
float headBounce = 0;
float heightChange = 0.1;

void special(int key, int x, int y) {
  if (key == GLUT_KEY_LEFT)
    turnDirection = -1;
  else if (key == GLUT_KEY_RIGHT)
    turnDirection = 1;

  if (key == GLUT_KEY_DOWN)
    moveDirection = -1;
  else if (key == GLUT_KEY_UP)
    moveDirection = 1;

  if (key == GLUT_KEY_CTRL_L || key == GLUT_KEY_CTRL_R)
    speedUp = 10;

  if (key == GLUT_KEY_SHIFT_L || key == GLUT_KEY_SHIFT_R)
    fly = -1;
}

void keyboard(unsigned char key, int x, int y) {
  if (key == ' ') {
    fly = 1;
  }
  if (key == 'q') {
  }
}

void keyboardUp(unsigned char key, int x, int y) {
  if (key == ' ') {
    fly = 0;
  }
}

void normal(int key, int x, int y) {
  if (key == GLUT_KEY_LEFT or key == GLUT_KEY_RIGHT)
    turnDirection = 0;
  if (key == GLUT_KEY_UP or key == GLUT_KEY_DOWN)
    moveDirection = 0;
  if (key == GLUT_KEY_CTRL_L || key == GLUT_KEY_CTRL_R)
    speedUp = 1;
  if (key == GLUT_KEY_SHIFT_L || key == GLUT_KEY_SHIFT_R)
    fly = 0;
}

void moveCamera() {
  if (turnDirection == -1) {
    angle -= 0.02;
  } else if (turnDirection == 1) {
    angle += 0.02;
  }
  if (moveDirection == 1) {
    eye_x += speedUp * 0.2 * sin(angle);
    eye_z -= speedUp * 0.2 * cos(angle);
  } else if (moveDirection == -1) {
    eye_x -= speedUp * 0.2 * sin(angle);
    eye_z += speedUp * 0.2 * cos(angle);
  }
  if (fly == 1) {
    height += speedUp * 0.5;
  } else if (fly == -1) {
    height -= speedUp * 0.5;
  }

  look_x = eye_x + 100 * sin(angle);
  look_z = eye_z - 100 * cos(angle);
  glutPostRedisplay();
}

// boilerplate funcs
// ------------------------------------------------------------------

void clockTimer(int value) {
  if (headBounce > 1.2) {
    heightChange = -0.05;
  } else if (headBounce < 0.9) {
    heightChange = 0.05;
  }
  headBounce += heightChange;
  glutPostRedisplay();
  glutTimerFunc(50, clockTimer, 0);
}

void display() {
  glPolygonMode(GL_FRONT_AND_BACK,
                GL_FILL); // GL_LINE = Wireframe;   GL_FILL = Solid
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, 1.777777778, 1, 1000);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(eye_x, height, eye_z, look_x, height, look_z, 0., 1., 0.);

  float lpos[4] = {0, 1, 0, 1.}; // light's position
  float dir[3] = {0, 0, 0};
  glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 200);
  glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2);
  glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, dir);
  glLightfv(GL_LIGHT1, GL_POSITION, lpos); // set light position
  moveCamera();
  drawFloor();
  glPushMatrix();
  glTranslatef(0, 2, 0);
  drawAlien(headBounce);
  PeopleSpinner();
  glPopMatrix();
  glutSwapBuffers();
}

void initialise() {
  glutInitWindowSize(1280, 720);
  glutInitWindowPosition(10, 10);
  glutCreateWindow("Super Duper Alien Theme Park!");
  glClearColor(0., 1., 1., 1.); // Background colour
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHTING); // Enable OpenGL states
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  initialise();

  glutTimerFunc(50, clockTimer, 0);
  glutDisplayFunc(display);

  // handle movement controls
  glutKeyboardFunc(keyboard);
  glutKeyboardUpFunc(keyboardUp);
  glutSpecialFunc(special);
  glutSpecialUpFunc(normal);
  glutMainLoop();
  return 0;
}