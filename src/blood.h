#ifndef BLOOD_H
#define BLOOD_H

#define _USE_MATH_DEFINES
#include <GL/freeglut.h>
#include <climits>
#include <cmath>
#include <iostream>
#include <list>

int tick = 0;

struct particle {
  int t;
  float pos[3];
  float vel[3];
  float col;
  float size;
};

list<particle> parList;

void newParticle() {
  particle p = {0};
  p.pos[0] = 10;
  p.pos[1] = 6.7;
  p.pos[2] = -10;
  p.vel[0] = 0;
  p.vel[1] = 0;
  p.vel[2] = -2;
  p.size = 1;

  parList.push_back(p);
}

void updateQueue() {
  const int LIFETIME = 20;
  list<particle>::iterator it;
  particle p;
  int tval;
  float delta;

  if (!parList.empty()) {
    p = parList.front();
    if (p.t > LIFETIME)
      parList.pop_front();
  }

  for (it = parList.begin(); it != parList.end(); it++) {
    tval = it->t;
    it->t = tval + 1;
    delta = (float)tval / (float)LIFETIME;

    for (int i = 0; i < 3; i++)
      (it->pos[i]) += it->vel[i];

    it->size = delta * 20 + 5; // (5 - 25)
    it->col = 1 - delta;       // (1 - 0)
  }
}

#endif