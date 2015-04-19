#include "Sudoku.h"
using namespace std;

Sudoku::Sudoku()
{
    ans = 0;
    for(int x = 0 ; x < 9 ; x++)
        for(int y = 0 ; y < 9; y++)
            cell[x][y] = 0;

}

void Sudoku::ReadIn(){
    for(int x = 0 ; x < 9 ; x++)
        for(int y = 0 ; y < 9 ; y ++)
            cin >> cell[x][y];
}

void Sudoku::Solve(){
    Solving(cell);
    backtracking(cell);
    PrintOut();
}

void Sudoku::FirstCheck(int board[][9]){
    //check all possibilities for every 0 cell
    for(int x = 0 ; x < 9 ; x++){
        for(int y = 0; y < 9; y++){
            if(board[x][y] == 0){
                for(int j = 1 ; j < 10 ; j++){
                    possibility[x][y][j] = 1;
                }
                possibility[x][y][0] = 9;
            }
            else{
                for(int j = 0 ; j < 10 ; j++){
                    possibility[x][y][j] = 0;
                }
            }
        }
    }
    for(int x = 0 ; x < 9 ; x++){
        for(int y = 0; y < 9 ; y++){
            if(board[x][y] == 0){
                for(int j = 0 ; j < 9 ; j++){
                    //check row
                    if(j!=y && board[x][j] != 0 && board[x][j] != -1){
                        if(possibility[x][y][board[x][j]] == 1){
                            possibility[x][y][board[x][j]] -= 1;
                            possibility[x][y][0] -= 1;
                        }
                    }
                    //check col
                    if(j!=x && board[j][y] != 0 && board[j][y] != -1){
                        if(possibility[x][y][board[j][y]] == 1){
                            possibility[x][y][board[j][y]] -= 1;
                            possibility[x][y][0] -= 1;
                        }
                    }
                }
                for(int n = 0; n < 9; n++){
                    int xx = x/3*3+n%3;
                    int yy = y/3*3+n/3;
                    if(xx!=x && yy!=y && board[xx][yy]!=0 && board[xx][yy]!=-1){
                        if(possibility[x][y][board[xx][yy]] == 1){
                            possibility[x][y][board[xx][yy]] -= 1;
                            possibility[x][y][0] -= 1;
                        }
                    }
                }
            }
        }
    }
}

void Sudoku::CheckAfterFill(int x,int y,int board[][9]){
    int value = board[x][y];
    for(int j = 0 ; j < 10 ; j ++){
        possibility[x][y][j] = 0;
    }
    for(int j = 0 ; j < 9 ; j++){
        if( possibility[x][j][value] == 1){
            possibility[x][j][value] -= 1;
            possibility[x][j][0] -= 1;
        }
        if( possibility[j][y][value] == 1){
            possibility[j][y][value] -= 1;
            possibility[j][y][0] -= 1;
        }
    }
    for(int n = 0 ; n < 9 ; n++){
        int xx = x/3*3+n%3;
        int yy = y/3*3+n/3;
        if( possibility[xx][yy][value] == 1){
            possibility[xx][yy][value] -= 1;
            possibility[xx][yy][0] -= 1;
        }

    }

}

void Sudoku::Solving(int board[][9]){
    FirstCheck(board);
    while(true){
        int before = ZeroCount(board);
        Solve_strategy1(board);
        Solve_strategy2(board);
        int after = ZeroCount(board);
        if(before == after) break;
    }
}

void Sudoku::Solve_strategy1(int board[][9]){
    //check all possibilities for every 0 cell
    for(int x = 0 ; x < 9 ; x++){
        for(int y = 0 ; y < 9 ; y++)
            if(board[x][y] == 0){
            if(possibility[x][y][0] == 1){
                for(int j = 1 ; j < 10 ; j++){
                    if(possibility[x][y][j] == 1){
                        board[x][y] = j;
                        CheckAfterFill(x,y,board);
                        break;
                    }
                }
            }
        }
    }
}

void Sudoku::Solve_strategy2(int board[][9]){
    //check row
    for(int x = 0 ; x < 9 ; x ++){
        for(int i = 1 ; i < 10; i ++){
            int countpossibility = 0;
            for(int y = 0 ; y < 9 ; y ++){
                if( possibility[x][y][i] == 1) countpossibility += 1;
            }
            if(countpossibility == 1){
                for(int y = 0 ; y < 9 ; y ++){
                    if( possibility[x][y][i] == 1){
                        board[x][y] = i;
                        CheckAfterFill(x,y,board);
                        break;
                    }
                }
            }
        }
    }
    //check col
    for(int y = 0 ; y < 9 ; y++){
        for(int i = 1 ; i < 10; i++){
            int countpossibility = 0;
            for(int x = 0 ; x < 9 ; x++){
                if( possibility[x][y][i] == 1) countpossibility += 1;
            }
            if(countpossibility == 1){
                for(int x = 0 ; x < 9 ; x++){
                    if( possibility[x][y][i] == 1){
                        board[x][y] = i;
                        CheckAfterFill(x,y,board);
                        break;
                    }
                }
            }
        }
    }
    //check zone
    int xx,yy;
    for(int x = 0 ; x < 9 ; x++){
        for(int y = 0 ; y < 9 ; y++){
            for(int i = 1 ; i < 10; i++){
                int countpossibility = 0;
                for(int n = 0 ; n < 9 ; n++){
                    xx = x/3*3+n%3;
                    yy = y/3*3+n/3;
                    if(possibility[xx][yy][i] == 1) countpossibility += 1;
                }
                if(countpossibility == 1){
                    for(int n = 0 ; n < 9 ; n++){
                        xx = x/3*3+n%3;
                        yy = y/3*3+n/3;
                        if(possibility[xx][yy][i] == 1){
                            board[xx][yy] = i;
                            CheckAfterFill(xx,yy,board);
                            break;
			}
                    }
                }
            }
        }
    }
}

int Sudoku::backtracking(int board[][9]){
    if (isSolved(board)){
	ans++;
        return paste(Ans, board);
    }
    int newboard[9][9];
    paste(newboard, board);

    for (int x=0;x<9;x++)
        for (int y=0;y<9;y++)
            if (newboard[x][y]==0){
                for (int n=1;n<=9;n++){
                    newboard[x][y]=n;
                    if (checkvalid(newboard, x, y)==1){
			Solving(newboard);
                        if(backtracking(newboard));
		    }
		    paste(newboard,board);
		    if(ans>1) break;
                }
                return 0;
            }
    return 0;
}

int Sudoku::checkvalid(int board[][9], int x, int y){
    int xx, yy;
    for(int n = 0; n < 9; n++){
        xx = x/3*3+n%3;
        yy = y/3*3+n/3;
        if (x!=xx && y!=yy && board[xx][yy]==board[x][y])
            return 0;
    }
    for(int n = 0; n < 9 ;n++){
        if ((n!=y && board[x][n]==board[x][y]) || (n!=x && board[n][y]==board[x][y]))
            return 0;
    }
    return 1;
}

int Sudoku::ZeroCount(int board[][9]){
    int zerocount = 0;
    for(int x = 0 ; x < 9 ; x++)
        for(int y = 0 ; y < 9 ; y++)
            if(board[x][y] == 0) zerocount += 1;
    return zerocount;
}


int Sudoku::isSolved(int board[][9]){
    int x, y;
    for (x = 0;x < 9; x++)
        for (y = 0; y < 9; y++)
            if (board[x][y]==0)
                return 0;
    return 1;
}

int Sudoku::paste(int a[][9], int b[][9]){
    int x,y;
    for (x = 0; x < 9; x++)
        for (y = 0; y < 9; y++)
            a[x][y] = b[x][y];
    return 1;
}

void Sudoku::PrintOut(){
    if(ans < 2) cout << ans << endl;	
    else cout << 2 << endl;	 
    if(ans == 1){
        for(int x = 0 ; x < 9 ; x++){
            for(int  y = 0 ; y < 9 ; y++){
                cout << setw(3) << Ans[x][y];
            }
            cout << endl;
        }
    }
    
}

void Sudoku::GiveQuestion(){
    srand(time(NULL));
    int a,b,c,d,e,f,g,h,i;
    int num[9] = {1,2,3,4,5,6,7,8,9}; 
    for(int j = 0 ; j < 9 ; j ++){
	int tmp;
	int ex = rand()%9;
	tmp = num[j];
	num[j] = num[ex];
	num[ex] = tmp;
    }
    a = num[0];
    b = num[1];
    c = num[2];
    d = num[3];
    e = num[4];
    f = num[5];
    g = num[6];
    h = num[7];
    i = num[8];
    int question[9][9] =     {{ a, b, c, d, e, f, g, h, i},
                                { d, e, f, g, h, i, a, b, c},
                                { g, h, i, a, b, c, d, e, f},
                                { b, c, a, e, f, d, h, i, g},
                                { e, f, d, h, i, g, b, c, a},
                                { h, i, g, b, c, a, e, f, d},
                                { c, a, b, f, d, e, i, g, h},
                                { f, d, e, i, g, h, c, a, b},
                                { i, g, h, c, a, b, f, d, e}};
    int temp[9][9];
    int count = 0;
    int holes = 70;
    for(int j = 0 ; j < holes ; j++){
        int x = rand()%9;
	int y = rand()%9; 
        if(question[x][y] > 0){ 
	    paste(temp,question);
	    temp[x][y] = 0;
	    Solving(temp);
	    backtracking(temp);
	    if(ans>1){ 
		j--; 
		ans=0; 
		if(++count > 100) break;
	    }
	    else{ 
		question[x][y] = 0;
		count = 0;
	    }
	}
        else j--;
    }
    
    int rand_1;
    int rand_2;
    int tmp_ele;
    for(int i = 0 ; i < 100 ; i++){
	rand_1 = rand()%9;
	rand_2 = rand_1/3*3+rand()%3;
	for(int j = 0 ; j < 9 ; j++){ // 兩行互換(同一區塊內ex 012 345 678 ...)
	    tmp_ele = question[rand_1][j];
	    question[rand_1][j] = question[rand_2][j];
	    question[rand_2][j] = tmp_ele;
	}
	rand_1 = rand()%9;
        rand_2 = rand_1/3*3+rand()%3;
	for(int j = 0 ; j < 9 ; j++){ // 兩欄互換(同一區塊內)
	    tmp_ele = question[j][rand_1];
	    question[j][rand_1] = question[j][rand_2];
	    question[j][rand_2] = tmp_ele;
	}
	rand_1 = rand()%9/3*3;
	rand_2 = rand()%9/3*3;
	for(int j = 0 ; j < 3 ; j++){
	    for(int k = 0 ; k < 9 ; k++){
		tmp_ele = question[rand_1+j][k];
		question[rand_1+j][k] = question[rand_2+j][k];
		question[rand_2+j][k] = tmp_ele; 
	    }
	}
	rand_1 = rand()%9/3*3;
        rand_2 = rand()%9/3*3;
	for(int j = 0 ; j < 3 ; j++){
	    for(int k = 0 ; k < 9 ; k++){
		tmp_ele = question[k][rand_1+j];
		question[k][rand_1+j] = question[k][rand_2+j];
		question[k][rand_2+j] = tmp_ele;
	    }
	}
    }
	    
    for(int x = 0 ; x < 9 ; x ++){
        for(int y = 0 ; y < 9 ; y ++){
            cout << setw(3) << question[x][y];
	}
	cout << endl;
    }
}

