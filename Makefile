CXX=g++
CPPFLAGS=-g -Wall --std=c++11 -DGLEW_STATIC
LDLIBS=-lGLEW -lGLU -lsfml-graphics -lsfml-window -lsfml-system

SRC_FILES=$(wildcard src/*/*.cc) $(wildcard src/*/*/*.cc)
OBJ_FILES=$(subst .cc,.o,$(subst src,build,$(SRC_FILES))) build/main.o


GAME_FILES=$(wildcard src/game/*.cc) src/game/game.ih src/game/game.h
PLAYER_FILES=$(wildcard src/player/*.cc) src/player/player.ih src/player/player.h
SHADERPROGRAM_FILES=$(wildcard src/shaderprogram/*.cc) src/shaderprogram/shaderprogram.ih src/shaderprogram/shaderprogram.h
CONTROLLER_FILES=$(wildcard src/controller/*.cc) src/controller/controller.ih src/controller/controller.h
DRAWABLE_FILES=$(wildcard src/drawable/*.cc) src/drawable/drawable.ih src/drawable/drawable.h
CUBE_FILES=$(wildcard src/drawable/cube/*.cc) src/drawable/cube/cube.ih src/drawable/cube/cube.h
GRID_FILES=$(wildcard src/drawable/grid/*.cc) src/drawable/grid/grid.ih src/drawable/grid/grid.h
MODEL_FILES=$(wildcard src/drawable/model/*.cc) src/drawable/model/model.ih src/drawable/model/model.h


GAME_DEPS=$(CONTROLLER_FILES) $(PLAYER_FILES) $(DRAWABLE_FILES) $(CUBE_FILES) $(GRID_FILES) $(MODEL_FILES)
PLAYER_DEPS=$(CONTROLLER_FILES)
SHADERPROGRAM_DEPS=
CONTROLLER_DEPS=
DRAWABLE_DEPS=$(SHADERPROGRAM_FILES)
CUBE_DEPS=$(SHADERPROGRAM_FILES) $(DRAWABLE_FILES)
GRID_DEPS=$(SHADERPROGRAM_FILES) $(DRAWABLE_FILES)
MODEL_DEPS=$(SHADERPROGRAM_FILES) $(DRAWABLE_FILES)


all: prep_out_dirs make_objs

make_objs: $(OBJ_FILES)
	$(CXX) $^ -o openglgame $(LDLIBS)

prep_out_dirs:
	mkdir -p build/game build/player build/shaderprogram build/controller
	mkdir -p build/drawable/cube build/drawable/grid build/drawable/model

build/main.o: src/main.cc
	$(CXX) -c $(CPPFLAGS) $< -o $@

build/game/%.o: src/game/%.cc src/game/game.ih src/game/game.h $(GAME_DEPS)
	$(CXX) -c $(CPPFLAGS) $< -o $@

build/player/%.o: src/player/%.cc src/player/player.ih src/player/player.h $(PLAYER_DEPS)
	$(CXX) -c $(CPPFLAGS) $< -o $@

build/shaderprogram/%.o: src/shaderprogram/%.cc src/shaderprogram/shaderprogram.ih src/shaderprogram/shaderprogram.h $(SHADERPROGRAM_DEPS)
	$(CXX) -c $(CPPFLAGS) $< -o $@

build/controller/%.o: src/controller/%.cc src/controller/controller.ih src/controller/controller.h $(CONTROLLER_DEPS)
	$(CXX) -c $(CPPFLAGS) $< -o $@

build/drawable/%.o: src/drawable/%.cc src/drawable/drawable.ih src/drawable/drawable.h $(DRAWABLE_DEPS)
	$(CXX) -c $(CPPFLAGS) $< -o $@

build/drawable/cube/%.o: src/drawable/cube/%.cc src/drawable/cube/cube.ih src/drawable/cube/cube.h $(CUBE_DEPS)
	$(CXX) -c $(CPPFLAGS) $< -o $@

build/drawable/grid/%.o: src/drawable/grid/%.cc src/drawable/grid/grid.ih src/drawable/grid/grid.h $(GRID_DEPS)
	$(CXX) -c $(CPPFLAGS) $< -o $@

build/drawable/model/%.o: src/drawable/model/%.cc src/drawable/model/model.ih src/drawable/model/model.h $(MODEL_DEPS)
	$(CXX) -c $(CPPFLAGS) $< -o $@


clean:
	rm build/*.o build/*/*.o build/*/*/*.o
	rm -r build


