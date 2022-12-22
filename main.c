#include <stdio.h>
#include <stdlib.h>
#define ROWS 6
#define COLS 7

typedef struct{

	int num;
	int moves;
	char disc;
	int score;
	
}player;

player player1, player2;

int score(char grid[ROWS][COLS]){
	int i, j;
	int score = 0;
	//check horizontal
	for(i = ROWS - 1; i >= 0; i--){
		for(j = 0; j < (COLS - 3); j++){
			if(grid[i][j] == player.disc && grid[i][j + 1] == player.disc && grid[i][j + 2] == player.disc && grid[i][j + 3] == player.disc){
				score += 1;
			}
		}	
	}
	//check vertical
	for(j = 0 ; j < COLS ; j++){
		for(i = ROWS - 1; i > 2; i--){
			if(grid[i][j] == player.disc && grid[i - 1][j] == player.disc && grid[i - 2][j] == player.disc && grid[i - 3][j] == player.disc){
				score += 1;
			}
		}	
	}
	//check diagonal
	//check bottom left to right
	for(i = ROWS - 1; i > 2; i--){
		for(j = 0; j < COLS - 3; j++){
			if(grid[i][j] == player.disc && grid[i - 1][j + 1] == player.disc && grid[i - 2][j + 2] == player.disc && grid[i - 3][j + 3] == player.disc){
				score += 1;
			}
		}
	}
	//check bottom right to left
	for(i = ROWS - 1; i > 2; i--){
		for(j = COLS - 1; j > 2 ; j--){
			if(grid[i][j] == player.disc && grid[i - 1][j - 1] == player.disc && grid[i - 2][j - 2] == player.disc && grid[i - 3][j - 3] == player.disc){
				score += 1;
			}
		}
	}
	
	return score;	
}

void print_grid()
{
    int i ,j;
	system(" ");
    printf("\033[0;31m");
    for ( i = 0; i < ROWS; i++)
    {
        for ( j = 0; j < COLS; j++)
        {
            printf("|---");
        }
        printf("|\n");
        for ( j = 0; j < COLS; j++)
        {
            printf("|   ");
        }
        printf("|\n");
    }
}

int main() {
	
	char grid[ROWS][COLS];
	print_ grid();
	player1.disc = "X";
	plaer2.disc = "O";
	
	return 0;
}
