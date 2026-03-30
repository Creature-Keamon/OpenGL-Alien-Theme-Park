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
float white[] = {1, 1, 1, 1};

float light[] = {10, 10, -11, 1};
float dir[] = {0, -2, 0};
float rot = 0;

float hoopPos = 0;
float hoopMove = 1;

GLUquadricObj *q;
GLuint texId[3];

pos hoopyAliens[3] = {{10,2,0,0, 0},
                      {0,2,-22,180, 2},
                      {10,2,-22,0, 1}};

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

  glBindTexture(GL_TEXTURE_2D, texId[2]);
  loadBMP("../assets/metal1.bmp");
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

// timer funcs ----------------------------------------------------------

// moves aliens (crudely)
void MoveAliens() {
  int counter = 0; //

  for (int i = 0; i < 3; i ++) {

    // allows aliens to jump through the hoop
    if (hoopyAliens[i].posZ > -22 && hoopyAliens[i].posX == 10 && hoopyAliens[i].rotY == 0) {
        hoopyAliens[i].state = 0;
        hoopyAliens[i].posZ -=0.4;
        hoopyAliens[i].posY = fabs(6 * sinf(hoopyAliens[i].posZ/7)) + 2;

        //comparing within a range is a precaution to try eliminate potential floating point errors
        if (hoopyAliens[i].posZ > -12 && hoopyAliens[i].posZ < -10) {
            showPerson = false;
        }
        if (hoopyAliens[i].posZ > -15 && hoopyAliens[i].posZ < -13) {
            refresh = true;
        }
    }

    //turns aliens after their jump
    else if (hoopyAliens[i].rotY < 180){
      hoopyAliens[i].state = 1;
      hoopyAliens[i].rotY += 4;
    } 

    //moves aliens back to the start
    else if (hoopyAliens[i].rotY >=180 && hoopyAliens[i].posZ < 0) {
      hoopyAliens[i].rotY = 180;
      hoopyAliens[i].state = 2;
      hoopyAliens[i].posZ += 0.5;
    }

    //turns aliens to face the hoop
    else {
      hoopyAliens[i].state = 3;
      hoopyAliens[i].rotY += 4;

      //resets alien locations back to their originals 
      if (hoopyAliens[i].rotY == 360) {
        hoopyAliens[i].rotY = 0;
        hoopyAliens[i].posX = 10;
        hoopyAliens[i].posZ = 0;
      }
    }
  }
}

void clockTimer(int value) {
  if (headBounce > 1.2) {
    heightChange = -0.05;
  } 
  else if (headBounce < -1.2) {
    heightChange = 0.05;
  }
  MoveAliens();

  rot = rot + 0.1;
  if (rot >= 360 ) {
    rot = 0;
  }

  if (refresh) {
    hoopPos += hoopMove;
    if (hoopPos >= 11) {
        hoopMove = -1;
        showPerson = true;
    }
    else if (hoopPos <= 0) {
        refresh = false;
        hoopMove = 1;
    }

  }
  
  headBounce += heightChange;
  bounce = (fabs(sinf(headBounce)) * 0.8) + 0.5;
  
  
  glutPostRedisplay();
  glutTimerFunc(25, clockTimer, 0);
  
}

// boilerplate functions ----------------------------------------------------

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

  //glLightfv(GL_LIGHT0, GL_POSITION, light);
  
  float spotDir[] = {look_x, height - 70, look_z};
  float spotPosn[] = {eye_x, height + 5, eye_z, 1};
  gluLookAt(eye_x, height, eye_z, look_x, height, look_z, 0., 1., 0.);
  glLightfv(GL_LIGHT1, GL_POSITION, spotPosn);
  glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 35);
  glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2);
  glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDir);

  glLightfv(GL_LIGHT2, GL_POSITION, light);
  glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 100);
  glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 3);
  glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, dir);

  moveCamera();
  DrawFloor(texId);
  DrawSkybox(texId, q, rot);
  //------
  //glPushMatrix();
  //glTranslatef(0, 2, 0);
  //drawAlien(bounce);
  //glPopMatrix();
  
  // drawing aliens (crudely)------
  for (int i = 0; i < 3; i ++) {
    pos hoopyAlien = hoopyAliens[i];
    if (hoopyAlien.state == 0) {
      glPushMatrix();
      glTranslatef(hoopyAlien.posX, hoopyAlien.posY, hoopyAlien.posZ);
      HungryAlien(bounce);
      glPopMatrix();
    } 
    else if (hoopyAlien.state == 1){
      glPushMatrix();
      glTranslatef(5, hoopyAlien.posY, -22);
      glRotatef(hoopyAlien.rotY,0, 1, 0);
      glTranslatef(5, 0, 0);
      HungryAlien(bounce);
      glPopMatrix();
    } 
    else if (hoopyAlien.state == 2) {
      glPushMatrix();
      glTranslatef(0, hoopyAlien.posY,  hoopyAlien.posZ);
      glRotatef(hoopyAlien.rotY, 0, 1, 0);
      HungryAlien(bounce);
      glPopMatrix();
    }
    else if (hoopyAlien.state == 3){
      glPushMatrix();
      glTranslatef(5, hoopyAlien.posY, 0);
      glRotatef(hoopyAlien.rotY,0, 1, 0);
      glTranslatef(5, 0, 0);
      HungryAlien(bounce);
      glPopMatrix();
    } 
  }  
  glColor3f(1, 1, 1);
  DrawRide(texId, hoopPos);
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
  glEnable(GL_LIGHT2);
  glEnable(GL_COLOR_MATERIAL);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
  glLightfv(GL_LIGHT1, GL_SPECULAR, white);
  glLightfv(GL_LIGHT2, GL_DIFFUSE, white);
  glLightfv(GL_LIGHT2, GL_SPECULAR, white);
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