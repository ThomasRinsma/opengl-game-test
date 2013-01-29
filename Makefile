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
ENTITY_FILES=$(wildcard src/entity/*.cc) src/entity/entity.ih src/entity/entity.h
OBJECT_FILES=$(wildcard src/object/*.cc) src/object/object.ih src/object/object.h
SCREENELEMENT_FILES=$(wildcard src/screenelement/*.cc) src/screenelement/screenelement.ih src/screenelement/screenelement.h

CUBE_FILES=$(wildcard src/object/cube/*.cc) src/object/cube/cube.ih src/object/cube/cube.h
GRID_FILES=$(wildcard src/object/grid/*.cc) src/object/grid/grid.ih src/object/grid/grid.h
MODEL_FILES=$(wildcard src/object/model/*.cc) src/object/model/model.ih src/object/model/model.h
TEXT_FILES=$(wildcard src/object/text/*.cc) src/object/text/text.ih src/object/text/text.h

TEXT2D_FILES=$(wildcard src/screenelement/text2d/*.cc) src/screenelement/text2d/text2d.ih src/screenelement/text2d/text2d.h

GAME_DEPS=$(CONTROLLER_FILES) $(PLAYER_FILES) $(OBJECT_FILES) $(CUBE_FILES) $(GRID_FILES) $(MODEL_FILES) $(TEXT_FILES)
PLAYER_DEPS=$(CONTROLLER_FILES) $(ENTITY_FILES)
SHADERPROGRAM_DEPS=
CONTROLLER_DEPS=
DRAWABLE_DEPS=$(SHADERPROGRAM_FILES)
ENTITY_DEPS=
OBJECT_DEPS=$(SHADERPROGRAM_FILES) $(DRAWABLE_FILES) $(ENTITY_FILES)
SCREENELEMENT_DEPS=$(SHADERPROGRAM_FILES) $(DRAWABLE_FILES)
CUBE_DEPS=$(SHADERPROGRAM_FILES) $(OBJECT_FILES)
GRID_DEPS=$(SHADERPROGRAM_FILES) $(OBJECT_FILES)
MODEL_DEPS=$(SHADERPROGRAM_FILES) $(OBJECT_FILES)
TEXT_DEPS=$(SHADERPROGRAM_FILES) $(OBJECT_FILES)
TEXT2D_DEPS=$(SHADERPROGRAM_FILES) $(SCREENELEMENT_FILES)


all: prep_out_dirs make_objs

make_objs: $(OBJ_FILES)
	$(CXX) $^ -o openglgame $(LDLIBS)

prep_out_dirs:
	mkdir -p build/game build/player build/shaderprogram build/controller build/drawable build/entity build/object
	mkdir -p build/screenelement/text2d
	mkdir -p build/object/cube build/object/grid build/object/model build/object/text

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

build/entity/%.o: src/entity/%.cc src/entity/entity.ih src/entity/entity.h $(ENTITY_DEPS)
	$(CXX) -c $(CPPFLAGS) $< -o $@

build/object/%.o: src/object/%.cc src/object/object.ih src/object/object.h $(OBJECT_DEPS)
	$(CXX) -c $(CPPFLAGS) $< -o $@

build/screenelement/%.o: src/screenelement/%.cc src/screenelement/screenelement.ih src/screenelement/screenelement.h $(SCREENELEMENT_DEPS)
	$(CXX) -c $(CPPFLAGS) $< -o $@

build/screenelement/text2d/%.o: src/screenelement/text2d/%.cc src/screenelement/text2d/text2d.ih src/screenelement/text2d/text2d.h $(TEXT2D_DEPS)
	$(CXX) -c $(CPPFLAGS) $< -o $@

build/object/cube/%.o: src/object/cube/%.cc src/object/cube/cube.ih src/object/cube/cube.h $(CUBE_DEPS)
	$(CXX) -c $(CPPFLAGS) $< -o $@

build/object/grid/%.o: src/object/grid/%.cc src/object/grid/grid.ih src/object/grid/grid.h $(GRID_DEPS)
	$(CXX) -c $(CPPFLAGS) $< -o $@

build/object/model/%.o: src/object/model/%.cc src/object/model/model.ih src/object/model/model.h $(MODEL_DEPS)
	$(CXX) -c $(CPPFLAGS) $< -o $@

build/object/text/%.o: src/object/text/%.cc src/object/text/text.ih src/object/text/text.h $(TEXT_DEPS)
	$(CXX) -c $(CPPFLAGS) $< -o $@


clean:
	rm build/*.o build/*/*.o build/*/*/*.o
	rm -r build


