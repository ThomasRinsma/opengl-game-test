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
SCENEOBJECT_FILES=$(wildcard src/sceneobject/*.cc) src/sceneobject/sceneobject.ih src/sceneobject/sceneobject.h
SCENE_FILES=$(wildcard src/scene/*.cc) src/scene/scene.ih src/scene/scene.h
GUI_FILES=$(wildcard src/gui/*.cc) src/gui/gui.ih src/gui/gui.h
TEXTURE_FILES=$(wildcard src/texture/*.cc) src/texture/texture.ih src/texture/texture.h
MODEL_FILES=$(wildcard src/model/*.cc) src/model/model.ih src/model/model.h
RESOURCEMANAGER_FILES=$(wildcard src/resourcemanager/*.cc) src/resourcemanager/resourcemanager.ih src/resourcemanager/resourcemanager.h
LIGHT_FILES=$(wildcard src/light/*.cc) src/light/light.ih src/light/light.h
SCREENELEMENT_FILES=$(wildcard src/screenelement/*.cc) src/screenelement/screenelement.ih src/screenelement/screenelement.h

CUBE_FILES=$(wildcard src/sceneobject/cube/*.cc) src/sceneobject/cube/cube.ih src/sceneobject/cube/cube.h
GRID_FILES=$(wildcard src/sceneobject/grid/*.cc) src/sceneobject/grid/grid.ih src/sceneobject/grid/grid.h
GENERICMODEL_FILES=$(wildcard src/sceneobject/genericmodel/*.cc) src/sceneobject/genericmodel/genericmodel.ih src/sceneobject/genericmodel/genericmodel.h
TEXT_FILES=$(wildcard src/drawable/text/*.cc) src/drawable/text/text.ih src/drawable/text/text.h
PORTAL_FILES=$(wildcard src/sceneobject/portal/*.cc) src/sceneobject/portal/portal.ih src/sceneobject/portal/portal.h

DEBUGTEXT_FILES=$(wildcard src/screenelement/debugtext/*.cc) src/screenelement/debugtext/debugtext.ih src/screenelement/debugtext/debugtext.h
CONSOLE_FILES=$(wildcard src/screenelement/console/*.cc) src/screenelement/console/console.ih src/screenelement/console/console.h


GAME_DEPS=$(CONTROLLER_FILES) $(PLAYER_FILES) $(CUBE_FILES) $(GRID_FILES) $(GENERICMODEL_FILES) $(PORTAL_FILES) $(DEBUGTEXT_FILES) $(CONSOLE_FILES) $(SCENE_FILES) $(GUI_FILES) $(RESOURCEMANAGER_FILES) $(LIGHT_FILES)
PLAYER_DEPS=$(CONTROLLER_FILES) $(ENTITY_FILES)
SHADERPROGRAM_DEPS=
CONTROLLER_DEPS=$(GAME_FILES)
DRAWABLE_DEPS=$(SHADERPROGRAM_FILES)
ENTITY_DEPS=
SCENEOBJECT_DEPS=$(SHADERPROGRAM_FILES) $(DRAWABLE_FILES) $(ENTITY_FILES)
SCENE_DEPS=$(PLAYER_FILES) $(SCENEOBJECT_FILES) $(PORTAL_FILES) $(LIGHT_FILES) $(RESOURCEMANAGER_FILES)
GUI_DEPS=$(SCENEOBJECT_FILES)
TEXTURE_DEPS=
MODEL_DEPS=$(SHADERPROGRAM_FILES)
RESOURCEMANAGER_DEPS=$(MODEL_FILES) $(TEXTURE_FILES) $(SHADERPROGRAM_FILES)
LIGHT_DEPS=$(ENTITY_FILES)
SCREENELEMENT_DEPS=$(DRAWABLE_FILES) $(ENTITY_FILES) $(SHADERPROGRAM_FILES)

CUBE_DEPS=$(SHADERPROGRAM_FILES) $(SCENEOBJECT_FILES) $(TEXTURE_FILES) $(RESOURCEMANAGER_FILES)
GRID_DEPS=$(SHADERPROGRAM_FILES) $(SCENEOBJECT_FILES) $(RESOURCEMANAGER_FILES)
GENERICMODEL_DEPS=$(SHADERPROGRAM_FILES) $(SCENEOBJECT_FILES) $(MODEL_FILES) $(TEXTURE_FILES) $(RESOURCEMANAGER_FILES)
TEXT_DEPS=$(SHADERPROGRAM_FILES) $(SCENEOBJECT_FILES) $(TEXTURE_FILES) $(RESOURCEMANAGER_FILES)
PORTAL_DEPS=$(SHADERPROGRAM_FILES) $(SCENEOBJECT_FILES) $(ENTITY_FILES) $(RESOURCEMANAGER_FILES)

DEBUGTEXT_DEPS=$(SCREENELEMENT_FILES) $(TEXT_FILES)
CONSOLE_DEPS=$(SCREENELEMENT_FILES) $(TEXT_FILES) $(CONTROLLER_FILES) $(RESOURCEMANAGER_FILES)

all: prep_out_dirs make_objs

make_objs: $(OBJ_FILES)
	$(CXX) $^ -o openglgame $(LDLIBS)

prep_out_dirs:
	mkdir -p build/game build/player build/shaderprogram build/controller build/drawable build/entity build/light
	mkdir -p build/texture build/model build/sceneobject build/scene build/gui build/resourcemanager
	mkdir -p build/sceneobject/cube build/sceneobject/grid build/sceneobject/genericmodel
	mkdir -p build/sceneobject/text build/sceneobject/portal
	mkdir -p build/drawable/text build/screenelement/debugtext build/screenelement/console

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

build/sceneobject/%.o: src/sceneobject/%.cc src/sceneobject/sceneobject.ih src/sceneobject/sceneobject.h $(SCENEOBJECT_DEPS)
	$(CXX) -c $(CPPFLAGS) $< -o $@

build/screenelement/%.o: src/screenelement/%.cc src/screenelement/screenelement.ih src/screenelement/screenelement.h $(SCREENELEMENT_DEPS)
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

build/drawable/text/%.o: src/drawable/text/%.cc src/drawable/text/text.ih src/drawable/text/text.h $(TEXT_DEPS)
	$(CXX) -c $(CPPFLAGS) $< -o $@

build/sceneobject/cube/%.o: src/sceneobject/cube/%.cc src/sceneobject/cube/cube.ih src/sceneobject/cube/cube.h $(CUBE_DEPS)
	$(CXX) -c $(CPPFLAGS) $< -o $@

build/sceneobject/grid/%.o: src/sceneobject/grid/%.cc src/sceneobject/grid/grid.ih src/sceneobject/grid/grid.h $(GRID_DEPS)
	$(CXX) -c $(CPPFLAGS) $< -o $@

build/sceneobject/genericmodel/%.o: src/sceneobject/genericmodel/%.cc src/sceneobject/genericmodel/genericmodel.ih src/sceneobject/genericmodel/genericmodel.h $(GENERICMODEL_DEPS)
	$(CXX) -c $(CPPFLAGS) $< -o $@

build/sceneobject/portal/%.o: src/sceneobject/portal/%.cc src/sceneobject/portal/portal.ih src/sceneobject/portal/portal.h $(PORTAL_DEPS)
	$(CXX) -c $(CPPFLAGS) $< -o $@

build/screenelement/debugtext/%.o: src/screenelement/debugtext/%.cc src/screenelement/debugtext/debugtext.ih src/screenelement/debugtext/debugtext.h $(DEBUGTEXT_DEPS)
	$(CXX) -c $(CPPFLAGS) $< -o $@

build/screenelement/console/%.o: src/screenelement/console/%.cc src/screenelement/console/console.ih src/screenelement/console/console.h $(CONSOLE_DEPS)
	$(CXX) -c $(CPPFLAGS) $< -o $@


clean:
	rm build/*.o build/*/*.o build/*/*/*.o
	rm -r build


