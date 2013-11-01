CXX=g++
CPPFLAGS=-g -Wall --std=c++11 -DGLEW_STATIC
LDLIBS=-L/usr/local/lib/ -lGL -lGLEW -lGLU -lsfml-graphics -lsfml-window -lsfml-system

SRC_FILES=$(wildcard src/*.cc) $(wildcard src/*/*.cc)
OBJ_FILES=$(subst .cc,.o,$(subst src,build,$(SRC_FILES)))



all: prep_out_dirs make_objs

make_objs: $(OBJ_FILES)
	$(CXX) $^ -o openglgame $(LDLIBS)

prep_out_dirs:
	mkdir -p build/collidable build/drawable build/sceneobject build/screenelement

build/%.o: src/%.cc src/%.h
	$(CXX) -c $(CPPFLAGS) $< -o $@

build/main.o: src/main.cc
	$(CXX) -c $(CPPFLAGS) $< -o $@

build/collidable/%.o: src/collidable/%.cc src/collidable/%.h
	$(CXX) -c $(CPPFLAGS) $< -o $@

build/drawable/%.o: src/drawable/%.cc src/drawable/%.h
	$(CXX) -c $(CPPFLAGS) $< -o $@

build/sceneobject/%.o: src/sceneobject/%.cc src/sceneobject/%.h
	$(CXX) -c $(CPPFLAGS) $< -o $@

build/screenelement/%.o: src/screenelement/%.cc src/screenelement/%.h
	$(CXX) -c $(CPPFLAGS) $< -o $@

clean:
	rm build/*.o build/*/*.o build/*/*/*.o
	rm -r build


