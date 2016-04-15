CC  := g++
SRC := $(shell find src/ -name *.cpp)
OBJ := $(SRC:src/%.cpp=bin/%.o)

CFLAGS := -Wall -std=c++14
LFLAGS := -lGL -lGLEW -lglfw

OUT := IceEngine

all: $(OBJ)
	$(CC) $^ $(LFLAGS) -o $(OUT)

bin/%.o: src/%.cpp
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $^ -o $@

clean:
	rm -rf bin/ $(OUT)