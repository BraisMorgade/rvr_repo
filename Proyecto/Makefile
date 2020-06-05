#OBJS specifies which files to compile as part of the project
OBJS = main.cpp App.cpp GameStateMachine.cpp GameStateTest.cpp GameObjectTest.cpp GameState.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
CFLAGS = -g -std=c++11

#LINKER_FLAGS specifies the libraries we're linking against
LIBS = libbox2d.a
LINKER_FLAGS = -lSDL2 -lSDL2_image

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = main

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(CFLAGS)  $(LINKER_FLAGS) -o $(OBJ_NAME) $(LIBS)
