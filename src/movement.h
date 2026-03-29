#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>

bool wireframe = false;
float angle = 0, look_x, look_z = -1, eye_x, eye_z, height = 2.5;
int turnDirection = 0;
int moveDirection = 0;
int speedUp = 1;
int fly = 0;
float headBounce = 0;
float heightChange = 0.1;
float bounce = 0;

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
    speedUp = 4;

  if (key == GLUT_KEY_SHIFT_L || key == GLUT_KEY_SHIFT_R)
    fly = -1;
}

void keyboard(unsigned char key, int x, int y) {
  if (key == ' ') {
    fly = 1;
  }
  if (key == 'q') {
    wireframe = !wireframe;
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
    angle -= 0.04;
  } else if (turnDirection == 1) {
    angle += 0.04;
  }
  if (moveDirection == 1) {
    eye_x += speedUp * 0.2 * sin(angle);
    eye_z -= speedUp * 0.2 * cos(angle);
  } else if (moveDirection == -1) {
    eye_x -= speedUp * 0.2 * sin(angle);
    eye_z += speedUp * 0.2 * cos(angle);
  }
  if (fly == 1) {
    height += speedUp * 0.1;
  } else if (fly == -1) {
    height -= speedUp * 0.1;
  }

  look_x = eye_x + 100 * sin(angle);
  look_z = eye_z - 100 * cos(angle);
  glutPostRedisplay();
}

#endif