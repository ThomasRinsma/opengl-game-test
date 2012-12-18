CC=g++
CFLAGS=-Wall --std=c++0x -DGLEW_STATIC -I/usr/include/nvidia-experimental-310/
LFLAGS=-lGLEW -lGLU -lsfml-graphics -lsfml-window -lsfml-system
EXEC=openglgame

all:
	$(CC) main.cc game/*.cc -o $(EXEC) $(CFLAGS) $(LFLAGS)
