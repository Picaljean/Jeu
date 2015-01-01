CXXFLAGS=-std=c++0x -lSDLmain -lSDL -lSDL_image -lSDL_ttf

all: clean main

main: main.o jeux.o
	g++ -o jeu main.o jeux.o $(CXXFLAGS)

main.o: main.cpp
	g++ -c main.cpp $(CXXFLAGS)

jeux.o: jeux.cpp
	g++ -c jeux.cpp $(CXXFLAGS)

clean:
	rm -rf *.o