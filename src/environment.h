#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>

void DrawFloor(GLuint *texId) {
  glBindTexture(GL_TEXTURE_2D, texId[1]);
  glColor3f(1, 1, 1);
  glNormal3f(0, 1, 0);
  glBegin(GL_QUADS);
  for (float x = -50; x <= 50; x += 0.5) {
    for (float z = -50; z <= 50; z += 0.5) {
      glTexCoord2f(0, 0);
      glVertex3f(x, -0.1, z);
      glTexCoord2f(0, 1);
      glVertex3f(x, -0.1, z + 0.5);
      glTexCoord2f(1, 1);
      glVertex3f(x + 0.5, -0.1, z + 0.5);
      glTexCoord2f(1, 0);
      glVertex3f(x + 0.5, -0.1, z);
    }
  }
  glEnd();
}

void DrawSkybox(GLuint *texId, GLUquadricObj *q, float rot) {
  glColor3f(1, 1, 1);
  glBindTexture(GL_TEXTURE_2D, texId[0]);
  glPushMatrix();
  glRotatef(rot, 1, 1, 1);
  glRotatef(-90, 1, 0, 0);
  gluSphere(q, 500, 36, 36);
  glPopMatrix();
}

#endif