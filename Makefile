main: solve.o Sudoku.o GiveQuestion.o
	g++ -o Solve Sudoku.o solve.o
	g++ -o GiveQuestion Sudoku.o GiveQuestion.o
Sudoku.o: Sudoku.cpp Sudoku.h
	g++ -c Sudoku.cpp
solve.o: solve.cpp Sudoku.h
	g++ -c solve.cpp
GiveQuestion.o: GiveQuestion.cpp Sudoku.h
	g++ -c GiveQuestion.cpp
clean:
	rm *.o
