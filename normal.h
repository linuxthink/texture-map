#ifndef NORMAL_H_
#define NORMAL_H_
#include "mp3.h"
void get_vertex_normal(int v_index, GLdouble *vertex_normal);
void get_face_normal_by_index(int v, int a, int b, GLdouble *face_normal);
void get_face_normal(GLdouble *v, GLdouble *a, GLdouble *b, 
                     GLdouble *face_normal);
void compute_and_store_vertex_normal();

#endif
