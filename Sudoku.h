#include <iostream>
#include <vector>
#include <iomanip>

class Sudoku
{
    public:
        Sudoku();
        void GiveQuestion();
        void ReadIn();
        void Solve();
        void Solve_strategy1();
	void Solve_strategy2();
	void FirstCheck();
	void Check();
	void CheckAfterFill(int i);
	void PrintOut();
        static const int sudokuSize = 81;
    private:
        int cell[sudokuSize];
        int possibility[sudokuSize][10];
};


