/*
* The 3D Studio File Format Library
* Copyright (C) 1996-2007 by Jan Eric Kyprianidis <www.lib3ds.org>
* All rights reserved.
*
* This program is  free  software;  you can redistribute it and/or modify it
* under the terms of the  GNU Lesser General Public License  as published by 
* the  Free Software Foundation;  either version 2.1 of the License,  or (at 
* your option) any later version.
*
* This  program  is  distributed in  the  hope that it will  be useful,  but
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
* or  FITNESS FOR A  PARTICULAR PURPOSE.  See the  GNU Lesser General Public  
* License for more details.
*
* You should  have received  a copy of the GNU Lesser General Public License
* along with  this program;  if not, write to the  Free Software Foundation,
* Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*
* $Id: 3dsplay.c,v 1.14 2007/06/18 06:51:53 jeh Exp $
*/

#include "3dsplay.h"

/*!
* Load the model from .3ds file.
*/
Lib3dsFile* 
load_model(const char* filepath)
{
  Lib3dsVector bmin, bmax;
  float	sx, sy, sz;
  float	cx, cy, cz;
  float size;
  Lib3dsFile* file;
  const char* camera=0;
  
  file=lib3ds_file_load(filepath);
  if (!file) {
    puts("3dsplayer: Error: Loading 3DS file failed.\n");
    exit(1);
  }

  /* No nodes?  Fabricate nodes to display all the meshes. */
  if( !file->nodes )
  {
    Lib3dsMesh *mesh;
    Lib3dsNode *node;

    for(mesh = file->meshes; mesh != NULL; mesh = mesh->next)
    {
      node = lib3ds_node_new_object();
      strcpy(node->name, mesh->name);
      node->parent_id = LIB3DS_NO_PARENT;
      lib3ds_file_insert_node(file, node);
    }
  }

  lib3ds_file_eval(file, 1.0f);
  lib3ds_file_bounding_box_of_nodes(file, LIB3DS_TRUE, LIB3DS_FALSE, LIB3DS_FALSE, bmin, bmax);
  sx = bmax[0] - bmin[0];
  sy = bmax[1] - bmin[1];
  sz = bmax[2] - bmin[2];
  size = MAX(sx, sy); size = MAX(size, sz);
  cx = (bmin[0] + bmax[0])/2;
  cy = (bmin[1] + bmax[1])/2;
  cz = (bmin[2] + bmax[2])/2;


  /* No cameras in the file?  Add four */

  if( !file->cameras ) {

    /* Add some cameras that encompass the bounding box */

    Lib3dsCamera *camera = lib3ds_camera_new("Camera_X");
    camera->target[0] = cx;
    camera->target[1] = cy;
    camera->target[2] = cz;
    memcpy(camera->position, camera->target, sizeof(camera->position));
    camera->position[0] = bmax[0] + 1.5 * MAX(sy,sz);
    camera->near_range = ( camera->position[0] - bmax[0] ) * .5;
    camera->far_range = ( camera->position[0] - bmin[0] ) * 2;
    lib3ds_file_insert_camera(file, camera);

    /* Since lib3ds considers +Y to be into the screen, we'll put
    * this camera on the -Y axis, looking in the +Y direction.
    */
    camera = lib3ds_camera_new("Camera_Y");
    camera->target[0] = cx;
    camera->target[1] = cy;
    camera->target[2] = cz;
    memcpy(camera->position, camera->target, sizeof(camera->position));
    camera->position[1] = bmin[1] - 1.5 * MAX(sx,sz);
    camera->near_range = ( bmin[1] - camera->position[1] ) * .5;
    camera->far_range = ( bmax[1] - camera->position[1] ) * 2;
    lib3ds_file_insert_camera(file, camera);

    camera = lib3ds_camera_new("Camera_Z");
    camera->target[0] = cx;
    camera->target[1] = cy;
    camera->target[2] = cz;
    memcpy(camera->position, camera->target, sizeof(camera->position));
    camera->position[2] = bmax[2] + 1.5 * MAX(sx,sy);
    camera->near_range = ( camera->position[2] - bmax[2] ) * .5;
    camera->far_range = ( camera->position[2] - bmin[2] ) * 2;
    lib3ds_file_insert_camera(file, camera);

    camera = lib3ds_camera_new("Camera_ISO");
    camera->target[0] = cx;
    camera->target[1] = cy;
    camera->target[2] = cz;
    memcpy(camera->position, camera->target, sizeof(camera->position));
    camera->position[0] = bmax[0] + .75 * size;
    camera->position[1] = bmin[1] - .75 * size;
    camera->position[2] = bmax[2] + .75 * size;
    camera->near_range = ( camera->position[0] - bmax[0] ) * .5;
    camera->far_range = ( camera->position[0] - bmin[0] ) * 3;
    lib3ds_file_insert_camera(file, camera);
  }


  /* No lights in the file?  Add some. */

  if (file->lights == NULL)
  {
    Lib3dsLight *light;

    light = lib3ds_light_new("light0");
    light->spot_light = 0;
    light->see_cone = 0;
    light->color[0] = light->color[1] = light->color[2] = .6;
    light->position[0] = cx + size * .75;
    light->position[1] = cy - size * 1.;
    light->position[2] = cz + size * 1.5;
    light->position[3] = 0.;
    light->outer_range = 100;
    light->inner_range = 10;
    light->multiplier = 1;
    lib3ds_file_insert_light(file, light);

    light = lib3ds_light_new("light1");
    light->spot_light = 0;
    light->see_cone = 0;
    light->color[0] = light->color[1] = light->color[2] = .3;
    light->position[0] = cx - size;
    light->position[1] = cy - size;
    light->position[2] = cz + size * .75;
    light->position[3] = 0.;
    light->outer_range = 100;
    light->inner_range = 10;
    light->multiplier = 1;
    lib3ds_file_insert_light(file, light);

    light = lib3ds_light_new("light2");
    light->spot_light = 0;
    light->see_cone = 0;
    light->color[0] = light->color[1] = light->color[2] = .3;
    light->position[0] = cx;
    light->position[1] = cy + size;
    light->position[2] = cz + size;
    light->position[3] = 0.;
    light->outer_range = 100;
    light->inner_range = 10;
    light->multiplier = 1;
    lib3ds_file_insert_light(file, light);

  }

  if (!file->cameras) {
    fputs("3dsplayer: Error: No Camera found.\n", stderr);
    lib3ds_file_free(file);
    file=0;
    exit(1);
  }
  //if (!camera) {
    camera=file->cameras->name;
  //}

  lib3ds_file_eval(file,0.);
  
  return file;
}



#ifdef  USE_SDL
/**
* Convert an SDL bitmap for use with OpenGL.
*
* Written by Gernot < gz@lysator.liu.se >
*/
void *convert_to_RGB_Surface(SDL_Surface *bitmap)
{
  unsigned char *pixel = (unsigned char *)malloc(sizeof(char) * 4 * bitmap->h * bitmap->w); 
  int soff = 0;   
  int doff = 0;   
  int x, y;
  unsigned char *spixels = (unsigned char *)bitmap->pixels;
  SDL_Palette *pal = bitmap->format->palette; 

  for (y = 0; y < bitmap->h; y++)
    for (x = 0; x < bitmap->w; x++)
    {
      SDL_Color* col = &pal->colors[spixels[soff]];

      pixel[doff] = col->r; 
      pixel[doff+1] = col->g; 
      pixel[doff+2] = col->b; 
      pixel[doff+3] = 255; 
      doff += 4; 
      soff++;
    }

    return (void *)pixel; 
}
#endif




/*!
* Render node recursively, first children, then parent.
* Each node receives its own OpenGL display list.
*/
void
render_node(Lib3dsNode *node, char* datapath, Lib3dsFile* file, int mode)
{
  ASSERT(file);

  {
    Lib3dsNode *p;
    for (p=node->childs; p!=0; p=p->next) {
      render_node(p,datapath,file,mode);
    }
  }
  if (node->type==LIB3DS_OBJECT_NODE) {
    Lib3dsMesh *mesh;

    if (strcmp(node->name,"$$$DUMMY")==0) {
      return;
    }

    mesh = lib3ds_file_mesh_by_name(file, node->data.object.morph);
    if( mesh == NULL )
      mesh = lib3ds_file_mesh_by_name(file, node->name);

    if (!mesh->user.d) {
      ASSERT(mesh);
      if (!mesh) {
        return;
      }

      mesh->user.d=glGenLists(1);
      glNewList(mesh->user.d, GL_COMPILE);

      {
        unsigned p;
        Lib3dsVector *normalL=(Lib3dsVector*)malloc(3*sizeof(Lib3dsVector)*mesh->faces);
        Lib3dsMaterial *oldmat = (Lib3dsMaterial *)-1;
        {
          Lib3dsMatrix M;
          lib3ds_matrix_copy(M, mesh->matrix);
          lib3ds_matrix_inv(M);
          glMultMatrixf(&M[0][0]);
        }
        lib3ds_mesh_calculate_normals(mesh, normalL);

        for (p=0; p<mesh->faces; ++p) {
          Lib3dsFace *f=&mesh->faceL[p];
          Lib3dsMaterial *mat=0;
#ifdef	USE_SDL
          Player_texture *pt = NULL;
          int tex_mode = 0;
#endif
          if (f->material[0]) {
            mat=lib3ds_file_material_by_name(file, f->material);
          }

          if( mat != oldmat ) {
            if (mat) {
              if( mat->two_sided )
                glDisable(GL_CULL_FACE);
              else
                glEnable(GL_CULL_FACE);

              glDisable(GL_CULL_FACE);

              /* Texturing added by Gernot < gz@lysator.liu.se > */

              if (mat->texture1_map.name[0]) {		/* texture map? */
                Lib3dsTextureMap *tex = &mat->texture1_map;
                if (!tex->user.p) {		/* no player texture yet? */
                  char texname[1024];
                  pt = (Player_texture*) malloc(sizeof(*pt));
                  tex->user.p = pt;
                  //snprintf(texname, sizeof(texname), "%s/%s", datapath, tex->name);
                  strcpy(texname, datapath);
                  strcat(texname, "/");
                  strcat(texname, tex->name);
#ifdef	DEBUG
                  printf("Loading texture map, name %s\n", texname);
#endif	/* DEBUG */
#ifdef	USE_SDL
#ifdef  USE_SDL_IMG_load
                  pt->bitmap = IMG_load(texname);
		  
#else
                  pt->bitmap = IMG_Load(texname);
#endif /* IMG_Load */

#else /* USE_SDL */
                  pt->bitmap = NULL;
                  fputs("3dsplayer: Warning: No image loading support, skipping texture.\n", stderr);
#endif /* USE_SDL */
                  if (pt->bitmap) {	/* could image be loaded ? */
                    /* this OpenGL texupload code is incomplete format-wise!
                    * to make it complete, examine SDL_surface->format and
                    * tell us @lib3ds.sf.net about your improvements :-)
                    */
                    int upload_format = GL_RED; /* safe choice, shows errors */
#ifdef USE_SDL
                    int bytespp = pt->bitmap->format->BytesPerPixel;
                    void *pixel = NULL;
                    glGenTextures(1, &pt->tex_id);
#ifdef	DEBUG
                    printf("Uploading texture to OpenGL, id %d, at %d bytepp\n",
                      pt->tex_id, bytespp);
#endif	/* DEBUG */
                    if (pt->bitmap->format->palette) {
                      pixel = convert_to_RGB_Surface(pt->bitmap);
                      upload_format = GL_RGBA;
                    }
                    else {
                      pixel = pt->bitmap->pixels;
                      /* e.g. this could also be a color palette */
                      if (bytespp == 1) upload_format = GL_LUMINANCE;
                      else if (bytespp == 3) upload_format = GL_RGB;
                      else if (bytespp == 4) upload_format = GL_RGBA;
                    }
                    glBindTexture(GL_TEXTURE_2D, pt->tex_id);
                    
		    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                      TEX_XSIZE, TEX_YSIZE, 0,
                      GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		    
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
                    glTexParameteri(GL_TEXTURE_2D,
                      GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D,
                      GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                   
		    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
                    
                    glTexSubImage2D(GL_TEXTURE_2D,
                      0, 0, 0, pt->bitmap->w, pt->bitmap->h,
                      upload_format, GL_UNSIGNED_BYTE, pixel);
                    pt->scale_x = (float)pt->bitmap->w/(float)TEX_XSIZE;
                    pt->scale_y = (float)pt->bitmap->h/(float)TEX_YSIZE;
#endif /* USE_SDL */
                    pt->valid = 1;
                  }
                  else {
                    fprintf(stderr,
                      "Load of texture %s did not succeed "
                      "(format not supported !)\n",
                      texname);
                    pt->valid = 0;
                  }
                }
                else {
                  pt = (Player_texture *)tex->user.p;
                }
                tex_mode = pt->valid;
              }
              else {
                tex_mode = 0;
              }
              glMaterialfv(GL_FRONT, GL_AMBIENT, mat->ambient);
              glMaterialfv(GL_FRONT, GL_DIFFUSE, mat->diffuse);
              glMaterialfv(GL_FRONT, GL_SPECULAR, mat->specular);
              glMaterialf(GL_FRONT, GL_SHININESS, pow(2, 10.0*mat->shininess));
	      if(mode==_3DS_COLOR)
		glColor3fv(mat->diffuse);
            }
            else {
              static const Lib3dsRgba a={0.7, 0.7, 0.7, 1.0};
              static const Lib3dsRgba d={0.7, 0.7, 0.7, 1.0};
              static const Lib3dsRgba s={1.0, 1.0, 1.0, 1.0};
              glMaterialfv(GL_FRONT, GL_AMBIENT, a);
              glMaterialfv(GL_FRONT, GL_DIFFUSE, d);
              glMaterialfv(GL_FRONT, GL_SPECULAR, s);
              glMaterialf(GL_FRONT, GL_SHININESS, pow(2, 10.0*0.5));
            }
            oldmat = mat;
          }

          else if (mat != NULL && mat->texture1_map.name[0]) {
            Lib3dsTextureMap *tex = &mat->texture1_map;
            if (tex != NULL && tex->user.p != NULL) {
              pt = (Player_texture *)tex->user.p;
              tex_mode = pt->valid;
            }
          }


          {
            int i;

            if (tex_mode) {
              //printf("Binding texture %d\n", pt->tex_id);
              glEnable(GL_TEXTURE_2D);
              glBindTexture(GL_TEXTURE_2D, pt->tex_id);
            }

            glBegin(GL_TRIANGLES);
            glNormal3fv(f->normal);
            for (i=0; i<3; ++i) {
              glNormal3fv(normalL[3*p+i]);

              if (tex_mode) {
                glTexCoord2f(mesh->texelL[f->points[i]][1]*pt->scale_x,
                  pt->scale_y - mesh->texelL[f->points[i]][0]*pt->scale_y);
              }

              glVertex3fv(mesh->pointL[f->points[i]].pos);
            }
            glEnd();

            if (tex_mode)
              glDisable(GL_TEXTURE_2D);
          }
        }

        free(normalL);
      }

      glEndList();
    }

    if (mesh->user.d) {
      Lib3dsObjectData *d;

      glPushMatrix();
      d=&node->data.object;
      glMultMatrixf(&node->matrix[0][0]);
      glTranslatef(-d->pivot[0], -d->pivot[1], -d->pivot[2]);
      glCallList(mesh->user.d);
      /* glutSolidSphere(50.0, 20,20); */
      glPopMatrix();
      //if( flush )
        glFlush();
    }
  }
}


/*!
* Main display function; called whenever the scene needs to be redrawn.
*/
void
display(char* datapath, Lib3dsFile* file,int mode)
{
  Lib3dsNode *p;
  

    for (p=file->nodes; p!=0; p=p->next) {
      render_node(p, datapath, file, mode);
    }
  
  //glutSwapBuffers();
}


void decompose_datapath(char* datapath, char* filename, const char *fn)
{
  const char *ptr = strrchr(fn, '/');

  if (ptr == NULL) {
    strcpy(datapath, ".");
    strcpy(filename, fn);
  }
  else {
    strcpy(filename, ptr+1);
    strcpy(datapath, fn);
    datapath[ptr - fn] = '\0';
  }
}
