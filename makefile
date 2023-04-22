#Compiling igLego

# For Linux
REQUIRED_LIBS := -lGL -lGLU -lglut -lm -lstdc++
SRC_DIR := src
COMPILER := g++
INC_DIR := include
INC_FLAGS := -I $(INC_DIR)
OTHER_FLAGS := -std=c++17 -Wall -O2

OBJS_FILES := build/objetsGeom.o build/Legobricks.o build/Tests.o build/coords.o build/legoBrick.o

all: project

build/legoBrick.o : $(SRC_DIR)/LegoBrick.cpp $(INC_DIR)/LegoBrick.h $(INC_DIR)/LegoBricks.h
	$(COMPILER) $< -c -o $@ $(INC_FLAGS) $(OTHER_FLAGS)

build/coords.o : $(SRC_DIR)/coords.cpp $(INC_DIR)/coords.h 
	$(COMPILER) $< -c -o $@ $(INC_FLAGS) $(OTHER_FLAGS)

build/objetsGeom.o : $(SRC_DIR)/ObjetsGeometriques.cpp $(INC_DIR)/ObjetsGeometriques.h 
	$(COMPILER) $< -c -o $@ $(INC_FLAGS) $(OTHER_FLAGS)

build/Legobricks.o : $(SRC_DIR)/LegoBricks.cpp $(INC_DIR)/LegoBricks.h $(INC_DIR)/ObjetsGeometriques.h
	$(COMPILER) $< -c -o $@ $(INC_FLAGS) $(OTHER_FLAGS)

build/Tests.o : $(SRC_DIR)/Tests.cpp $(INC_DIR)/LegoBricks.h
	$(COMPILER) $< -c -o $@ $(INC_FLAGS) $(OTHER_FLAGS)

project : $(OBJS_FILES)
	$(COMPILER) $^ -o build/runnable $(REQUIRED_LIBS) $(INC_FLAGS) $(OTHER_FLAGS)

run :
	build/runnable

check-run :
	valgrind build/runnable

clean:
	rm build/*
