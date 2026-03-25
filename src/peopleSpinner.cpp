#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <GL/freeglut_std.h>
#include <GL/gl.h>

void PeopleSpinner() {

  glPushMatrix();
  glutSolidTorus(1, 4, 40, 40);
  glPopMatrix();
}