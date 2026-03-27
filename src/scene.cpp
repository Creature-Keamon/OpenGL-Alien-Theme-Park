#include "alien.h"
#include "environment.h"
#include "loadBMP.h"
#include "movement.h"
#include "peopleSpinner.h"
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>

float aspectRequired = 1.777777778;
float purple[] = {1, 1, 1, 1};

GLUquadricObj *q;
GLuint texId[3];

void loadTexture() {
  glGenTextures(3, texId);

  glBindTexture(GL_TEXTURE_2D, texId[0]);
  loadBMP("../assets/skyboxTex.bmp");
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glBindTexture(GL_TEXTURE_2D, texId[1]);
  loadBMP("../assets/gravelRoad.bmp");
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

// boilerplate funcs ---------------------------------------------------------

void clockTimer(int value) {
  if (headBounce > 1.2) {
    heightChange = -0.05;
  } else if (headBounce < -1.2) {
    heightChange = 0.05;
  }
  headBounce += heightChange;
  bounce = (fabs(sinf(headBounce)) * 0.8) + 0.5;
  glutPostRedisplay();
  glutTimerFunc(50, clockTimer, 0);
}

void reshape(int width, int height) {
  float aspectCurrent = (float)width / (float)height;
  if (aspectCurrent > aspectRequired)
    glViewport(0, 0, height * aspectRequired, height);
  else
    glViewport(0, 0, width, width / aspectRequired);
}

void display() {
  if (!wireframe) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  } else {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, 1.777777778, 1, 1000);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  float spotDir[] = {look_x, height - 70, look_z};
  float spotPosn[] = {eye_x, height + 5, eye_z, 1};
  gluLookAt(eye_x, height, eye_z, look_x, height, look_z, 0., 1., 0.);
  glLightfv(GL_LIGHT1, GL_POSITION, spotPosn);
  glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 35);
  glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2);
  glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDir);

  moveCamera();
  DrawFloor(texId);
  DrawSkybox(texId, q);
  //------
  glPushMatrix();
  glTranslatef(0, 2, 0);
  drawAlien(bounce);
  glPopMatrix();
  //------
  glPushMatrix();
  glTranslatef(10, 2, 0);
  HungryAlien(bounce);
  glPopMatrix();
  //------
  glPushMatrix();
  glTranslatef(10, 7, -10);
  DrawPeopleSpinner();
  glPopMatrix();
  //------
  glPushMatrix();
  glTranslatef(8, 0, -5);
  DrawRamp();
  glPopMatrix();
  //------
  glPushMatrix();
  glTranslatef(8, 0, -15);
  DrawRamp();
  glPopMatrix();

  glutSwapBuffers();
}

void initialise() {
  q = gluNewQuadric();
  glEnable(GL_TEXTURE_2D);
  loadTexture();

  glClearColor(0., 1., 1., 1.); // Background colour
  glEnable(GL_ALPHA_TEST);
  glAlphaFunc(GL_GREATER, 0);
  glEnable(GL_LIGHTING); // Enable OpenGL states
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_COLOR_MATERIAL);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, purple);
  glLightfv(GL_LIGHT1, GL_SPECULAR, purple);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluQuadricDrawStyle(q, GL_FILL);
  gluQuadricNormals(q, GLU_SMOOTH);
  gluQuadricTexture(q, GL_TRUE);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(1280, 720);
  glutInitWindowPosition(10, 10);
  glutCreateWindow("Super Duper Alien Theme Park!");
  initialise();

  glutTimerFunc(50, clockTimer, 0);
  glutDisplayFunc(display);

  // handle movement controls
  glutKeyboardFunc(keyboard);
  glutKeyboardUpFunc(keyboardUp);
  glutSpecialFunc(special);
  glutSpecialUpFunc(normal);
  glutReshapeFunc(reshape);
  glutMainLoop();
  return 0;
}