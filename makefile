#Compiling igLego

# For Linux
REQUIRED_LIBS := -lGL -lGLU -lglut -lm -lstdc++ -std=c++17
SRC_DIR := src
COMPILER := g++
INC_DIR := include
INC_FLAGS := -I $(INC_DIR)

OBJS_FILES := build/objetsGeom.o build/bricks.o build/Tests.o

all: project

build/objetsGeom.o : $(SRC_DIR)/ObjetsGeometriques.cpp $(INC_DIR)/ObjetsGeometriques.h 
	$(COMPILER) $< -c -o $@ $(INC_FLAGS)

build/bricks.o : $(SRC_DIR)/LegoBricks.cpp $(INC_DIR)/LegoBricks.h $(INC_DIR)/ObjetsGeometriques.h
	$(COMPILER) $< -c -o $@ $(INC_FLAGS)

build/Tests.o : $(SRC_DIR)/Tests.cpp $(INC_DIR)/LegoBricks.h
	$(COMPILER) $< -c -o $@ $(INC_FLAGS)

project : $(OBJS_FILES)
	$(COMPILER) $^ -o build/runnable $(REQUIRED_LIBS) $(INC_FLAGS) 

run : project
	build/runnable

clean:
	rm build/*
