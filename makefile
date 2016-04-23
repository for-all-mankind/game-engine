CC  := clang++
SRC := $(shell find src/ -name *.cpp)
OBJ := $(SRC:src/%.cpp=obj/%.o)

CFLAGS := -Wall -std=c++14 -I./include/
LFLAGS := -lGL -lGLEW -lglfw

OUT := IceEngine

all: $(OBJ)
	$(CC) $^ $(LFLAGS) -o $(OUT)

obj/%.o: src/%.cpp
	mkdir -p $(dir $@)
	$(CC) -c -g $(CFLAGS) $^ -o $@

clean:
	rm -rf obj/ $(OUT)