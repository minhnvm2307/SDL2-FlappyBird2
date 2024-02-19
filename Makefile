all: main run

main: main.cpp
	g++ -std=c++17 -I include -L lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2

run: main
	./main.exe

.PHONY: all run
