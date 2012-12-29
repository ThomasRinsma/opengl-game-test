CC=g++
CFLAGS=-g -Wall --std=c++11 -DGLEW_STATIC
LFLAGS=-lGLEW -lGLU -lsfml-graphics -lsfml-window -lsfml-system
EXEC=openglgame

all:
	$(CC) main.cc */*.cc */*/*.cc -o $(EXEC) $(CFLAGS) $(LFLAGS)
