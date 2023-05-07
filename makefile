#Compiling igLego

# For Linux
REQUIRED_LIBS := -lGL -lGLU -lglut -lm -lstdc++
SRC_DIR := src
COMPILER := g++
INC_DIR := include
INC_FLAGS := -I $(INC_DIR)
OTHER_FLAGS := -std=c++17 -Wall -O2 

TMP:=$(wildcard PNG/*.cpp)
TMP2:=$(wildcard PNG/Png/*.c)
ADD_LIB:=$(patsubst %.cpp, %.o, $(TMP)) $(patsubst %.c, %.o, $(TMP2))


OBJS_FILES := build/objetsgeometriques.o build/legobricks.o build/tests.o build/coords.o build/construction.o build/legobrick.o 

all: project

build/construction.o : $(SRC_DIR)/construction.cpp $(INC_DIR)/construction.h
	$(COMPILER) $< -c -o $@ $(INC_FLAGS) $(OTHER_FLAGS)

build/legobrick.o : $(SRC_DIR)/LegoBrick.cpp $(INC_DIR)/LegoBrick.h $(INC_DIR)/LegoBricks.h
	$(COMPILER) $< -c -o $@ $(INC_FLAGS) $(OTHER_FLAGS)

build/coords.o : $(SRC_DIR)/coords.cpp $(INC_DIR)/coords.h 
	$(COMPILER) $< -c -o $@ $(INC_FLAGS) $(OTHER_FLAGS)

build/objetsgeometriques.o : $(SRC_DIR)/ObjetsGeometriques.cpp $(INC_DIR)/ObjetsGeometriques.h 
	$(COMPILER) $< -c -o $@ $(INC_FLAGS) $(OTHER_FLAGS)

build/legobricks.o : $(SRC_DIR)/LegoBricks.cpp $(INC_DIR)/LegoBricks.h $(INC_DIR)/ObjetsGeometriques.h
	$(COMPILER) $< -c -o $@ $(INC_FLAGS) $(OTHER_FLAGS)

build/tests.o : $(SRC_DIR)/Tests.cpp $(INC_DIR)/*.h 
	$(COMPILER) $< -c -o $@ -g -I PNG -I /PNG/Png -Wno-deprecated $(INC_FLAGS) $(OTHER_FLAGS) $(ADD_LIB)

$(ADD_LIB):
	$(MAKE) -C PNG

project : $(ADD_LIB) $(OBJS_FILES) 
	$(COMPILER) $^ -o build/runnable $(REQUIRED_LIBS) $(INC_FLAGS) $(OTHER_FLAGS) 

run :
	build/runnable

check-run :
	valgrind build/runnable

test-other : build/legobrick.o build/coords.o build/legobricks.o build/objetsgeometriques.o
	$(COMPILER) $^ -o build/runnable $(REQUIRED_LIBS) $(INC_FLAGS) $(OTHER_FLAGS)
	build/runnable

clean:
	rm build/*
	$(MAKE) -C PNG clean
