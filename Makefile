
all: main

main: main.cpp
	g++ main.cpp -o main -Ofast -Wall -lSDL2 -Wfatal-errors -g

two: main2.cpp
	g++ main2.cpp -o main2 -Ofast -Wall -lSDL2 -Wfatal-errors -g

