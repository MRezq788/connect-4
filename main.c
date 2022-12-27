#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#define ROWS 6
#define COLS 7
int turn=0;
char disc[] = "XO";
char grid[ROWS][COLS];
int savecol[COLS * ROWS] = {0};
int top = -1;

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
// add each move's col. to savecol[] to be recorded
void push(int col/*users col*/){
	top++;
	savecol[ top ] = col;
	savecol[ top + 1 ] = 0;
	
}


//check grid full or not 
int isfull(){
	int j;
	for(j = 0; j < COLS; j++ ){
		if(grid[0][j] != '\0'){
		return 0;
		}
	}
	return 1;
	
}


void undo(/*int col users col*/ int lastrow[COLS]){
    if(top != - 1 || savecol[top] != 0){	
		grid[ lastrow[ savecol[ top ] + 1 ] ][ savecol[ top ] - 1 ] = '\0';
		top--;
//		turn = 1 - turn;  
	}
	score();
}

void redo( int lastrow[COLS]){
	top++;
	if(savecol[top] != 0){
		grid[ lastrow[ savecol[ top ] - 1 ] + 1 ][ savecol[ top ] - 1] = disc[turn];
	}
	score();
}

// print ellapsed time after each move
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
void print_grid(long t){
    int i ,j;
    printf("\e[1;H\e[2J");    //clear terminal
    timee(t);
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
            score();
        }else if(disc[turn]== disc[1]){
            	player2.moves++;
        		score();	
        }	
}


// fill_grid 
void fill_grid(int col/*users col*/, int lastrow[COLS]){
    grid[last_row(col,lastrow)][col-1] = disc[turn];
	moves(turn); 
	}

void steering(int lastrow[COLS]){

	if(turn == 0){
		printf("\033[0;35m");
	}else{
		printf("\033[0;36m");
	}	
	printf("Player %d , your turn :\n", turn + 1);
	int wheel;
	scanf("%d", &wheel);
	while( wheel > -5){
	
	 
		if(wheel == -1){              // 85  U  117  u
			undo(lastrow);
		}else if(wheel == -2 ){        //82  R   114  r
			redo(lastrow);				
		}else if( wheel > 0 && wheel <= COLS){
				if(grid[0][wheel - 1] == '\0'){
					fill_grid(wheel, lastrow);
					push(wheel);
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

//else if(wheel == -3 ){         //69  E   101  e
	//		exit();
	//	}else if(wheel == -4 ){        //83  S    115  s
	//		save();
	//	}else
    //else if(wheel == -3 ){         //69  E   101  e
	//		exit();
	//	}else if(wheel == -4 ){        //83  S    115  s
	//		save();
	//	}else
	}
}

int main(){
	long start=time(NULL);
	int lastrow[COLS];
	memset(lastrow, 0 ,sizeof lastrow);
	
	while( isfull() ){
		print_grid(start);
		steering(lastrow);
    }
	
	return 0;
}
