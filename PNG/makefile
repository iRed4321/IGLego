SRC:= $(wildcard ./*.cpp)
OBJ:= $(patsubst ./%.cpp, ./%.o, $(SRC))

ADD_LIB:= $(patsubst ./Png/%.c, ./Png/%.o ,$(wildcard ./Png/*.c))

CC:= g++

CC_FLAGS:= -Wall -g

CC_LIBS:= -lglut -lGL -lGLU -lm

all: $(ADD_LIB) $(OBJ)

$(OBJ): $(SRC)
	$(CC) $(CC_FLAGS) -c $(SRC) $(CC_LIBS) $(ADD_LIB)

$(ADD_LIB):
	$(MAKE) -C Png

clean:
	rm -rf $(OBJ)
	$(MAKE) -C Png clean