#ifndef TEXTURE_H_
#define TEXTURE_H_
#include "mp3.h"
#include "soil/SOIL.h" // include soil library

struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    char *data;
};
typedef struct Image Image;

int LoadGLTextures();
void compute_and_store_vertex_texture();
void get_texture_by_vertex_index(int index, GLdouble *texture_coordinate);

#endif
