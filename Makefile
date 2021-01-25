SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

EXE := game.bin
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CC := g++
CPPFLAGS := -Iinclude/
CFLAGS   := -Wall -Werror -g
LDFLAGS  :=
LDLIBS   := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rv $(OBJ_DIR)
	rm $(EXE)
