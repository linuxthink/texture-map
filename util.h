#ifndef UTIL_H_
#define UTIL_H_
#include "mp3.h"

// string manipulation
void substr(char* str, char* substr, int from, int len);
int strsplit(const char *original, char *delimiter, char ***value);
int prefix_cmp(const char *input, const char *prefix);

// matrix manipulation
void vector3_dot_vector3(GLdouble *a, GLdouble *b, GLdouble *c);
void vector3_cross_vector3(GLdouble *a, GLdouble *b, GLdouble *c);
void vector3_a_vector3(GLdouble *a, GLdouble *b, GLdouble *c);
void vector3_s_vector3(GLdouble *a, GLdouble *b, GLdouble *c);
void normalize_vector3(GLdouble *a);
void matrix33_m_vector3(GLdouble (*a)[3], GLdouble *b, GLdouble *c);
void print_matrix1(GLdouble *input);
void print_matrix3(GLdouble (*input)[3]);

// clean up functions
void free_2d_array_char(char **value, int count);
void free_2d_array_int(int **value, int count);
void free_2d_array_glfloat(GLfloat **value, int count);
void free_2d_array_gldouble(GLdouble **value, int count);

#endif
