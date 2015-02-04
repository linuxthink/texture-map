#include "glut_function.h"
extern int nFPS;
extern float fRotateAngle;
extern GLdouble direction_x;
extern GLdouble direction_y;
extern int auto_animation;

// reshape when window size changed
void glut_reshape (int w, int h) {
  glViewport(0, 0, w, h); // reset viewport ( drawing screen ) size
  float fAspect = ((float)w)/h; // reset OpenGL projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70.0f, fAspect, 0.1f, 30.0f);
}

void glut_timer(int v) {
  if (auto_animation == 1) {
    direction_x = direction_x - fRotateAngle / 3;
    direction_y = direction_y - fRotateAngle / 1.5; // change rotation angles  
//    printf("direction_x: %f\n", direction_x);
//    printf("direction_y: %f\n", direction_y);
  }
  glutPostRedisplay(); // trigger display function by sending redraw into message queue
  glutTimerFunc(1000/nFPS, glut_timer, v); // restart timer again
}

// handle keyboard function
void glut_keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 27: // ESC
      printf("exit program.\n");
      global_free();
      exit(0);
      break;
    case 32: // Space
      if (auto_animation == 1) {
        printf("Auto animation stoped. Press [Space] to start auto animation.\n");
        auto_animation = 0;
      } else {
        printf("Auto animation started. Press [Space] to stop auto animation.\n");
        auto_animation = 1;
      }
      break;
    case 'a': // left
      //printf("Roll left\n");
      if (auto_animation == 1) {
        auto_animation = 0;
        printf("Auto animation stoped. Press [Space] to start auto animation.\n");
      }
      direction_y = direction_y + fRotateAngle;
      break;
    case 'd': // right
      //printf("Roll left\n");
      if (auto_animation == 1) {
        auto_animation = 0;
        printf("Auto animation stoped. Press [Space] to start auto animation.\n");
      }
      direction_y = direction_y - fRotateAngle;
      break;
    case 'w': // up
      //printf("Roll up\n");
      if (auto_animation == 1) {
        auto_animation = 0;
        printf("Auto animation stoped. Press [Space] to start auto animation.\n");
      }
      direction_x = direction_x - fRotateAngle;
      break;
    case 's': // down
      //printf("Roll down\n");
      if (auto_animation == 1) {
        auto_animation = 0;
        printf("Auto animation stoped. Press [Space] to start auto animation.\n");
      }
      direction_x = direction_x + fRotateAngle;
      break;
    default:
      break;
  }
}

// handles special key
void glut_keyboard_special(int key, int x, int y) {
  if (key == GLUT_KEY_LEFT)
    glut_keyboard('a', x, y);
  else if (key == GLUT_KEY_RIGHT)
    glut_keyboard('d', x, y);
  else if (key == GLUT_KEY_UP)
    glut_keyboard('w', x, y);
  else if (key == GLUT_KEY_DOWN)
    glut_keyboard('s', x, y);
}


void glut_mouse(int button, int state, int x, int y) {
  // process your mouse control here
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
  }
}

