#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ROWS 6
#define COLS 7

char disc[] = "XO";
char grid[ROWS][COLS];
typedef struct{
	int moves;
	char disc;
	int score;
	
}player;

player player1, player2;
//score function >> evaluate score after each move 
void score(){
	static turn = 0;

	int i, j;
	int score = 0;
	//check horizontal
	for(i = ROWS - 1; i >= 0; i--){
		for(j = 0; j < (COLS - 3); j++){
			if((grid[i][j] == disc[turn] )&&( grid[i][j + 1] == disc[turn] )&&( grid[i][j + 2] == disc[turn] )&&( grid[i][j + 3] == disc[turn])){
				score += 1;
			}
		}	
	}
	//check vertical
	for(i = ROWS - 1; i > 2; i--){
		for(j = 0 ; j < COLS ; j++){
			if((grid[i][j] == disc[turn] )&&( grid[i - 1][j] == disc[turn] )&&( grid[i - 2][j] == disc[turn] )&&( grid[i - 3][j] == disc[turn])){
				score += 1;
			}
		}	
	}
	//check diagonal
	//check bottom left to right
	for(i = ROWS - 1; i > 2; i--){
		for(j = 0; j < COLS - 3; j++){
			if((grid[i][j] == disc[turn] )&&( grid[i - 1][j + 1] == disc[turn] )&&( grid[i - 2][j + 2] == disc[turn] )&&( grid[i - 3][j + 3] == disc[turn])){
				score += 1;
			}
		}
	}
	//check bottom right to left
	for(i = ROWS - 1; i >= 3; i--){
		for(j = COLS - 1; j >=3 ; j--){
			if((grid[i][j] == disc[turn] )&&( grid[i - 1][j - 1] == disc[turn] )&&( grid[i - 2][j - 2] == disc[turn] )&&( grid[i - 3][j - 3] == disc[turn])){
				score += 1;
			}
		}
	}
	if(turn == 0){
		player1.score = score;
	}else{
		player2.score = score;
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
void print_grid()
{
    int i ,j;

    //system("color a");                     //TO COLOR THE BOARD
    for ( i = 0; i < ROWS; i++)
    {
        for ( j = 0; j < COLS; j++)
        {
            printf("+---");
        }
        printf("+\n");
        for ( j = 0; j < COLS; j++)
        {
            if((grid[i][j] != disc[0] )&&( grid[i][j] != disc[1]  )){
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

void move(){
	int static turn=0;
    
	int lastr[COLS],col,counter;
    memset(lastr, 0 ,sizeof lastr);
    int n=ROWS*COLS;

    while(n!=0){
        printf("Player %d your turn:", turn +1);
		scanf("%d",&col);
        while(col>COLS){               //checking limits
            printf("INVALID INPUT\n");
            scanf("%d",&col);
        }

        grid[last_row(col,lastr)][col-1]=disc[turn];
        print_grid();

		moves(turn);

           //taking turns
        n--;
       	turn=1-turn; 
	    printf("P1 score : %d  P2 score: %d\n",player1.score,player2.score);
        printf("P1 moves : %d  P2 moves: %d\n",player1.moves,player2.moves);
    }
}
// moves count moves of each player
void moves(int turn){
	 if(disc[turn]==disc[0]){     //count moves
            player1.moves++;
            if(player1.moves % 4 == 0){
            	score();
			}
        }
        if(disc[turn]== disc[1]){
            player2.moves++;
             if(player2.moves % 4 == 0){
            	score();
			}
        }	
}

int main() {
	player1.score = 0;
	player2.score =0;
	print_grid();
	move();
	return 0;
}
