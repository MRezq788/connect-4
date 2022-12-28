#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#define ROWS 6
#define COLS 7
int turn=0;
char disc[] = "XO ";
char grid[ROWS][COLS];
int savecol[COLS * ROWS] = {0};
int saverow[COLS * ROWS] =  {0};
int lastrow[COLS] = {0};
int top = -1;
int load_indic=0;

typedef struct{
	int moves;
	char disc;
	int score;
	char name[40];
}player;
typedef struct{
    long sec;
    long min;
    long hour;
    long total;
}ttime;

player player1, player2;
ttime timer;
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
//check grid full or not
int isfull(){
	int j, counter = 0;
	for(j = 0; j < COLS; j++ ){
		if(grid[0][j] != '\0'){
		counter++;
		}
	}
	if(counter == COLS){
		return 0;
	}else{
		return 1;

	}

}


void undo(){
		grid[ saverow[ top ] ][ savecol[ top ] - 1 ] = '\0';
		lastrow[ savecol[top] - 1 ] = lastrow[ savecol[top] - 1] + 1;
		top--;
		turn = 1 - turn;
		score();
}

void redo(){
		top++;
		if(top %2 == 0){
			grid[ saverow[top] ][ savecol[ top ] - 1] = disc[0];
		}else{
			grid[ saverow[top] ][ savecol[ top ] - 1] = disc[1];
		}
	    lastrow[ savecol[top] - 1 ] = lastrow[ savecol[top] - 1] - 1;
		turn = 1 - turn;
		score();
}

// print ellapsed time after each move
 void timee(){
    long time_now=time(NULL);
    long time_passed = time_now - timer.total;
    timer.sec = time_passed % 60;
    timer.min = time_passed / 60;
    printf("\033[0;33m");
    if(timer.sec<10&&timer.min<10){
      printf("\nTimer 0%ld:0%ld\n",timer.min,timer.sec);
    }
    else if(timer.sec>10&&timer.min<10){
      printf("\nTimer 0%ld:%ld\n",timer.min,timer.sec);
    }
    else if(timer.sec<10&&timer.min>10){
      printf("\nTimer %ld:0%ld\n",timer.min,timer.sec);
    }
    else{
      printf("\nTimer %ld:%ld\n",timer.min,timer.sec);
    }
}

//last_row function >> returns index of last empty row in specific columns
int last_row(int col){
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
    system ("cls");   //clear terminal
    timee();
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
        printf("[-1]Undo [-2]Redo [-3]Exit [-4]Save \n\n");
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
void fill_grid(int col){
    grid[last_row(col)][col-1] = disc[turn];
	top++;
	savecol[ top ] = col;
	saverow[ top ] = lastrow[ col - 1];
	savecol[ top + 1 ] = 0;
	saverow[ top + 1] = 0;
	moves(turn) ;
	}

void steering(){
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
			if(top > - 1 || savecol[top] > 0){
				undo();
				break;
			}else{
				printf("\033[0;31m");
				printf("NO LAST MOVE, CAN'T USE UNDO, PLEASE ENTER ANOTHER INPUT:\n");
	 			scanf("%d", &wheel);
			}
		}else if(wheel == -2 ){        //82  R   114  r
			if(savecol[top + 1] != 0 ){
				redo();
				break;
			}else{
				printf("\033[0;31m");
				printf("NO LAST MOVE TO REDO, PLEASE ENTER ANOTHER INPUT:\n");
	 			scanf("%d", &wheel);
			}
		}

    else if(wheel == -3 ){
		  printf("\n Are you sure you wanna exit?\n");
		  printf("[1]yes [2] NO\n");
          int exit;
          scanf("%d",&exit);
          if(exit==1){
              system("cls");
              start_menu();
          }
          else if (exit==2){
            break;
          }
          else{
             printf("\033[0;31m");
			 printf("PLEASE ENTER A VALID INPUT :\n");
          }
	}else if(wheel == -4 ){        //83  S    115  s
			save();
			break;
	//	}else
	}
    else if( wheel > 0 && wheel <= COLS){
				if(grid[0][wheel - 1] == '\0'){
					fill_grid(wheel);
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
  }
}
void game_loop(){
   if(load_indic==0){
    timer.total=time(NULL);
   	while( isfull() ){
		print_grid();
		steering();
    }
   }
   else{
    	while( isfull() ){
		print_grid();
		steering();
        }
   }
}
void start_menu(){
    int select;
    int mode;
    printf("\033[0;31m");
    printf("\nWELCOME TO CONNECT FOUR\n");
    printf("**************************\n");
    printf("\033[0;34m");
    printf("1: Start a new game\n");
    printf("2: Load a game\n");
    printf("3: Top players\n");
    printf("4: Quit\n");
    scanf("%d",&select);
    switch(select){
        case 1 : system("cls");
                 printf("\033[1;31m");
                 printf("Choose game mode\n");
                 printf("*******************\n");
                 printf("\033[1;34m");
                 printf("1 :Human VS Human\n");
                 printf("2 :Human VS Computer\n");
                 scanf("%d",&mode);
                 if(mode==1){
                    game_loop();
                 }
                 break;
        case 2:load_indic=1;
               load();
               break;

                /* else{

                 }*/
        case 4: exit(1);

    }
}

void saving_process(FILE *file){
    int i,j;
    fprintf(file,"%d",player1.score);fprintf(file,"\n");
    fprintf(file,"%d",player2.score);fprintf(file,"\n");
    fprintf(file,"%d",player1.moves);fprintf(file,"\n");
    fprintf(file,"%d",player2.moves);fprintf(file,"\n");
    fprintf(file,"%d",timer.total);fprintf(file,"\n");
    fprintf(file,"%d",turn);fprintf(file,"\n");

    for(int i=0;i<ROWS;i++){
        for(j=0;j<COLS;j++){
            fprintf(file,"%c",grid[i][j]);
             fprintf(file,"\n");
        }
    }
    for(int ii=0;ii<COLS;ii++){
           fprintf(file,"%d",lastrow[ii]);
           fprintf(file,"\n");
    }
    fclose(file);
}
void save(){
    int fileNumber;
    printf("\nwhere do you wanna save this game?\n");
    printf("[1]file 1 \n[2]file 2\n[3]file 3  ");
    scanf("%d",&fileNumber);
     if(fileNumber==1){
            FILE *file1;
            file1=fopen("file1.bin","wb");
            saving_process(file1);
    }
    else if(fileNumber==2){
            FILE *file2;
            file2=fopen("file2.bin","wb");
            saving_process(file2);
    }
    else if(fileNumber==3){
            FILE *file3;
            file3=fopen("file3.bin","wb");
            saving_process(file3);
    }

}

void load_process(FILE *file){
        fscanf(file,"%d",&player1.score);fscanf(file,"\n");
        fscanf(file,"%d",&player2.score);fscanf(file,"\n");
        fscanf(file,"%d",&player1.moves);fscanf(file,"\n");
        fscanf(file,"%d",&player2.moves);fscanf(file,"\n");
        fscanf(file,"%d",&timer.total);fscanf(file,"\n");
        fscanf(file,"%d",&turn);fscanf(file,"\n");
        int i,j;
        for(i=0;i<ROWS;i++){
            for(j=0;j<COLS;j++){
                fscanf(file,"%c",&grid[i][j]);
                fscanf(file,"\n");
            }
        }
         for(int ii=0;ii<COLS;ii++){
           fscanf(file,"%d",&lastrow[ii]);
           fscanf(file,"\n");
    }
    fclose(file);
    game_loop();
}
void load(){
    int fileNumber;
    int select;
    printf("\nwhich game you wanna load?\n");
    printf("[1]file 1\n[2]file 2\n[3]file 3\n");
    scanf("%d",&fileNumber);
            if(fileNumber==1){
                FILE *file1p;
                file1p=fopen("file1.bin","rb");
                if(file1p==NULL){
                    printf("the file is empty\n 1: main menu \n 2:select another file");
                    scanf("%d",&select);

                    if(select==1){
                      start_menu();
                    }
                    else if (select==2){
                        load();
                    }
                }
                else{
                    load_process(file1p);
                    fclose(file1p);
                }
        }
        else if(fileNumber==2){
                FILE *file2p;
                file2p=fopen("file2.bin","rb");
                if(file2p==NULL){
                    printf("the file is empty\n 1: main menu \n 2:select another file");
                    scanf("%d",&select);

                    if(select==1){
                      start_menu();
                    }
                    else if (select==2)
                        load();
                    }
                else{
                    load_process(file2p);
                }
        }
        else if(fileNumber==3){
                FILE *file3p;
                file3p=fopen("file3.bin","rb");

                if(file3p==NULL){
                    printf("the file is empty\n 1: main menu \n 2:select another file");
                    scanf("%d",&select);

                    if(select==1){
                     start_menu();
                    }
                    else if (select==2){
                        load();
                    }
                }
                else{
                    load_process(file3p);
                    fclose(file3p);
                }
     }
}
void check_winner()
{
    if (player1.score>player2.score){
        printf("player 1 is the winner?\n");
        printf("player 1 name:\n");
        scanf("%s",player1.name);
    }
     else if (player1.score>player2.score){
        printf("player 2 is the winner?\n");
        printf("player 2 name:\n");
        scanf("%s",player2.name);
    }
    else{
        printf("it's a draw");
    }
}

int main(){
	start_menu();
	check_winner();
    return 0;
}
