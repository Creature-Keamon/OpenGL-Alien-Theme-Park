#include <GL/freeglut.h>
#include <GL/freeglut_std.h>
#include "Alien.h"

void drawAlien() {

    glutSolidCone(1, 1, 10, 10);
    glColor3f(0,0,1);
    glPushMatrix();
    glScalef(1,0.5,1);
    glutSolidSphere(1, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glScalef(1,0.5,1);
    glTranslatef(0,-2,0);
    glutSolidSphere(1, 10, 10);
    glPopMatrix();

}