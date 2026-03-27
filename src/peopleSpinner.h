#ifndef SPINNER_H
#define SPINNER_H

#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>

void DrawPerson() {
  GLUquadric *q = gluNewQuadric();
  gluQuadricDrawStyle(q, GLU_FILL);

  // torso
  glPushMatrix();
  glScalef(0.7, 2, 0.7);
  glTranslatef(0, 1, 0);
  glRotatef(90, 1, 0, 0);
  gluCylinder(q, 0.8, 0.8, 1.5, 36, 10);
  glPopMatrix();

  glColor3f(0.75, 0.72, 0.49);
  // head
  glPushMatrix();
  glTranslatef(0, 2, 0);
  glutSolidSphere(1, 20, 20);
  glPopMatrix();

  // left arm
  glPushMatrix();
  glRotatef(90, 0, 1, 0);
  glTranslatef(0, 1, 0.5);
  gluCylinder(q, 0.2, 0.2, 1.5, 12, 8);
  glPopMatrix();

  // right arm
  glPushMatrix();
  glRotatef(90, 0, 1, 0);
  glTranslatef(0, 1, -2);
  gluCylinder(q, 0.2, 0.2, 1.5, 12, 8);
  glPopMatrix();

  // right leg
  glPushMatrix();
  glTranslatef(0.2, -1, 0);
  glRotatef(90, 0, 1, 0);
  glRotatef(40, 1, 0, 0);
  gluCylinder(q, 0.2, 0.2, 1.5, 12, 8);
  glPopMatrix();

  // left leg
  glPushMatrix();
  glTranslatef(-0.2, -1, 0);
  glRotatef(90, 0, 1, 0);
  glRotatef(140, 1, 0, 0);
  gluCylinder(q, 0.2, 0.2, 1.5, 12, 8);
  glPopMatrix();
}

void DrawPeopleSpinner() {

  glColor3f(0.2, 0.2, 0.2);
  glPushMatrix();
  glutSolidTorus(1, 4, 8, 40);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, -0.3, 0);
  DrawPerson();
  glPopMatrix();
}

void DrawRamp() {
  GLUquadric *q = gluNewQuadric();
  gluQuadricDrawStyle(q, GLU_FILL);

  glPushMatrix();
  glRotatef(90, 0, 1, 0);
  glColor3f(1, 1, 1);
  gluDisk(q, 0, 4, 3, 2);
  gluCylinder(q, 4, 4, 4, 3, 2);
  glPushMatrix();
  glTranslatef(0, 0, 4);
  gluDisk(q, 0, 4, 3, 2);
  glPopMatrix();
  glPopMatrix();
}

#endif