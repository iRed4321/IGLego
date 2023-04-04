#Compiling igLego

# For Linux
REQUIRED_LIBS := -lGL -lGLU -lglut -lm -lstdc++
SRC_DIR := src
COMPILER := gcc
INC_DIR := include
INC_FLAGS := -I $(INC_DIR)

all: igLego

igLego : $(SRC_DIR)/*.cpp
	$(COMPILER) $^ $(REQUIRED_LIBS) $(INC_FLAGS) -o build/runnable

run: build/runnable
	./build/runnable

clean:
	rm build/*
