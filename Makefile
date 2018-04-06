#Variable declarations
COMPILER=g++
CFLAGS=-c -std=c++11 -Iheaders -Ishaders
SOURCES=main.cpp glad.c WindowUtilities.cpp Shader.cpp ImageLoader.cpp Image.cpp
#Camera.cpp GameObject.cpp GameComponent.cpp

# $(SOURCES:.cpp=.o) is a Substitution Reference
INTERMEDIATE=$(SOURCES:.cpp=.o)
OBJECTS=$(INTERMEDIATE:.c=.o)
EXECUTABLE=Engine-63500

#Check OS
ifeq ($(OS), Windows_NT)
	os_name=Windows
else
	os_name=$(shell uname -s)
endif

#Assign appropiate linker flags to the OS
ifeq ($(os_name), Windows)
	LFLAGS=-mconsole -mwindows -Llibs/x86 -lopengl32 -lgdi32 -lglfw3
	EXECUTABLE:=$(EXECUTABLE).exe
else ifeq ($(os_name), Linux)
	LFLAGS=-Llibs/linux -lGLEW -lGL -lglfw3 -lX11 -lXxf86vm -lpthread -ldl -lXrandr -lXinerama -lXcursor
else ifeq ($(os_name), Darwin)
	LFLAGS=-Llibs/mac -lopengl32 -lgdi32 -lglfw3
	EXECUTABLE:=$(EXECUTABLE).app
endif

#Overriding Make's automatic compilation step (.cpp.o says to get .o you must do this first) 
#We do this because we want it to include our compiler flags (otherwise it runs g++ main.cpp without the flags)
#The symbol $< just says: given the target (e.g. Game.o), get the req (e.g. Game.cpp)
#So in this case, as it goes over all object files, it'll compile all the .cpp files
#The symbol $< is one of a bunch of Makefile's "Automatic Variables"
.cpp.o:
	$(COMPILER) $(CFLAGS) $<

.c.o:
	$(COMPILER) $(CFLAGS) $<

#Actual Makefile targets
dev: CFLAGS += -Wall -Wpedantic -Wextra -g -DDEBUG
dev: $(OBJECTS) Logger.o
	$(COMPILER) -o $(EXECUTABLE) $(OBJECTS) Logger.o $(LFLAGS)

production: $(OBJECTS)
	$(COMPILER) -o $(EXECUTABLE) $(OBJECTS) $(LFLAGS)

clean:
	rm $(EXECUTABLE) *.o