INCLUDE = -I/usr/include/ 
LIBRARIES =  -lGL -lSDL -lGLEW
SOURCE  = main.cpp shaders.cpp 
HEADERS = shaders.h
OBJECTS = ${SOURCE:.c=.o}                              
PROJECT = shadertest
                                    
CC        = g++
CFLAGS    = -O -Wall $(INCLUDE) $(LIBRARIES)                     

%.o : %.c
	$(CC) $(CFLAGS) -c $< 

compile: ${OBJECTS}                                      
	${CC} -o $(PROJECT) `sdl-config --libs` ${OBJECTS}  $(LIBRARIES)                    

all: compile                                             

clean:                                                
	rm -f *.o *~ $(PROJECT)                      
