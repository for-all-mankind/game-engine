CC  := g++
SRC := $(shell find src/ -name *.cpp)

CFLAGS := -Wall -std=c++14
LFLAGS := -lGL -lGLEW -lSDL2

OUT := IceEngine

all:
	$(CC) $(CFLAGS) $(SRC) $(LFLAGS) -o $(OUT)

clean:
	rm -rf $(OUT)