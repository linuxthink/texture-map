#ifndef GLUT_FUNCTION_H_
#define GLUT_FUNCTION_H_
#include "mp3.h"

void glut_reshape (int w, int h);
void glut_timer(int v);
void glut_keyboard(unsigned char key, int x, int y);
void glut_keyboard_special(int key, int x, int y);
void glut_mouse(int button, int state, int x, int y);

#endif
