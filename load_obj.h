#ifndef LOAD_OBJ_H_
#define LOAD_OBJ_H_
#define BUFFER_SIZE 128

//void load_obj(const char *file_name,  GLfloat ***vertex, GLfloat ***face);
int load_obj_vertex(const char *file_name,  GLdouble ***vertex);
int load_obj_face(const char *file_name,  int ***face);

#endif
