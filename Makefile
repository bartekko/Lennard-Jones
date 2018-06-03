
all: main

main: main.cpp
	g++ main.cpp -o a.out -Ofast -Wall -lSDL2 -Wfatal-errors -g

