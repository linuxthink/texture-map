#include "texture.h"
#include "mp3.h"
#include "soil/SOIL.h"

extern GLuint texture[2];
extern int vertex_no;
extern GLdouble **teapot_vertex;
extern GLdouble **teapot_vertex_texture;
extern GLdouble vertex_max_y;

// contains code from:
// http://nehe.gamedev.net/tutorial/lesson_06_texturing_update/47002/

// to do textures:
// 1) set correct parameters to opengl
// 2) load the correct textue
// 3) specify the texture to use in each vertex, using a certain function

int LoadGLTextures() {
  // load an image file directly as a new OpenGL texture 0
  texture[0] = SOIL_load_OGL_texture("qinghuaci.png", SOIL_LOAD_AUTO,
                                     SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | 
                                     SOIL_FLAG_INVERT_Y |
                                     SOIL_FLAG_NTSC_SAFE_RGB | 
                                     SOIL_FLAG_COMPRESS_TO_DXT);   
  texture[1] = SOIL_load_OGL_texture("forest.jpg", SOIL_LOAD_AUTO,
                                     SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS  | 
                                     SOIL_FLAG_INVERT_Y |
                                     SOIL_FLAG_NTSC_SAFE_RGB | 
                                     SOIL_FLAG_COMPRESS_TO_DXT); 
  if(texture[0] == 0 || texture[1] == 0)
    return -1;
  
  ////////////////////// texture 0 //////////////////////////
  glActiveTextureARB (GL_TEXTURE0_ARB);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture[0]);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  
  ////////////////////// texture 1 //////////////////////////
  glActiveTextureARB (GL_TEXTURE1_ARB);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture[1]);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
  glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
  glEnable(GL_TEXTURE_GEN_S);
  glEnable(GL_TEXTURE_GEN_T);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  
  return 1; // Return Success
}

void compute_and_store_vertex_texture() {
  int i;
  teapot_vertex_texture = malloc(vertex_no * sizeof(GLdouble *));
  for (i = 0; i < vertex_no; i++) {
    teapot_vertex_texture[i] = malloc(2 * sizeof(GLdouble *));
  }
  for (i = 1; i <= vertex_no; i++) {
    get_texture_by_vertex_index(i, teapot_vertex_texture[i-1]);
    //printf("%f, %f \n", teapot_vertex_texture[i-1][0],teapot_vertex_texture[i-1][1]);
  }
}

void get_texture_by_vertex_index(int index, GLdouble *texture_coordinate) {
  GLdouble x = teapot_vertex[index-1][0];
  GLdouble y = teapot_vertex[index-1][1];
  GLdouble z = teapot_vertex[index-1][2];

  GLdouble theta = atan2(z, x);
  if (theta < 0)
    theta = -theta;
  GLdouble s = (theta + PI)/ (2 * PI);
  GLdouble t = y / vertex_max_y;

  texture_coordinate[0] = s;
  texture_coordinate[1] = t;
}

void get_environment_by_vertex_index(int index, GLdouble *texture_coordinate) {
  GLdouble x = teapot_vertex[index-1][0];
  GLdouble y = teapot_vertex[index-1][1];
  GLdouble z = teapot_vertex[index-1][2];

  GLdouble theta = atan2(z, x);
  if (theta < 0)
    theta = -theta;
  GLdouble s = (theta + PI)/ (2 * PI);
  GLdouble t = y / vertex_max_y;

  texture_coordinate[0] = s;
  texture_coordinate[1] = t;
}






