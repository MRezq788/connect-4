#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ROWS 6
#define COLS 7

typedef struct{

	int num;
	int moves;
	char disc;
	int score;
	
}player;

player player1, player2;

void score(char grid[ROWS][COLS]){
	static turn = 0;
	char disc[] = "XO";
	int i, j;
	int score = 0;
	//check horizontal
	for(i = ROWS - 1; i >= 0; i--){
		for(j = 0; j < (COLS - 3); j++){
			if(grid[i][j] == disc[turn] && grid[i][j + 1] == disc[turn] && grid[i][j + 2] == disc[turn] && grid[i][j + 3] == disc[turn]){
				score += 1;
			}
		}	
	}
	//check vertical
	for(j = 0 ; j < COLS ; j++){
		for(i = ROWS - 1; i > 2; i--){
			if(grid[i][j] == disc[turn] && grid[i - 1][j] == disc[turn] && grid[i - 2][j] == disc[turn] && grid[i - 3][j] == disc[turn]){
				score += 1;
			}
		}	
	}
	//check diagonal
	//check bottom left to right
	for(i = ROWS - 1; i > 2; i--){
		for(j = 0; j < COLS - 3; j++){
			if(grid[i][j] == disc[turn] && grid[i - 1][j + 1] == disc[turn] && grid[i - 2][j + 2] == disc[turn] && grid[i - 3][j + 3] == disc[turn]){
				score += 1;
			}
		}
	}
	//check bottom right to left
	for(i = ROWS - 1; i > 2; i--){
		for(j = COLS - 1; j > 2 ; j--){
			if(grid[i][j] == disc[turn] && grid[i - 1][j - 1] == disc[turn] && grid[i - 2][j - 2] == disc[turn] && grid[i - 3][j - 3] == disc[turn]){
				score += 1;
			}
		}
	}
	if(turn == 0){
		player1.score += score;
	}else{
		player2.score += score;
	}
	turn = 1 - turn;
}
 
int lastrow(int col){
	static int lastrow[column];
	memset(lastrow , 0 ,sizeof lastrow );
	int i;
	if(lastrow[col] == 0){
		lastrow[col] = ROWS - 1;
		return lastrow; 
	}else{
		return lastrow[col];
	}
}

void print_grid()
{
    int i ,j;

    system("color f1");                     //TO COLOR THE BOARD
    for ( i = 0; i < ROWS; i++)
    {
        for ( j = 0; j < COLS; j++)
        {
            printf("+---");
        }
        printf("+\n");
        for ( j = 0; j < COLS; j++)
        {
            if(grid[i][j] != "X" && grid[i][j] != "O"  ){
				printf("|   ");
				}else{
					printf("| %c ", grid[i][j]);
				}
			
        }
        printf("|\n");
    }
    for ( j = 0; j < COLS; j++)
        {
            printf("+---");
        }
        printf("+\n");
}


int main() {
	
	char grid[ROWS][COLS];
	print_grid();
	player1.disc = "X";
	player2.disc = "O";
	
	return 0;
}
