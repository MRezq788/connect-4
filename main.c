#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ROWS 6
#define COLS 7
char disc[] = "XO";
typedef struct{

	int num;
	int moves;
	char disc;
	int score;
	
}player;

player player1, player2;
//score function >> evaluate score after each move 
void score(char grid[ROWS][COLS]){
	static turn = 0;

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
	for(i = ROWS - 1; i > 2; i--){
		for(j = 0 ; j < COLS ; j++){
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
//last_row function >> returns index of last empty row in specific columns
int last_row(int col/*users col*/, int lastrow[col]){
	if(lastrow[col - 1] == 0){
		lastrow[col - 1 ] = ROWS - 1;
		return lastrow[col - 1]; 
	}else{
		lastrow[col - 1] = lastrow[col - 1] - 1;
		return lastrow[col - 1];
	}
}
//print_grid function
void print_grid(char grid[ROWS][COLS])
{
    int i ,j;

    system("color a");                     //TO COLOR THE BOARD
    for ( i = 0; i < ROWS; i++)
    {
        for ( j = 0; j < COLS; j++)
        {
            printf("+---");
        }
        printf("+\n");
        for ( j = 0; j < COLS; j++)
        {
            if(grid[i][j] != disc[0] && grid[i][j] != disc[1]  ){
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
	int lastrow[COLS];
	memset(lastrow , 0 ,sizeof lastrow);
	char grid[ROWS][COLS];
	print_grid(grid);

	return 0;
}
