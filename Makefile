CXX=g++
CPPFLAGS=-g -Wall --std=c++11 -DGLEW_STATIC
LDLIBS=-L/usr/local/lib/ -lGL -lGLEW -lGLU -lsfml-graphics -lsfml-window -lsfml-system

SRC_FILES=$(wildcard src/*/*.cc) $(wildcard src/*/*/*.cc)
OBJ_FILES=$(subst .cc,.o,$(subst src,build,$(SRC_FILES))) build/main.o


GAME_FILES=$(wildcard src/game/*.cc) src/game/game.ih src/game/game.h
PLAYER_FILES=$(wildcard src/player/*.cc) src/player/player.ih src/player/player.h
SHADERPROGRAM_FILES=$(wildcard src/shaderprogram/*.cc) src/shaderprogram/shaderprogram.ih src/shaderprogram/shaderprogram.h
CONTROLLER_FILES=$(wildcard src/controller/*.cc) src/controller/controller.ih src/controller/controller.h
DRAWABLE_FILES=$(wildcard src/drawable/*.cc) src/drawable/drawable.ih src/drawable/drawable.h
ENTITY_FILES=$(wildcard src/entity/*.cc) src/entity/entity.ih src/entity/entity.h
DRAWABLEENTITY_FILES=$(wildcard src/drawableentity/*.cc) src/drawableentity/drawableentity.ih src/drawableentity/drawableentity.h
SCENE_FILES=$(wildcard src/scene/*.cc) src/scene/scene.ih src/scene/scene.h
GUI_FILES=$(wildcard src/gui/*.cc) src/gui/gui.ih src/gui/gui.h
TEXTURE_FILES=$(wildcard src/texture/*.cc) src/texture/texture.ih src/texture/texture.h
MODEL_FILES=$(wildcard src/model/*.cc) src/model/model.ih src/model/model.h
RESOURCEMANAGER_FILES=$(wildcard src/resourcemanager/*.cc) src/resourcemanager/resourcemanager.ih src/resourcemanager/resourcemanager.h
LIGHT_FILES=$(wildcard src/light/*.cc) src/light/light.ih src/light/light.h

CUBE_FILES=$(wildcard src/drawableentity/cube/*.cc) src/drawableentity/cube/cube.ih src/drawableentity/cube/cube.h
GRID_FILES=$(wildcard src/drawableentity/grid/*.cc) src/drawableentity/grid/grid.ih src/drawableentity/grid/grid.h
GENERICMODEL_FILES=$(wildcard src/drawableentity/genericmodel/*.cc) src/drawableentity/genericmodel/genericmodel.ih src/drawableentity/genericmodel/genericmodel.h
TEXT_FILES=$(wildcard src/drawableentity/text/*.cc) src/drawableentity/text/text.ih src/drawableentity/text/text.h
PORTAL_FILES=$(wildcard src/drawableentity/portal/*.cc) src/drawableentity/portal/portal.ih src/drawableentity/portal/portal.h

GAME_DEPS=$(CONTROLLER_FILES) $(PLAYER_FILES) $(CUBE_FILES) $(GRID_FILES) $(GENERICMODEL_FILES) $(TEXT_FILES) $(SCENE_FILES) $(GUI_FILES) $(RESOURCEMANAGER_FILES) $(LIGHT_FILES)
PLAYER_DEPS=$(CONTROLLER_FILES) $(ENTITY_FILES)
SHADERPROGRAM_DEPS=
CONTROLLER_DEPS=
DRAWABLE_DEPS=$(SHADERPROGRAM_FILES)
ENTITY_DEPS=
DRAWABLEENTITY_DEPS=$(SHADERPROGRAM_FILES) $(DRAWABLE_FILES) $(ENTITY_FILES)
SCENE_DEPS=$(PLAYER_FILES) $(DRAWABLEENTITY_FILES) $(PORTAL_FILES) $(LIGHT_FILES) $(RESOURCEMANAGER_FILES)
GUI_DEPS=$(DRAWABLEENTITY_FILES)
TEXTURE_DEPS=
MODEL_DEPS=$(SHADERPROGRAM_FILES)
RESOURCEMANAGER_DEPS=$(MODEL_FILES) $(TEXTURE_FILES) $(SHADERPROGRAM_FILES)
LIGHT_DEPS=$(ENTITY_FILES)

CUBE_DEPS=$(SHADERPROGRAM_FILES) $(DRAWABLEENTITY_FILES) $(TEXTURE_FILES) $(RESOURCEMANAGER_FILES)
GRID_DEPS=$(SHADERPROGRAM_FILES) $(DRAWABLEENTITY_FILES) $(RESOURCEMANAGER_FILES)
GENERICMODEL_DEPS=$(SHADERPROGRAM_FILES) $(DRAWABLEENTITY_FILES) $(MODEL_FILES) $(TEXTURE_FILES) $(RESOURCEMANAGER_FILES)
TEXT_DEPS=$(SHADERPROGRAM_FILES) $(DRAWABLEENTITY_FILES) $(TEXTURE_FILES) $(RESOURCEMANAGER_FILES)
PORTAL_DEPS=$(SHADERPROGRAM_FILES) $(DRAWABLEENTITY_FILES) $(ENTITY_FILES) $(RESOURCEMANAGER_FILES)


all: prep_out_dirs make_objs

make_objs: $(OBJ_FILES)
	$(CXX) $^ -o openglgame $(LDLIBS)

prep_out_dirs:
	mkdir -p build/game build/player build/shaderprogram build/controller build/drawable build/entity build/light
	mkdir -p build/texture build/model build/drawableentity build/scene build/gui build/resourcemanager
	mkdir -p build/drawableentity/cube build/drawableentity/grid build/drawableentity/genericmodel
	mkdir -p build/drawableentity/text build/drawableentity/portal

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

build/drawableentity/%.o: src/drawableentity/%.cc src/drawableentity/drawableentity.ih src/drawableentity/drawableentity.h $(DRAWABLEENTITY_DEPS)
	$(CXX) -c $(CPPFLAGS) $< -o $@

build/scene/%.o: src/scene/%.cc src/scene/scene.ih src/scene/scene.h $(SCENE_DEPS)
	$(CXX) -c $(CPPFLAGS) $< -o $@

build/gui/%.o: src/gui/%.cc src/gui/gui.ih src/gui/gui.h $(GUI_DEPS)
	$(CXX) -c $(CPPFLAGS) $< -o $@

build/texture/%.o: src/texture/%.cc src/texture/texture.ih src/texture/texture.h $(TEXTURE_DEPS)
	$(CXX) -c $(CPPFLAGS) $< -o $@

build/model/%.o: src/model/%.cc src/model/model.ih src/model/model.h $(MODEL_DEPS)
	$(CXX) -c $(CPPFLAGS) $< -o $@

build/light/%.o: src/light/%.cc src/light/light.ih src/light/light.h $(LIGHT_DEPS)
	$(CXX) -c $(CPPFLAGS) $< -o $@

build/resourcemanager/%.o: src/resourcemanager/%.cc src/resourcemanager/resourcemanager.ih src/resourcemanager/resourcemanager.h $(RESOURCEMANAGER_DEPS)
	$(CXX) -c $(CPPFLAGS) $< -o $@

build/drawableentity/cube/%.o: src/drawableentity/cube/%.cc src/drawableentity/cube/cube.ih src/drawableentity/cube/cube.h $(CUBE_DEPS)
	$(CXX) -c $(CPPFLAGS) $< -o $@

build/drawableentity/grid/%.o: src/drawableentity/grid/%.cc src/drawableentity/grid/grid.ih src/drawableentity/grid/grid.h $(GRID_DEPS)
	$(CXX) -c $(CPPFLAGS) $< -o $@

build/drawableentity/genericmodel/%.o: src/drawableentity/genericmodel/%.cc src/drawableentity/genericmodel/genericmodel.ih src/drawableentity/genericmodel/genericmodel.h $(GENERICMODEL_DEPS)
	$(CXX) -c $(CPPFLAGS) $< -o $@

build/drawableentity/text/%.o: src/drawableentity/text/%.cc src/drawableentity/text/text.ih src/drawableentity/text/text.h $(TEXT_DEPS)
	$(CXX) -c $(CPPFLAGS) $< -o $@

build/drawableentity/portal/%.o: src/drawableentity/portal/%.cc src/drawableentity/portal/portal.ih src/drawableentity/portal/portal.h $(PORTAL_DEPS)
	$(CXX) -c $(CPPFLAGS) $< -o $@


clean:
	rm build/*.o build/*/*.o build/*/*/*.o
	rm -r build


