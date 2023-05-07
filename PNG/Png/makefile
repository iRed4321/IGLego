
SRC:= $(wildcard ./*.c)

OBJ:= $(patsubst ./%.c, ./%.o, $(SRC))

CC:= gcc

CC_FLAGS:= -Wall -g

CC_LIBS:= -lglut -lGL -lGLU -lm

all: $(OBJ)

%.o: %.c
	$(CC) $(CC_FLAGS) -c $< -o $@ $(CC_LIBS)

clean:
	rm -rf $(OBJ)