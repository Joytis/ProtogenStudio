CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wall -Wextra -pedantic -O2

SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDLIBS := $(shell sdl2-config --libs)

TARGET = main
SRC = main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
    $(CXX) $(CXXFLAGS) $(SDL_CFLAGS) -o $(TARGET) $(SRC) $(SDL_LDLIBS)

clean:
    del /Q $(TARGET).exe 2>NUL || rm -f $(TARGET)