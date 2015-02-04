#include "util.h"
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define PI 3.14159265

////////////////////////// string manipulation /////////////////////////////

/**
* return 0 if prefix is the same
* otherwise not the same
*/
int prefix_cmp(const char *input, const char *prefix) {
  int length = strlen(prefix);
  char *input_sub = malloc(sizeof(char) * length + 1);
  memcpy(input_sub, &input[0], length);
  input_sub[length] = '\0';
  int result = strcmp(input_sub, prefix);
  if (input_sub) {
    free(input_sub);
  }
  return result;
}

void substr(char* str, char* substr, int from, int len) {
  memcpy(substr, &str[from], len);
  substr[len] = '\0';
}

int strsplit(const char *original, char *delimiter, char ***value) {
  int count = 0;
  char *token;
  char *input = (char *) malloc(strlen(original) * sizeof(original) + 8);
  strcpy(input, original);

  token = strtok(input, delimiter);
  while (token != NULL) {
    count++;
    token = strtok (NULL, delimiter);
  }
  *value = malloc(count * sizeof (char *));

  free(input);
  input = (char *) malloc(strlen(original) * sizeof(original) + 8);
  strcpy(input, original);

  count = 0;
  token = strtok(input, delimiter);
  while (token != NULL) {
    (*value)[count] = malloc(strlen(token) * sizeof(char) + 8);
    strcpy((*value)[count], token);
    count++;
    token = strtok (NULL, delimiter);
  }
  if (count == 0) {
    *value = NULL;
  }

  free(input);
  return count;
}

///////////////////////// matrix manipulation //////////////////////////////
// dot product
void vector3_dot_vector3(GLdouble *a, GLdouble *b, GLdouble *c) {
  c[0] = a[0]*b[0];
  c[1] = a[1]*b[1];
  c[2] = a[2]*b[2];
}

// cross product
void vector3_cross_vector3(GLdouble *a, GLdouble *b, GLdouble *c) {
  c[0] = a[1]*b[2] - a[2]*b[1];
  c[1] = a[2]*b[0] - a[0]*b[2];
  c[2] = a[0]*b[1] - a[1]*b[0];
}

// vector addition
void vector3_a_vector3(GLdouble *a, GLdouble *b, GLdouble *c)  {
  c[0] = a[0] + b[0];
  c[1] = a[1] + b[1];
  c[2] = a[2] + b[2];
}

// vector substraction
void vector3_s_vector3(GLdouble *a, GLdouble *b, GLdouble *c)  {
  c[0] = a[0] - b[0];
  c[1] = a[1] - b[1];
  c[2] = a[2] - b[2];
}

// normalize to unit vector
void normalize_vector3(GLdouble *a) {
  GLdouble sum = a[0]*a[0] + a[1]*a[1] + a[2]*a[2];
  sum = sqrt(sum);
  a[0] = a[0] / sum;
  a[1] = a[1] / sum;
  a[2] = a[2] / sum;
}

// vector multiplication
void matrix33_m_vector3(GLdouble (*a)[3], GLdouble *b, GLdouble *c) {
  GLdouble d[3];
  d[0] = b[0];
  d[1] = b[1];
  d[2] = b[2];
  c[0] = a[0][0]*d[0] + a[0][1]*d[1] + a[0][2]*d[2];
  c[1] = a[1][0]*d[0] + a[1][1]*d[1] + a[1][2]*d[2];
  c[2] = a[2][0]*d[0] + a[2][1]*d[1] + a[2][2]*d[2];
}

// print 1 * 3 matrix
void print_matrix1(GLdouble *input) {
  printf("%f ", input[0]);
  printf("%f ", input[1]);
  printf("%f\n", input[2]);
}

// print 3 * 3 matrix
void print_matrix3(GLdouble (*input)[3]) {
  printf("%f ", input[0][0]);
  printf("%f ", input[0][1]);
  printf("%f \n", input[0][2]);
  printf("%f ", input[1][0]);
  printf("%f ", input[1][1]);
  printf("%f \n", input[1][2]);
  printf("%f ", input[2][0]);
  printf("%f ", input[2][1]);
  printf("%f \n", input[2][2]);
}

// rotate about the about vector
void rotate_about(GLdouble *about, GLdouble degree, GLdouble *input, 
                  GLdouble *output) {
  GLdouble sin_value = sin (degree*PI/180);
  GLdouble cos_value = cos (degree*PI/180);
  GLdouble up[3] = {0.0, 0.0, 1.0};
  GLdouble side[3], up_[3];
  normalize_vector3(about);
  vector3_cross_vector3(up, about, side);
  normalize_vector3(side);
  vector3_cross_vector3(about, side, up_);
  normalize_vector3(up_);
  GLdouble r_matrix[3][3] = {{side[0],  side[1],  side[2]},
                           {up_[0],   up_[1],   up_[2]},
                           {about[0], about[1], about[2]}};
  GLdouble r_matrix_r[3][3] = {{side[0], up_[0], about[0]},
                             {side[1], up_[1], about[1]},
                             {side[2], up_[2], about[2]}};
  //print_matrix3(r_matrix_r);
  GLdouble r_core_matrix[3][3] = {{cos_value, -sin_value, 0},
                                {sin_value, cos_value,  0},
                                {0,         0,          1}};
  //print_matrix3(r_core_matrix);
  matrix33_m_vector3(r_matrix, input, output);
  matrix33_m_vector3(r_core_matrix, output, output);
  matrix33_m_vector3(r_matrix_r, output, output);
}


///////////////////////// clean up functions //////////////////////////////

void free_2d_array_char(char **value, int count) {
  if (value) {
    int i;
    for (i = 0; i < count; i++) {
      free(value[i]);
      value[i] = NULL;
    }
    free(value);
  }
}

void free_2d_array_int(int **value, int count) {
  if (value) {
    int i;
    for (i = 0; i < count; i++) {
      free(value[i]);
      value[i] = NULL;
    }
    free(value);
  }
}

void free_2d_array_glfloat(GLfloat **value, int count) {
  if (value) {
    int i;
    for (i = 0; i < count; i++) {
      free(value[i]);
      value[i] = NULL;
    }
    free(value);
  }
}

void free_2d_array_gldouble(GLdouble **value, int count) {
  if (value) {
    int i;
    for (i = 0; i < count; i++) {
      free(value[i]);
      value[i] = NULL;
    }
    free(value);
  }
}

