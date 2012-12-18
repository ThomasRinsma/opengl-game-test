CC=g++
CFLAGS=-Wall --std=c++0x -DGLEW_STATIC
LFLAGS=-lGLEW -lGLU -lsfml-graphics -lsfml-window -lsfml-system
EXEC=openglgame

all:
	$(CC) main.cc */*.cc -o $(EXEC) $(CFLAGS) $(LFLAGS)
