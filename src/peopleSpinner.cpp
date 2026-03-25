#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>

void DrawPerson() { glutSolidCube(2); }

void PeopleSpinner() {

  glColor3f(0.2, 0.2, 0.2);
  glPushMatrix();
  glutSolidTorus(1, 4, 8, 40);
  glPopMatrix();

  glPushMatrix();
  DrawPerson();
  glPopMatrix();
}
