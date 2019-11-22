CC = g++
CFLAGS = -c -std=c++11 -g -Wall
INC = -I include

sudoku_solver: main.o sudoku_fun.o
	$(CC) build/main.o build/sudoku_fun.o -o sudoku_solver

main.o:
	mkdir -p build
	$(CC) $(CFLAGS) $(INC) src/main.cpp -o build/main.o

sudoku_fun.o:
	$(CC) $(CFLAGS) $(INC) src/sudoku_functions.cpp -o build/sudoku_fun.o

clean:
	rm -r -f build
