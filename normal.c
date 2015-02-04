#include "normal.h"
#include "util.h"

extern int vertex_no;
extern int face_no;
extern GLdouble **teapot_vertex;
extern GLdouble **teapot_vertex_normal;
extern int **teapot_face;


void compute_and_store_vertex_normal() {
  int i;
  teapot_vertex_normal = malloc(vertex_no * sizeof(GLdouble *));
  for (i = 0; i < vertex_no; i++) {
    teapot_vertex_normal[i] = malloc(3 * sizeof(GLdouble *));
  }
  for (i = 1; i <= vertex_no; i++) {
    get_vertex_normal(i, teapot_vertex_normal[i-1]);
  }
}

/**
 * input: the index of the vertex (starting from 1, so need to -1!!)
 *        the function will:
 *        (1) find all surfaces containing the vertex
 *        (2) compute the surface normal in order
 *        (3) sum up and normalized the surface normals
 * output: the vertex_normal
 */
void get_vertex_normal(int v_index, GLdouble *vertex_normal) {
  
  int target_face_no = 0;
  int i;
  
  // 1 count the target face number
  for (i = 0; i < face_no; i++) {
    if (teapot_face[i][0]==v_index || 
        teapot_face[i][1]==v_index ||
        teapot_face[i][2]==v_index) {
      target_face_no++;
    }
  }
  
  // 2 allocate memory for the target face, target face normal
  int **target_face;
  target_face = malloc(target_face_no * sizeof(int *));
  for (i = 0; i < target_face_no; i++) {
    target_face[i] = malloc(3 * sizeof(int *));
  }
  GLdouble **target_face_normal;
  target_face_normal = malloc(target_face_no * sizeof(GLdouble *));
  for (i = 0; i < target_face_no; i++) {
    target_face_normal[i] = malloc(3 * sizeof(GLdouble *));
  }
  
  // 3 write all target face
  int current = 0;
  for (i = 0; i < face_no; i++) {
    if (teapot_face[i][0]==v_index || 
        teapot_face[i][1]==v_index ||
        teapot_face[i][2]==v_index) {
      target_face[current][0] = teapot_face[i][0];
      target_face[current][1] = teapot_face[i][1];
      target_face[current][2] = teapot_face[i][2];
      current++;
    }
  }
  
  // 4 get face normal for each target face
  for (i = 0; i < target_face_no; i++) {
    get_face_normal_by_index(target_face[i][0], target_face[i][1],
                             target_face[i][2], target_face_normal[i]);
  }

  // 5 sum up and normalize
  GLdouble total_normal[3];
  total_normal[0] = 0.00;
  total_normal[1] = 0.00;
  total_normal[2] = 0.00;
  for (i = 0; i < target_face_no; i++) {
    total_normal[0] = total_normal[0] + target_face_normal[i][0];
    total_normal[1] = total_normal[1] + target_face_normal[i][1];
    total_normal[2] = total_normal[2] + target_face_normal[i][2];
  }
  normalize_vector3(total_normal);
  vertex_normal[0] = total_normal[0];
  vertex_normal[1] = total_normal[1];
  vertex_normal[2] = total_normal[2];
  
  // 6 clean up
  free_2d_array_int(target_face, target_face_no);
  free_2d_array_gldouble(target_face_normal, target_face_no);
}

/** get the normal of a face by the vertex index
 *  input: the index of the vertex (starting from 1, so need to -1!!)
 *         v the main vertex coordinates
 *         a, b the other two vertex coordinates
 *  output: the unit normal of the surface
 *          based on vertex(ab) cross vertex(bc)
 *  all inputs and output need pre-allocated memory (global variable) 
 */
void get_face_normal_by_index(int v, int a, int b, GLdouble *face_normal) {
  get_face_normal(teapot_vertex[v - 1],
                  teapot_vertex[a - 1], 
                  teapot_vertex[b - 1],
                  face_normal);
}

/** get the normal of a face
 * input: the coordinate of three vertex
 *        v the main vertex coordinates
 *        a, b the other two vertex coordinates
 * output: the unit normal of the surface
 *         based on vertex(ab) cross vertex(bc)
 * all inputs and output need pre-allocated memory         
 */ 
void get_face_normal(GLdouble *v, GLdouble *a, GLdouble *b, 
                     GLdouble *face_normal) {
  GLdouble va[3];
  GLdouble vb[3];
  vector3_s_vector3(a, v, va);
  vector3_s_vector3(b, v, vb);
  vector3_cross_vector3(va, vb, face_normal);
  normalize_vector3(face_normal);
}
