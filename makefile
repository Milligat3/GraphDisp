COMPILER_PATH := D:/ProgrStuff/raylib/w64devkit/bin
CC := $(COMPILER_PATH)/gcc.exe
TARGET := GraphDisp.exe
SRC_DIR := src
SRCS := VecDisp.c DrawFuncs.c  MouseEvents.c  VertMove.c  vectors.c ThingsWithGraph.c  
SOURCES := 
OBJ_DIR := obj
OBJS := $(OBJ_DIR)/$(SRCS:.c=.o)
INCFLAGS := -Iinclude -ID:/ProgrStuff/raylib/raylib/src 
LDFLAGS := -LD:/ProgrStuff/raylib/raylib/src -lraylib -lopengl32 -lgdi32 -lwinmm -mconsole

all: $(TARGET)

$(TARGET): obj/VecDisp.o obj/VertMove.o obj/ThingsWithGraph.o obj/MouseEvents.o obj/DrawFuncs.o obj/vectors.o
	$(CC) -g $^ -o $@ $(LDFLAGS)

obj/VecDisp.o: src/VecDisp.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -std=c99 $(INCFLAGS) -c $< -o $@

obj/VertMove.o: src/VertMove.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -std=c99 $(INCFLAGS) -c $< -o $@

obj/ThingsWithGraph.o: src/ThingsWithGraph.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -std=c99 $(INCFLAGS) -c $< -o $@

obj/MouseEvents.o: src/MouseEvents.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -std=c99 $(INCFLAGS) -c $< -o $@

obj/DrawFuncs.o: src/DrawFuncs.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -std=c99 $(INCFLAGS) -c $< -o $@

obj/vectors.o: src/vectors.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -std=c99 $(INCFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
	
love:
	@echo "Hey! Don't you fucking dare give up! You're the only soul that can help this world in this room!"
