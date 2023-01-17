# /***********************************************************************
# * FILENAME :        Makefile
# *
# * DESCRIPTION :
# *       Course: Advanced Programming Techniques for Engineering Applications (ECE-6122)
# *       Term: 2022-Fall
# *       Problem: Lab3
# *
# * NOTES :
# *       Copyright Chun-wei Ho, 2022.  All rights reserved.
# *
# * AUTHOR :    Chun-wei Ho        START DATE :    22 Oct. 22
# *
# * CHANGES :
# *
# * VERSION DATE    WHO     DETAIL
# * 1.0.0   22Oct22 CH      First edition
# *
# */

CXX:=g++
CFLAG:=-O3
LDFLAGS:=-L"C:\Program Files (x86)\SFML\lib" # chnage this to SFML installation directory
LDLIBS:=-lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
OUTPUT:=pacman

# Link all the dependencies
all: bin/main.o bin/window.o bin/map.o bin/agents.o bin/music.o
	$(CXX) $(CFLAG) $^ -o $(OUTPUT) $(LDLIBS) $(LDFLAGS)

# main function
bin/main.o: src/main.cpp src/window.h | bin

# displayer
bin/window.o: src/window.cpp src/window.h src/map.h src/constants.h src/music.h | bin

# record game status (map, locations, etc)
bin/map.o: src/map.cpp src/map.h src/agents.h src/constants.h src/music.h | bin

# manage pacman and ghosts
bin/agents.o: src/agents.cpp src/agents.h src/constants.h | bin

# manage music/sound effect
bin/music.o: src/music.cpp src/music.h | bin

# compile object files
%.o:
	$(CXX) $(CFLAG) $< -o $@ -c

# create bin folder
bin:
	mkdir -p $@

# .PHONY target, clean up binary files
clean:
	rm -rf bin
	rm -rf $(OUTPUT)
	rm -rf $(OUTPUT).exe # For windows system
