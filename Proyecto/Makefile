#OBJS specifies which files to compile as part of the project
OBJS = main.cpp App.cpp GameStateMachine.cpp GameObjectTest.cpp GameState.cpp RenderableObject.cpp PhysicsObject.cpp MainMenu.cpp GameScene.cpp MenuButton.cpp Fighter.cpp AnimationMachine.cpp HitDetectionBox.cpp Socket.cc NetMessage.cpp CreateButton.cpp JoinButton.cpp
SOBJ = ServerMain.cpp Socket.cc NetMessage.cpp Server.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
CFLAGS = -g -std=c++11

#LINKER_FLAGS specifies the libraries we're linking against
LIBS = libbox2d.a
LINKER_FLAGS = -lSDL2 -lSDL2_image -lpthread

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = main
SER_NAME = server

#This is the target that compiles our executable
all : c s
	
c: $(OBJS)
	$(CC) $(OBJS) $(CFLAGS)  $(LINKER_FLAGS) -o $(OBJ_NAME) $(LIBS)
s: $(OBJS)
	$(CC) $(SOBJ) $(CFLAGS)  $(LINKER_FLAGS) -o $(SER_NAME)
