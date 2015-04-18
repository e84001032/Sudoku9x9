#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>
class Sudoku
{
    public:
        Sudoku();
        void ReadIn();
        void Solve();
        void GiveQuestion();
    protected:
    private:
        void FirstCheck();
        void CheckAfterFill(int x,int y);
        void Solving();
        void Solve_strategy1();
        void Solve_strategy2();
        int backtracking(int board[][9]);
        int checkvalid(int board[][9], int x, int y);
        int ZeroCount();
        int isSolved(int board[][9]);
        int paste(int a[][9], int b[][9]);
        void PrintOut();
        int ans;
        int cell[9][9];
        int Ans[9][9];
        int possibility[9][9][10];
};

