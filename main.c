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
	char name[];

}player;


player player1, player2;
char disc[] = "XO";

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

    /*system("color f1");*/ //TO COLOR THE BOARD
    for( int ii = 1;ii <= COLS; ii++){
          if(log10(ii)<1){
            printf("  %d ",ii);
          }
          else{
            printf(" %d",ii);
          }
    }
        printf("\n");
    for ( i = 0; i < ROWS; i++)
    {
        for ( j = 0; j < COLS; j++)
        {
            printf("+---");
        }
        printf("+\n");
        for ( j = 0; j < COLS; j++)
        {
            if(grid[i][j] != 'X' && grid[i][j] != 'O'  ){
				printf("|   ");
				}
				else{
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
void move(char grid[ROWS][COLS]){

    int static turn=0;
    int lastr[COLS],col;

    memset(lastr, 0 ,sizeof lastr);
    int n=ROWS*COLS;

    while(n!=0){
        scanf("%d",&col);
        while(col>COLS){               //checking limits
            printf("INVALID INPUT\n");
            scanf("%d",&col);
        }

        int r=last_row(col,lastr);
       /* while( grid[r][col-1]=='X'||grid[r][col-1]=='O'){
            printf("Choose another col\n");
            scanf("%d",&col);
        }*/


        grid[r][col-1]=disc[turn];
        print_grid(grid);

        if(disc[turn]=='X'){     //count moves
            player1.moves++;
        }
        if(disc[turn]=='O'){
            player2.moves++;
        }

        turn=1-turn;     //taking turns
        n--;
        score(grid);
        printf("P1 score : %d  P2 score: %d\n",player1.score,player2.score);
        printf("P1 moves : %d  P2 moves: %d\n",player1.moves,player2.moves);
    }
}
/*void time(){

}*/
int main() {

	int lastrow[COLS],col;
	memset(lastrow , 0 ,sizeof lastrow );

	char grid[ROWS][COLS];

	print_grid(grid);

	player1.disc = 'X';
	player2.disc = 'O';

	move(grid);
   return 0;
}
