#ifndef _3DS_PLAY_
#define _3DS_PLAY_

#define USE_SDL 1

#include "file.h"
#include "camera.h"
#include "mesh.h"
#include "node.h"
#include "material.h"
#include "matrix.h"
#include "vector.h"
#include "light.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

// OS X has a different path than everyone else
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifdef	USE_SDL
#include <SDL_image.h>
#endif

// texture size: by now minimum standard
#define	TEX_XSIZE	1024
#define	TEX_YSIZE	1024

#define _3DS_COLOR 	1
#define _3DS_TEXTURE     2

struct _player_texture
{
  int valid; // was the loading attempt successful ? 
#ifdef	USE_SDL
  SDL_Surface *bitmap;
#else
  void *bitmap;
#endif
  GLuint tex_id; //OpenGL texture ID
  float scale_x, scale_y; // scale the texcoords, as OpenGL thinks in TEX_XSIZE and TEX_YSIZE
};

typedef struct _player_texture Player_texture; 

#define	NA(a)	(sizeof(a)/sizeof(a[0]))

#ifndef	MIN
#define	MIN(a,b) ((a)<(b)?(a):(b))
#define	MAX(a,b) ((a)>(b)?(a):(b))
#endif

Lib3dsFile* 
load_model(const char* filepath);

void *convert_to_RGB_Surface(SDL_Surface *bitmap);

void
render_node(Lib3dsNode *node, char* datapath, Lib3dsFile* file, int mode);

void
display(char* datapath, Lib3dsFile* file, int mode);

void decompose_datapath(char* datapath, char* filename, const char *fn);



#endif