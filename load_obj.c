#include "mp3.h"
#include "load_obj.h"
#include "util.h"
extern GLdouble vertex_max_y;

int load_obj_vertex(const char *file_name,  GLdouble ***vertex) {
  int vertex_no = 0;
  char buffer[100];
  GLdouble **vertex_data;
  int i;
  
  FILE *fp;
  fp = fopen(file_name, "r");
  if (fp == NULL) {
    perror ("Error opening file");
  } else {
    while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
      if (prefix_cmp(buffer, "v") == 0) {
        vertex_no++;
      }
    }
    fclose (fp);
  }
  
  // allocate memory
  vertex_data = malloc(vertex_no * sizeof(int *));
  for (i = 0; i < vertex_no; i++) {
    vertex_data[i] = malloc(3 * sizeof(int *));
  }
  
  // write value
  fp = fopen(file_name, "r");
  int current = 0;
  if (fp == NULL) {
    perror ("Error opening file");
  } else {
    while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
      if (prefix_cmp(buffer, "v") == 0) {
        char **token;
        int token_no = strsplit(buffer, " ", &token);
        vertex_data[current][0] = atof(token[1]);
        vertex_data[current][1] = atof(token[2]);
        vertex_data[current][2] = atof(token[3]);
        if (vertex_data[current][1] > vertex_max_y) {
          vertex_max_y = vertex_data[current][1];
        }
        current++;
        free_2d_array_char(token, token_no);
      }
    }
    fclose (fp);
  }
  
  *vertex = vertex_data;
  return vertex_no;
}

int load_obj_face(const char *file_name,  int ***face) {
  int face_no = 0;
  char buffer[100];
  int **face_data;
  int i;
  
  FILE *fp;
  fp = fopen(file_name, "r");
  if (fp == NULL) {
    perror ("Error opening file");
  } else {
    while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
      if (prefix_cmp(buffer, "f") == 0) {
        face_no++;
      }
    }
    fclose (fp);
  }
  
  // allocate memory
  face_data = malloc(face_no * sizeof(int *));
  for (i = 0; i < face_no; i++) {
    face_data[i] = malloc(3 * sizeof(int *));
  }
  
  // write value
  fp = fopen(file_name, "r");
  int current = 0;
  if (fp == NULL) {
    perror ("Error opening file");
  } else {
    while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
      if (prefix_cmp(buffer, "f") == 0) {
        char **token;
        int token_no = strsplit(buffer, " ", &token);
        face_data[current][0] = atoi(token[1]);
        face_data[current][1] = atoi(token[2]);
        face_data[current][2] = atoi(token[3]);
        current++;
        free_2d_array_char(token, token_no);
      }
    }
    fclose (fp);
  }
  
  *face = face_data;
  return face_no;
}









