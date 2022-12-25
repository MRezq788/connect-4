#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define ROWS 6
#define COLS 7
int turn=0;
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
void print_grid(){
    int i ,j;
	printf("\e[1;H\e[2J");			          //clear terminal
    printf("\033[0;32m");                    //TO COLOR THE BOARD green
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
					printf("| ");
					
					if(grid[i][j] == disc[0] ){
						printf("\033[0;35m");
						printf("%c ", grid[i][j]);
					}else{
						printf("\033[0;36m");
						printf("%c ", grid[i][j]);
					}
					printf("\033[0;32m");                    //TO COLOR THE BOARD green
					
					
				}
			
        }
        printf("|\n");
    }
    for ( j = 0; j < COLS; j++)
        {
            printf("+---");
        }
        printf("+\n");
        printf("[u]Undo [r]Redo [e]Exit [s]Save \n\n");
        printf("\033[0;37m");     // to color white 
        printf("P1 score : %d  P2 score: %d\n",player1.score,player2.score);
        printf("P1 moves : %d  P2 moves: %d\n\n",player1.moves,player2.moves);
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


// fill_grid 
void fill_grid(int col/*users col*/, int lastrow[COLS]){
    grid[last_row(col,lastrow)][col-1] = disc[turn];
	moves(turn); 
	}

void steering(int lastrow[COLS],long start_time){

	if(turn == 0){
		printf("\033[0;35m");
	}else{
		printf("\033[0;36m");
	}
	
	
	printf("Player %d , your turn :\n", turn + 1);
	
	int wheel;
	scanf("%d", &wheel);
	time(start_time);
	while( wheel > -5){
	
	 
	//	if(wheel == -1){              // 85  U  117  u
	//		undo();
	//	}else if(wheel == -2 ){        //82  R   114  r
	//		redo();
	//	}else if(wheel == -3 ){         //69  E   101  e
	//		exit();
	//	}else if(wheel == -4 ){        //83  S    115  s
	//		save();
	//	}else
		 if( wheel > 0 && wheel <= COLS){
				if(grid[0][wheel - 1] == '\0'){
					fill_grid(wheel, lastrow);
					turn = 1 - turn; 
					break;
				}else{
			 		printf("\033[0;31m");
			 		printf("THIS COLUMN IS FULL, PLEASE CHOOSE ANOTHER ONE:\n");
			 		scanf("%d", &wheel);	
				}
		}else{
			 printf("\033[0;31m");
			 printf("PLEASE ENTER A VALID INPUT :\n");
			 scanf("%d", &wheel);
			
		}
		//else{
//			computer();
//		}
	}
}
 void timee(long t){
    long time_now=time(NULL);
    long time_passed = time_now - t;
    long sec = time_passed % 60;
    long min = time_passed / 60;
    printf("\033[0;33m");
    if(sec<10&&min<10){
      printf("\nTimer 0%ld:0%ld\n",min,sec);
    }
    else if(sec>10&&min<10){
      printf("\nTimer0%ld:%ld\n",min,sec);
    }
    else if(sec<10&&min>10){
      printf("\nTimer%ld:0%ld\n",min,sec);
    }
    else{
      printf("\nTimer%ld:%ld\n",min,sec);
    }
}

int main() {
	long start=time(NULL);
	int lastrow[COLS];
	memset(lastrow, 0 ,sizeof lastrow);
	int n = ROWS*COLS;
	while(n>0){
		print_grid();
		steering(lastrow,start);
		n--;
    }
	return 0;
}
