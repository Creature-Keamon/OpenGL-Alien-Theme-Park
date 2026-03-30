#ifndef SPINNER_H
#define SPINNER_H

#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>

bool refresh = false;
bool showPerson = true;

void DrawPerson() {
  GLUquadric *q = gluNewQuadric();
  gluQuadricDrawStyle(q, GLU_FILL);

  glNormal3f(0, 1, 0);
  // torso
  glPushMatrix();
  glScalef(0.7, 2, 0.7);
  glTranslatef(0, 1, 0);
  glRotatef(90, 1, 0, 0);
  gluCylinder(q, 0.8, 0.8, 1.5, 36, 10);
  glPopMatrix();

  glNormal3f(0, 1, 0);
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

void DrawPeopleSpinner(float hoopPos) {

    glNormal3f(0, 1, 0);
    glColor3f(0.2, 0.2, 0.2);
    glPushMatrix();
    glTranslatef(hoopPos, 0, 0);
    glPushMatrix();
    glutSolidTorus(1, 4, 8, 40);
    glPopMatrix();
    if (showPerson) {
        glPushMatrix();
        glTranslatef(0, -0.3, 0);
        DrawPerson();
        glPopMatrix();
    }
    glPopMatrix();
}

void DrawRamp() {
    GLUquadric *q = gluNewQuadric();
    gluQuadricDrawStyle(q, GLU_FILL);

    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glColor3f(1, 1, 1);
    glNormal3f(0, 1, 0);
    gluDisk(q, 0, 4, 3, 2);
    gluCylinder(q, 4, 4, 4, 3, 2);
    glPushMatrix();
    glTranslatef(0, 0, 4);
    gluDisk(q, 0, 4, 3, 2);
    glPopMatrix();
    glPopMatrix();
}

void DrawRefresher(GLuint *texId) {
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texId[2]);
    glNormal3f(0, 1, 0);
    glColor3f(1, 1, 1);
    
    //back side
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(0, 0, 0);
    glTexCoord2f(1, 0);
    glVertex3f(10, 0, 0);
    glTexCoord2f(1, 1);
    glVertex3f(10, 15, 0);
    glTexCoord2f(0, 1);
    glVertex3f(0, 15, 0);
    glEnd();
    
    // end
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(10, 0, 0);
    glTexCoord2f(1, 0);
    glVertex3f(10, 0, 8);
    glTexCoord2f(1, 1);
    glVertex3f(10, 15, 8);
    glTexCoord2f(0, 1);
    glVertex3f(10, 15, 0);
    glEnd();
    
    //front side
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(0, 0, 8);
    glTexCoord2f(1, 0);
    glVertex3f(10, 0, 8);
    glTexCoord2f(1, 1);
    glVertex3f(10, 15, 8);
    glTexCoord2f(0, 1);
    glVertex3f(0, 15, 8);
    glEnd();

    //top 
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(0, 15, 0);
    glTexCoord2f(1, 0);
    glVertex3f(10, 15, 0);
    glTexCoord2f(1, 1);
    glVertex3f(10, 15, 8);
    glTexCoord2f(0, 1);
    glVertex3f(0, 15, 8);
    glEnd();

    //bottom 
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(0, 0, 0);
    glTexCoord2f(1, 0);
    glVertex3f(10, 0, 0);
    glTexCoord2f(1, 1);
    glVertex3f(10, 0, 8);
    glTexCoord2f(0, 1);
    glVertex3f(0, 0, 8);
    glEnd();

    // end
    glColor3f(0, 0, 0);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(0, 0, 0);
    glTexCoord2f(1, 0);
    glVertex3f(0, 0, 8);
    glTexCoord2f(1, 1);
    glVertex3f(0, 15, 8);
    glTexCoord2f(0, 1);
    glVertex3f(0, 15, 0);
    glEnd();

    glPopMatrix();


}

void DrawRide(GLuint *texId, float hoopPos) {
  //------
  glPushMatrix();
  glTranslatef(10, 7, -10);
  DrawPeopleSpinner(hoopPos);
  glPopMatrix();
  //------
  glPushMatrix();
  glTranslatef(8, 0, -3);
  DrawRamp();
  glPopMatrix();
  //------
  glPushMatrix();
  glTranslatef(8, 0, -15);
  DrawRamp();
  glPopMatrix();
  //------
  glPushMatrix();
  glTranslatef(15, 0, -15);
  DrawRefresher(texId);
  glPopMatrix();
}

#endif