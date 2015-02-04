// display function
#include "display.h"
#include "load_obj.h"
extern int face_no;
extern GLdouble **teapot_vertex;
extern GLdouble **teapot_vertex_normal;
extern GLdouble **teapot_vertex_texture;
extern int **teapot_face;
extern GLdouble direction_x;
extern GLdouble direction_y;;

void display(void) {
  int i;
  
  // put your OpenGL display commands here
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  // reset OpenGL transformation matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity(); // reset transformation matrix to identity
  
  // setup look at transformation
  gluLookAt(0.0, 3.0, 6.0, 0.0, 1.5, 0.0, 0.0, 1.0, 0.0);
  
  glRotatef(direction_x, 1.0f, 0.0f, 0.0f);
  glRotatef(direction_y, 0.0f, 1.0f, 0.0f);
  
  //glColor3f(1.0,0.0,0.0); // set current color to Red
  glBegin(GL_TRIANGLES);
    for (i = 0; i < face_no; i++) {
      glMultiTexCoord2dvARB (GL_TEXTURE0_ARB, teapot_vertex_texture[teapot_face[i][0]-1]);
      glNormal3dv(teapot_vertex_normal[teapot_face[i][0]-1]);
      glTexCoord2dv(teapot_vertex_texture[teapot_face[i][0]-1]);
      glVertex3dv(teapot_vertex[teapot_face[i][0]-1]);
      
      glMultiTexCoord2dvARB (GL_TEXTURE0_ARB, teapot_vertex_texture[teapot_face[i][1]-1]);
      glNormal3dv(teapot_vertex_normal[teapot_face[i][1]-1]);
      glTexCoord2dv(teapot_vertex_texture[teapot_face[i][1]-1]);
      glVertex3dv(teapot_vertex[teapot_face[i][1]-1]);
      
      glMultiTexCoord2dvARB (GL_TEXTURE0_ARB, teapot_vertex_texture[teapot_face[i][2]-1]);
      glNormal3dv(teapot_vertex_normal[teapot_face[i][2]-1]);
      glTexCoord2dv(teapot_vertex_texture[teapot_face[i][2]-1]);
      glVertex3dv(teapot_vertex[teapot_face[i][2]-1]);
    }
  glEnd();

  glFlush();
  glutSwapBuffers();  // swap front/back framebuffer to avoid flickering
}
