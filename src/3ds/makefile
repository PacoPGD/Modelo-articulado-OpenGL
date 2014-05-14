GL_LIBS=-lGL -lglut -lGLU
SDLIMAGE_LIBS=-lSDL_image

SDL_INCLUDE=/usr/include/SDL

3dsplay: 3dsplay.c atmosphere.h background.h camera.h chunk.h ease.c file.c io.c light.c material.h matrix.h mesh.h node.h quat.h shadow.h tcb.h tracks.h vector.c viewport.c atmosphere.c background.c camera.c chunk.c chunktable.h ease.h file.h io.h light.h material.c matrix.c mesh.c node.c quat.c shadow.c tcb.c tracks.c types.h vector.h viewport.h
	g++ *.c -o 3dsplay -I$(SDL_INCLUDE) -O0 -g3  $(SDLIMAGE_LIBS) $(GL_LIBS)
clean:
	rm 3dsplay *.o *~ -f
