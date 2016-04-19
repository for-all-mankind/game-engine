CC  := g++
SRC := $(shell find src/ -name *.cpp)
OBJ := $(SRC:src/%.cpp=bin/%.o)

CFLAGS := -Wall -std=c++14 -I./include/
LFLAGS := -lGL -lGLEW -lm -lglfw

OUT := IceEngine

all: $(OBJ)
	$(CC) $^ $(LFLAGS) -o $(OUT)

bin/%.o: src/%.cpp
	mkdir -p $(dir $@)
	$(CC) -c -g $(CFLAGS) $^ -o $@

clean:
	rm -rf bin/ $(OUT)