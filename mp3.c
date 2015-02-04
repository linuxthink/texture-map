///////////////////////////////
// CS418 MP3 Teapot contest
// Lao Yixing (ylao2)
// Main Program
///////////////////////////////

#include "mp3.h"
#include "display.h"
#include "load_obj.h"
#include "glut_function.h"
#include "util.h"
#include "normal.h"
#include "texture.h"
#include "lighting.h"
#include "soil/SOIL.h" // include soil library

// global variables structure
int vertex_no;
int face_no;
GLdouble **teapot_vertex;
GLdouble **teapot_vertex_normal;
GLdouble **teapot_vertex_texture;
GLdouble vertex_max_y = 0;
int **teapot_face;
GLuint texture[2]; // texture[0] teapot surface, texture[1] environment
GLdouble direction_x = 0.0f;
GLdouble direction_y = 0.0f;
char *teapot_file_name = "teapot_0.obj";
int nFPS = 60;
float fRotateAngle = 2.0f;
int auto_animation = 1;

void init() {
  
  glewExperimental = GL_TRUE; 
  glewInit();
  // load data
  vertex_no = load_obj_vertex(teapot_file_name, &teapot_vertex);
  face_no = load_obj_face(teapot_file_name, &teapot_face);
  
  // clear color
  glClearColor(0.10f,0.10f,0.10f,1.0f); // clear color is gray
  
  // depth
  glClearDepth(1.0);              // Enables Clearing Of The Depth Buffer
  glDepthFunc(GL_LESS);           // The Type Of Depth Test To Do
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  
  // material
  init_material();
  
  // lighting
  init_light();
  
  // texture
  if (LoadGLTextures() == -1) {
    perror("failed to load texture file\n");
    exit(1);
  }
  
  // polygon mode
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  
  // others
  glEnable(GL_NORMALIZE);
  
  glDepthMask(GL_TRUE);
}

void global_free() {
  free_2d_array_gldouble(teapot_vertex, vertex_no);
  free_2d_array_gldouble(teapot_vertex_normal, vertex_no);
  free_2d_array_gldouble(teapot_vertex_texture, vertex_no);
  free_2d_array_int(teapot_face, face_no);
}

int main(int argc, char* argv[]) {
  welcome_message();
  
  glutInit(&argc, (char**)argv);

  // 1 init glut
  // double-buffering & RGB color buffer & depth test
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize (600, 600);
  glutInitWindowPosition (100, 100);
  glutCreateWindow ((const char*)"MP3 Teapot");

  // 2 init OpenGL
  init();
  
  // 3 compute and store pervertex surface normal
  compute_and_store_vertex_normal();
  compute_and_store_vertex_texture();

  // 4 call glut functions
  glutDisplayFunc(display);  // called when draw
  glutReshapeFunc(glut_reshape);  // called when change window size
  glutKeyboardFunc(glut_keyboard); // called when received keyboard
  glutSpecialFunc(glut_keyboard_special);
  glutMouseFunc(glut_mouse);     // called when received mouse
  glutTimerFunc(100,glut_timer,nFPS); // a periodic timer. used for animation
  glutMainLoop(); // start the main message-callback loop  
  
  return 0;
}

void welcome_message() {
  printf("******************************************\n");
  printf("Welcome to MP3 Teapot Contest\n");
  printf("By Lao Yixing (ylao2)\n");
  printf("Space: start and stop auto animation\n");
  printf("a or left arrow: roll left\n");
  printf("d or right arrow: roll right\n");
  printf("w or up arrow: roll up\n");
  printf("s or down arrow: roll down\n");
  printf("******************************************\n");
}


