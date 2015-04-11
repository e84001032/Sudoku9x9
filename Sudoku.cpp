#include "Sudoku.h"
using namespace std;

Sudoku::Sudoku()
{
    for(int i = 0 ; i < sudokuSize ; i++){
        cell[i] = 0;
    }
}

void Sudoku::ReadIn(){
    for(int i = 0 ; i < sudokuSize ; i++){
        cin >> cell[i];
    }
}

void Sudoku::Solve(){
    
    if(Process()){
	PrintOut();
    }
    else
	cout << "no solution" << endl;

}

bool Sudoku::Process(){
    FirstCheck();
    while(true){
	int before = ZeroCount();
	Solve_strategy1();
	Solve_strategy2();
	int after = ZeroCount();
	if(after == 0) return true;
	if(after == before) break;
    }
    int processing = GetNextZero();
    for(int i = 1 ; i < 10 ; i ++){
	if(possibility[processing][i] == 1){
	    cell[processing] = i;
	    if(Process()) return true;
	    cell[processing] = 0;
	}
    }
    return false;
}

int Sudoku::GetNextZero(){
    int i;
    for( i = 0 ; i < sudokuSize ; i ++){
	if(cell[i] == 0) return i;
    }
    return -1;
}

int Sudoku::ZeroCount(){
    int zerocount = 0 ;
    for(int i = 0 ; i < sudokuSize ; i++){
        if(cell[i] == 0){
	    zerocount += 1;
        }	
    } 
    return zerocount;
}

void Sudoku::Solve_strategy1(){
    //check all possibilities for every 0 cell
    for(int i = 0 ; i < sudokuSize ; i++){
        if(cell[i] == 0){ 
	    if(possibility[i][0] == 1){
		for(int j = 1 ; j < 10 ; j++){
	    	    if(possibility[i][j] == 1){
			cell[i] = j;
			CheckAfterFill(i);
			break;
		    }	
		}		
	    }
	}
    }
}
void Sudoku::FirstCheck(){
    //check all possibilities for every 0 cell
    for(int i = 0 ; i < sudokuSize ; i++){
        if(cell[i] == 0){
	   for(int j = 1 ; j < 10 ; j++){
		possibility[i][j] = 1;
            }	
            possibility[i][0] = 9;
	}
	else{
            for(int j = 1 ; j < 10 ; j++){
                possibility[i][j] = 0;
            }
            possibility[i][0] = 0;
	} 
    }
    for(int i = 0 ; i < sudokuSize ; i++){
        if(cell[i] == 0){
            int row = i/9;
            int col = i%9;
            int zonerow = i/27;
            int zonecol = i%9/3;
            int zone[9] = {0,1,2,9,10,11,18,19,20};
            for(int j = 0 ; j < 9 ; j++){
                zone[j] += zonerow * 27 + zonecol * 3;
            }
            for(int j = 0 ; j < 9 ; j++){
                //check row
                if(cell[row*9+j] != 0){
		    if(possibility[i][cell[row*9+j]] == 1){
                        possibility[i][cell[row*9+j]] -= 1;
                        possibility[i][0] -= 1;
                    }
                }
                //check col
                if(cell[col+j*9] != 0){
                    if(possibility[i][cell[col+j*9]] == 1){
                        possibility[i][cell[col+j*9]] -= 1;
                        possibility[i][0] -= 1;
                    }
                }
            }
            for(int j = 0 ; j < 9 ; j++){
                //check zone
                if(cell[zone[j]] != 0 && cell[zone[j]] != -1){
		    if( possibility[i][cell[zone[j]]] == 1){
                        possibility[i][cell[zone[j]]] -= 1;
                        possibility[i][0] -= 1;
                    }
                }
            }
	}
    }
}
void Sudoku::Solve_strategy2(){
    //check row from 1 to 9 if there's only one cell can be filled with the number then fill
    for(int row = 0 ; row < 9 ; row ++){
	for(int i = 1 ; i < 10; i ++){
            int countpossibility = 0;
     	    for(int j = 0 ; j < 9 ; j ++){
	        if( possibility[row*9+j][i] == 1) countpossibility += 1;
	    }
	    if(countpossibility == 1){
	        for(int j = 0 ; j < 9 ; j ++){
		    if( possibility[row*9+j][i] == 1){
			cell[row*9+j] = i;
			CheckAfterFill(row*9+j);
			break;
		    }
	    	}
	    }
	}
    }
    //check col from 1 to 9 if there's only one cell can be filled with the number then fill
    for(int col = 0 ; col < 9 ; col ++){
        for(int i = 1 ; i < 10; i ++){
            int countpossibility = 0;
            for(int j = 0 ; j < 9 ; j ++){
                if( possibility[col+j*9][i] == 1) countpossibility += 1;
            }
            if(countpossibility == 1){
                for(int j = 0 ; j < 9 ; j ++){
                    if( possibility[col+9*j][i] == 1){
                        cell[col+9*j] = i;
			CheckAfterFill(col+9*j);
			break;
                    }
                }
            }
        }
    }
    //check zones from 1 to 9 if there's only one cell can be filled with the number then fill
    for(int numofzone = 0 ; numofzone < 9 ; numofzone ++){
        int zone[9] = {0,1,2,9,10,11,18,19,20};
	for(int i = 0 ; i < 9 ; i++){
	    zone[i] += numofzone%3*3 + numofzone/3*27;
	}
        for(int i = 1 ; i < 10; i ++){
            int countpossibility = 0;
            for(int j = 0 ; j < 9 ; j ++){
                if(possibility[zone[j]][i] == 1) countpossibility += 1;
            }
            if(countpossibility == 1){
                for(int j = 0 ; j < 9 ; j ++){
                    if(possibility[zone[j]][i] == 1){
                        cell[zone[j]] = i;
			CheckAfterFill(zone[j]);
			break;
                    }
                }
            }
        }
    }
}
void Sudoku::Check(){
    for(int i = 0 ; i < sudokuSize ; i++){
        if(cell[i] == 0){
            int row = i/9;
            int col = i%9;
            int zonerow = i/27;
            int zonecol = i%9/3;
            int zone[9] = {0,1,2,9,10,11,18,19,20};
            for(int j = 0 ; j < 9 ; j++){
                zone[j] += zonerow * 27 + zonecol * 3;
            }
            for(int j = 0 ; j < 9 ; j++){
                //check row
                if(cell[row*9+j] != 0){
		    if(possibility[i][cell[row*9+j]] == 1){
                        possibility[i][cell[row*9+j]] -= 1;
                        possibility[i][0] -= 1;
                    }
                }
                //check col
                if(cell[col+j*9] != 0){
                    if(possibility[i][cell[col+j*9]] == 1){
                        possibility[i][cell[col+j*9]] -= 1;
                        possibility[i][0] -= 1;
                    }
                }
            }
            for(int j = 0 ; j < 9 ; j++){
                //check zone
                if(cell[zone[j]] != 0 && cell[zone[j]] != -1){
		    if( possibility[i][cell[zone[j]]] == 1){
                        possibility[i][cell[zone[j]]] -= 1;
                        possibility[i][0] -= 1;
                    }
                }
            }
	}
	else{
	    for(int j = 0 ; j < 10 ; j ++){
		possibility[i][j] = 0 ;
	    }
	}
    }
}

void Sudoku::CheckAfterFill(int i){    
    int value = cell[i];
    int row = i/9;
    int col = i%9;
    int zonerow = i/27;
    int zonecol = i%9/3;
    int zone[9] = {0,1,2,9,10,11,18,19,20};
    for(int j = 0 ; j < 9 ; j++){
        zone[j] += zonerow * 27 + zonecol * 3;
    }
    for(int j = 0 ; j < 10 ; j ++){
	possibility[i][j] = 0;
    }
    for(int j = 0 ; j < 9 ; j++){
	if( possibility[row*9+j][value] == 1){ 
	    possibility[row*9+j][value] -= 1;
	    possibility[row*9+j][0] -= 1;
	} 
	if( possibility[col+9*j][value] == 1){
            possibility[col+9*j][value] -= 1;
            possibility[col+9*j][0] -= 1;
	}
	if( possibility[zone[j]][value] == 1){
            possibility[zone[j]][value] -= 1;
            possibility[zone[j]][0] -= 1;
        }

    }
		    
}

void Sudoku::PrintOut(){
    for(int i = 0 ; i < 9 ; i++ ){
	for(int j = 0 ; j < 9 ; j ++){
            cout << setw(3) << cell[i*9+j]; 
	}
	cout << endl;
    }
}

void Sudoku::GiveQuestion(){
    int a,b,c,d,e,f,g,h,i;
    
    
}
