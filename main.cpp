#include <iostream>
#include "Sudoku.h"
using namespace std;

int main(){
	Sudoku su;
	su.ReadIn();
	su.Solve();
	return 0;
}
