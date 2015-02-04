#include "mp3.h"
#include "lighting.h"

// contains reference code from
// http://60hz.csse.uwa.edu.au/workshop/workshop0/workshop1.c

void init_material() {
  // define material properties
  GLfloat k_ambient[] = {0.15f, 0.15f, 0.15f};
  GLfloat k_diffuse[] = {0.60f, 0.60f, 0.60f};
  GLfloat k_specular[] = {1.0f, 1.0f, 1.0f};
  GLfloat k_shininess = 125.0f;

  // load material properties
  glMaterialfv(GL_FRONT, GL_AMBIENT, k_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, k_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, k_specular);
  glMaterialf(GL_FRONT, GL_SHININESS, k_shininess);
}

void init_light() {
  // define light properties
  GLfloat light0[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat light0_position[] = {3.0, 4.0, 4.0, 0.0};

  // enable lights 0
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  //glEnable(GL_LIGHT1);

  // load light properties
  glLightfv(GL_LIGHT0, GL_AMBIENT, light0);
  glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
  
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light0);
  glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
  
  glLightfv(GL_LIGHT0, GL_SPECULAR, light0);
  glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
  
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
}
