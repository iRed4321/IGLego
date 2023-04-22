#Compiling igLego

# For Linux
REQUIRED_LIBS := -lGL -lGLU -lglut -lm -lstdc++
COMPILER := g++
OTHER_FLAGS := -std=c++17 -Wall -O2



all : *.cpp
	$(COMPILER) $^ -o ../build/runnable $(REQUIRED_LIBS) $(OTHER_FLAGS)

run : all
	../build/runnable

clean:
	rm build/*
