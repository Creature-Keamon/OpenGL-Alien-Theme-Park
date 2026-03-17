#include <GL/freeglut.h>
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include "Alien.h"

void drawAlien() {
    glPushMatrix();
    glTranslatef(0, 2, 0);
    alienHead();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, -1.5);
    glScalef(0.7, 1.3, 1);
    glutSolidSphere(2, 10, 10);
    glPopMatrix();
    

}

void alienHead() {
    // teeth
    for (int i = 0; i < 7; i ++) {
        glPushMatrix();
        glTranslatef(-0.6 + (i*0.2), 0, 0.8);
        glRotatef(90, 1, 0, 0);
        glutSolidCone(0.2, 1, 10, 10);
        glPopMatrix();
    }

    // eyes
    for (int  i = -1; i < 2; i +=2) {
        glPushMatrix();
        glColor3f(1, 1, 1);
        glTranslatef(i*0.5, 0.6, 0.5);
        glutSolidSphere(0.3, 8, 8);
        glPopMatrix();
        
        glPushMatrix();
        glColor3f( 0,0,0);
        glTranslatef(i*0.4, 0.5, 0.75);
        glutSolidSphere(0.1, 6, 6);
        glPopMatrix();
    }
    
    //jaw
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