objects = src/main.o 	\
src/util/file.o			\
src/setup_opengl.o 		\
src/input.o				\
src/physics/collision.o	\
src/physics/physics.o	\
src/render/render.o		\
src/game/world.o		\
src/render/queue.o		

lib = -Llib -lglfw3 -lGL -lGLEW
CPPFLAGS = -g -Iinclude/ -Isrc/ -Wall
CC = gcc
name = test

all: $(objects)
	g++ $(objects) -o build/$(name) $(lib)
src/main.o: src/linked_list.h
src/setup_opengl.o:

src/util/file.o:

src/input.o:

src/physics/collision.o:
src/physics/physics.o:

src/render/render.o:
src/render/queue.o:

src/game/world.o: src/game/game_util.h src/render/ColoredMesh.h

.PHONY: clean
clean:
	rm $(objects)
