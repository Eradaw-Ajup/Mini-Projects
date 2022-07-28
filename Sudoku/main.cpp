#include "bits/stdc++.h"
using namespace std;

void print_board(vector<vector<int> > &board){
	for (int i = 0; i < 9; i++){
		cout << "	";
		if (i%3 == 0)
			cout << "-------------------------\n	";

		for (int j = 0; j < 9; j++){
			if (j%3 == 0)
				cout << "| ";
			cout << board[i][j] << " ";
		}
		cout << "| \n";
	}
	cout << "	";
	cout << "-------------------------\n";
}

bool check_function(int x, int y, int k, vector<vector<int> > &board){
	
	// checking for entire row
	for (int j = 0; j < 9; j++)
		if (board[x][j] == k)
			return false;
	

	// checking for entire column;
	for (int i = 0; i < 9; i++)
		if (board[i][y] == k)
			return false;

	// checking for entire block
	// for loop i%3 == 0 1 2 similarily j%3 == 0 1 2

	for (int i = x-(x%3); i < x+3 - (x%3); i++)
		for (int j = y-(y%3); j < y+3 - (y%3); j++)
			if (board[i][j] == k)
				return false;
	return true;
}

bool complete_sudoku(vector<vector<int> > &board){
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			if (board[i][j] == 0)
				return false;
	return true;
}



bool solve_board(int r, int c, vector<vector<int> > &board){
	if (r == 8 and c == 9)
		return true;
	if (c == 9)
		r++, c = 0;
	if (board[r][c] != 0)
		return solve_board(r, c+1,board);
	for (int k = 1; k < 10; k++){
		if (check_function(r,c,k,board)){
			board[r][c] = k;
			if (solve_board(r,c+1, board))
				return true;
		}
		board[r][c] = 0;
	}
	return false;
}

void sudoku_generator(vector<vector<int> > &board){

	int counter = 36;

	while (counter){
		int k = rand()%9 + 1;
		int i = rand()%9, j = rand()%9;
		if (check_function(i,j,k,board)){

			
			vector<vector<int> > temp = board;
			temp[i][j] = k; 
			if (solve_board(0,0,temp))
				board[i][j] = k, counter--;
		}
	}

}

int main(){
	vector<vector<int> > board(9, vector<int>(9));
	// board[0][0]	= 8;board[0][3] = 9; board[0][5] = 1;board[0][7] = 2;
	// board[1][0]	= 2;board[1][2] = 3; board[1][4] = 6;board[1][5] = 4;
	// board[2][2]	= 6;board[2][8] = 7; 
	// board[3][0]	= 1;board[3][4] = 9; 
	// board[4][2]	= 8;board[4][6] = 9; board[4][7] = 6;
	// board[5][3]	= 6;board[5][5] = 3; board[5][6] = 7;board[5][8] = 8;
	// board[6][1]	= 9;board[6][2] = 5; board[6][4] = 8;board[6][5] = 6;board[6][6] = 2; board[6][7] = 7;board[6][8] = 1;
	// board[7][1]	= 4;board[7][2] = 1; board[7][8] = 3;
	// board[8][1]	= 8;board[8][2] = 2; board[8][3] = 1;board[8][4] = 3;board[8][5] = 5; board[8][6] = 6;board[8][7] = 4;
	// for (int i =0 ; i < 9; i++)
	// 	for (int j = 0; j < 9; j++)
	// 		cin >> board[i][j];
	srand(time(0));
	system("clear");
	sudoku_generator(board);
	cout << "Puzzle : \n";
	print_board(board);
	solve_board(0,0,board);
	cout << "Solution : \n";
	print_board(board);
	return 0;
}




















