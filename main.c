#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#define DIM 8000
#define BETWEEN(value, min, max)(value < max && value > min)
int mode;
int turn=0;
char disc[] = "XO ";
char grid[DIM][DIM];
int savecol[DIM * DIM] = {0};
int saverow[DIM * DIM] =  {0};
int lastrow[DIM] = {0};
int top = -1;
int high_scores[100]={0};
int COLS,ROWS , high_score;
char names[100][40];
 int counter=0;
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


void xml(){
		int  i =0, tags_indx[8];
	char k, xml_txt[256], path[280];
	char con[]="<configurations>", con1[]="</configurations>", h[]="<height>", h1[]="</height>";
	char w[]="<width>", w1[]="</width>", hs[]="<highscores>", hs1[]="</highscores>";
	system(" ");
	FILE *fp = fopen("cc.xml", "r");
	while( (fp == NULL) && (i < 3)){
		printf("\033[0;31m");
		printf("ERROR CONFIGURATION FILE CANNOT BE FOUND!\nmake sure to put every \\ in the path into \\\\\nPLEASE ENTER THE FILE PATH:\n");
		gets(path);
		fp = fopen(path, "r");
		i++;
	}
	if(fp == NULL){
		printf("\033[0;31m");
		printf("COULDN'T BE ABLE TO FIND THE CONFIGURATION FILE.\nDEFUALT CONFIGURATIONS WILL BE APPLIED.");
		ROWS = 9;
			COLS = 7;
			high_score = 10;
	}else{
		while((k = fgetc(fp))!=EOF){
        	if(isspace(k) == 0 ){           //IGNORING ANxml_txt SPACES OR TABS OR BREAKING LINE
           		xml_txt[i] = k;
          	    i++;
        	}
    	}
    		xml_txt[i] = '\0';
			i = 0;
//check for occuerence and recording first index
   			if(strstr(xml_txt, con)){
	   			tags_indx[i] = (strstr(xml_txt, con) - xml_txt) ;
   				i++;
        		if(strstr(xml_txt, con1)){
	   				tags_indx[i] = (strstr(xml_txt, con1) - xml_txt) ;
	   				i++;
	   				if(strstr(xml_txt, h)){
   						tags_indx[i] = (strstr(xml_txt, h) - xml_txt) ;
   						i++;
   		 				if(strstr(xml_txt, h1)){
   							tags_indx[i] = (strstr(xml_txt, h1) - xml_txt) ;
   							i++;
	      					if(strstr(xml_txt, w)){
   								tags_indx[i] = (strstr(xml_txt, w) - xml_txt) ;
   								i++;
   								if(strstr(xml_txt, w1)){
									tags_indx[i] = (strstr(xml_txt, w1) - xml_txt) ;
									i++;
      								if(strstr(xml_txt, hs)){
   										tags_indx[i] = (strstr(xml_txt, hs) - xml_txt) ;
   										i++;
	   									if(strstr(xml_txt, hs1)){
   											tags_indx[i] = (strstr(xml_txt, hs1) - xml_txt) ;
   											i++;
   										}
   									}
 								}
							}
						}
					}
				}
			}
		if(i != 8){
			printf("\033[0;31m");
			printf("NOT ALL TAGS ARE IN THE FILE.\nDEFUALT CONFIGURATIONS WILL BE APPLIED.");
			ROWS = 9;
			COLS = 7;
			high_score = 10;
			i = 0;
		}else{
			// check if tags are repeated
			i = 0;
			if( ( strstr( (strstr(xml_txt, con) + 1), con ) ) == NULL ){
				i++;
				if( ( strstr( (strstr(xml_txt, con1) + 1), con1 ) ) == NULL ){
					i++;
					if( ( strstr( (strstr(xml_txt, h) + 1), h ) ) == NULL ){
						i++;
						if( ( strstr( (strstr(xml_txt, h1) + 1), h1 ) ) == NULL ){
							i++;
							if( ( strstr( (strstr(xml_txt, w) + 1), w ) ) == NULL ){
								i++;
								if( ( strstr( (strstr(xml_txt, w1) + 1), w1 ) ) == NULL ){
									i++;
									if( ( strstr( (strstr(xml_txt, hs) + 1), hs ) ) == NULL ){
										i++;
										if( ( strstr( (strstr(xml_txt, hs1) + 1), hs1 ) ) == NULL ){
											i++;
										}
									}
								}
							}
						}
					}
				}
			}
		}
		if(i != 8 && i != 0){
			printf("\033[0;31m");
			printf("SOME TAGS ARE  REPEATED IN THE FILE.\nDEFUALT CONFIGURATIONS WILL BE APPLIED.");
			ROWS = 9;
			COLS = 7;
			high_score = 10;
			i = 0;
			//ddefualts
		}else{
			// check if the order is acceptaple
    		i = 0;
			// check if <configurations> comes before </configuration>
			if( tags_indx[0] < tags_indx[1] ){
				//check if  all tags are between <configurations> and </configuration>
				if( ( BETWEEN(tags_indx[2], tags_indx[0] , tags_indx[1]) ) && ( BETWEEN(tags_indx[3], tags_indx[0] , tags_indx[1]) ) && ( BETWEEN(tags_indx[4], tags_indx[0] , tags_indx[1]) )
					&& ( BETWEEN(tags_indx[5], tags_indx[0] , tags_indx[1]) ) && ( BETWEEN(tags_indx[6], tags_indx[0] , tags_indx[1]) ) && ( BETWEEN(tags_indx[7], tags_indx[0] , tags_indx[1]) ) ){
						i++;
						// check if <height> comes before </height>
						if( tags_indx[2] < tags_indx[3] ){
							// check if all tags are not between <height> and </height>
							if( ( !BETWEEN(tags_indx[4], tags_indx[2] , tags_indx[3]) ) && ( !BETWEEN(tags_indx[5], tags_indx[2] , tags_indx[3]) )
							   	&& ( !BETWEEN(tags_indx[6], tags_indx[2] , tags_indx[3]) ) && ( !BETWEEN(tags_indx[7], tags_indx[2] , tags_indx[3]) ) ){
							   		   i++;
									// check if <width> comes before </width>
							   		if( tags_indx[4] < tags_indx[5] ){
								   		// check if all tags are not between <width> and </width>
						   				if( ( !BETWEEN(tags_indx[2], tags_indx[4] , tags_indx[5]) ) && ( !BETWEEN(tags_indx[3], tags_indx[4] , tags_indx[5]) )
						        	   		&& ( !BETWEEN(tags_indx[6], tags_indx[4] , tags_indx[5]) ) && ( !BETWEEN(tags_indx[7], tags_indx[4] , tags_indx[5]) ) ){
						           				i++;
												//check if <highscores> comes before </highscores>
												if( tags_indx[6] < tags_indx[7]){
													// check if all tags are not between <highscores> and </highscores>
													if( ( !BETWEEN(tags_indx[2], tags_indx[6] , tags_indx[7]) ) && ( !BETWEEN(tags_indx[3], tags_indx[6] , tags_indx[7]) )
						           						&& ( !BETWEEN(tags_indx[4], tags_indx[6] , tags_indx[7]) ) && ( !BETWEEN(tags_indx[5], tags_indx[6] , tags_indx[7]) ) ){
															i++;
													}
												}
									   	}
								   }
							}
						}
				}
			}
		}
		if( i != 4 && i != 0 ){
			printf("\033[0;31m");
			printf("THE TAGS ORDER IS INVALID.\nDEFUALT CONFIGURATIONS WILL BE APPLIED.");
			//defaults
			ROWS = 9;
			COLS = 7;
			high_score = 10;
		}else{
			//extracting numbers
			//extraxt height
			int size = ( strstr(xml_txt, h1) ) - ( strstr(xml_txt, h) + 8);
			char temp[size + 1];
			int j = 0;
			for(i = ( tags_indx[2] + 8 ) ; i < tags_indx[3] ; i++ ){
				if( isdigit( (xml_txt[i]) ) ){
					temp[j] = xml_txt[i];
					j++;
				}
			}
			temp[j] = '\0';
			ROWS= atoi(temp);

			// extract width
			size = ( strstr(xml_txt, w1) ) - ( strstr(xml_txt, w) + 7);
			temp[size + 1];
			j = 0;
			for(i = ( tags_indx[4] + 7 ) ; i < tags_indx[5] ; i++ ){
				if( isdigit( (xml_txt[i]) ) ){
					temp[j] = xml_txt[i];
					j++;
				}
			}
			temp[j] = '\0';
   		 	COLS = atoi(temp);

			// extract highscores
			size = ( strstr(xml_txt, hs1) ) - ( strstr(xml_txt, hs) + 12);
			temp[size + 1];
			j = 0;
			for(i = ( tags_indx[6] + 12 ) ; i < tags_indx[7] ; i++ ){
				if( isdigit( (xml_txt[i]) ) ){
					temp[j] = xml_txt[i];
					j++;
				}
			}
			temp[j] = '\0';
			high_score = atoi(temp);
			}
		}

   fclose(fp);
	//extracting numbers
/*int extract_num(char xml_txt[], char s_tag[], char e_tag[]){
	int size = ( strstr(xml_txt, e_tag) ) - ( (strstr(xml_txt, s_tag)) + (strlen(s_tag)));
	char temp[size + 1];
	int j = 0, i;
	for(i = ( (strstr(xml_txt, s_tag)) + (strlen(s_tag)) ) ; i < (strstr(xml_txt, e_tag)); i++ ){
		if( isdigit( (xml_txt[i]) ) ){
			temp[j] = xml_txt[i];
			j++;
		}
	}
	temp[j+1] = '\0';

	return atoi(temp);
}*/
}

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
	//	if(mode == 1){
	//		turn = 1 - turn;
	//	}
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
    system (" ");
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
		if(mode == 1){
            printf("\033[0;35m");
			printf("P1 score: %d  P1 moves: %d\n",player1.score,player1.moves);
			printf("\033[0;36m");
        	printf("P2 score: %d  P2 moves: %d\n\n",player2.score,player2.moves);
		}else{
		    printf("\033[0;35m");
			printf("P1 score: %d  p1 moves: %d\n",player1.score,player1.moves);
            printf("\033[0;36m");
        	printf("computer score: %d  Computer moves: %d\n\n",player2.score,player2.moves);
		}
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
	int wheel;
	char x[10];
	if(turn == 0){
		printf("\033[0;35m");
	}else{
		printf("\033[0;36m");
	}
	if((mode == 1) || (mode == 2 && turn == 0)){
		printf("Player %d , your turn :\n", turn + 1);
		gets(x);
		wheel = atoi(x);
	}else{
		//computer will make a random move
		srand(time(0));
		wheel = (rand() % COLS) + 1;
	}
	while( wheel > -5){
    	if(wheel == -1){
			if(top > - 1 || savecol[top] > 0){
				undo();
				break;
			}else{
				printf("\033[0;31m");
				printf("NO LAST MOVE, CAN'T USE UNDO, PLEASE ENTER ANOTHER INPUT:\n");
	 			gets(x);
                wheel = atoi(x);
			}
		}else if(wheel == -2 ){
			if(savecol[top + 1] != 0 ){
				redo();
				break;
			}else{
				printf("\033[0;31m");
				printf("NO LAST MOVE TO REDO, PLEASE ENTER ANOTHER INPUT:\n");
	 			gets(x);
                wheel = atoi(x);
			}
		}else if(wheel == -3 ){
			printf("\nAre you sure you wanna exit?\n");
		  	printf("[1]yes [2] NO\n");
          	int exit;
          	gets(x);
            exit = atoi(x);
          	if(exit==1){
            	system("cls");
            	reset();
            	start_menu();
            	break;
        	}else if (exit==2){
            	break;
        	}else{
            	printf("\033[0;31m");
				printf("PLEASE ENTER A VALID INPUT :\n");
        }}else if(wheel == -4 ){
			save();
			break;
		}else if( wheel > 0 && wheel <= COLS){
				if(grid[0][wheel - 1] == '\0'){
					fill_grid(wheel);
					turn = 1 - turn;
					break;
				}else{
			 		if((mode == 1 )|| (mode == 2 && turn == 0)){
						printf("\033[0;31m");
			 			printf("THIS COLUMN IS FULL, PLEASE CHOOSE ANOTHER ONE:\n");
			 			gets(x);
                        wheel = atoi(x);
					}else{
						//computer will make another random move
						srand(time(0));
						wheel = (rand() % COLS) + 1;
					}
				}
		}else{
			 printf("\033[0;31m");
			 printf("PLEASE ENTER A VALID INPUT :\n");
			 gets(x);
             wheel = atoi(x);

		}
	}
}
void game_loop(){
    timer.total=time(NULL);
   	while( isfull() ){
		print_grid();
		steering();
   	}
}
void start_menu(){
    system("cls");
    reset();
    int select;
    char x[2];
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
                 gets(x);
                 mode = atoi(x);
                 while(mode >= 3 || mode <=0 ){
                    printf("PLEASE CHOOSE ONE OF THE OPTIONS\n");
                    gets(x);
                 mode = atoi(x);
                 }
                 game_loop();
                 break;
        case 2:load();

               break;

        case 3: printing_high_scores();
                int mm;
                printf("\nEnter [1] to go back yo main menu\n");
                scanf("%d",&mm);
                if(mm==1){
                  start_menu();
                  }
                else{
                  void printing_high_scores();
                }
                break;
        case 4: exit(0);
        default: start_menu();
                 break;

    }
}

void saving_process(FILE *file){
    int ii, i, j;
    fwrite(&player1.score,sizeof(player1.score),1,file);
    fwrite(&player2.score,sizeof(player2.score),1,file);
    fwrite(&player1.moves,sizeof(player1.moves),1,file);
    fwrite(&player2.moves,sizeof(player2.moves),1,file);
    fwrite(&turn,sizeof(turn),1,file);
    fwrite(&mode,sizeof(mode),1,file);
    for( i=0;i<ROWS;i++){
        for(j=0;j<COLS;j++){
            fwrite(&grid[i][j],sizeof(grid[i][j]),1,file);
        }
    }
    for(ii=0;ii<COLS;ii++){
           fwrite(&lastrow[ii],sizeof(lastrow[ii]),1,file);
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
     int ii, i, j;
    fread(&player1.score,sizeof(player1.score),1,file);
    fread(&player2.score,sizeof(player2.score),1,file);
    fread(&player1.moves,sizeof(player1.moves),1,file);
    fread(&player2.moves,sizeof(player2.moves),1,file);
    fread(&turn,sizeof(turn),1,file);
    fread(&mode,sizeof(mode),1,file);
    for( i=0;i<ROWS;i++){
        for(j=0;j<COLS;j++){
            fread(&grid[i][j],sizeof(grid[i][j]),1,file);
        }
    }
    for(ii=0;ii<COLS;ii++){
           fread(&lastrow[ii],sizeof(lastrow[ii]),1,file);
    }
    fclose(file);
    game_loop();
}
void load(){
    int fileNumber;
    char x[2];
    int select;
    printf("\nwhich game you wanna load?\n");
    printf("[1]file 1\n[2]file 2\n[3]file 3\n");
    scanf("%d",&fileNumber);
            if(fileNumber==1){
                FILE *file1p;
                file1p=fopen("file1.bin","rb");
                if(file1p==NULL){
                    printf("the file is empty\n 1: main menu \n 2:select another file");
                    gets(x);
                    select = atoi(x);

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
                    gets(x);
                    select = atoi(x);

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
                    gets(x);
                    select = atoi(x);

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
void reset(){

    for(int i=0;i<ROWS;i++){
        for(int j=0;j<COLS;j++){
            grid[i][j]='\0';
        }
    }
   for(int ii=0;ii<COLS;ii++){
       lastrow[ii]=0;
   }
   for(int jj=0;jj<COLS*ROWS;jj++){
       saverow[jj]=0;
       savecol[jj]=0;
   }
    turn=0;
    top = -1;
    player1.moves=0;
    player2.moves=0;
    player1.score=0;
    player2.score=0;

}
void check_winner(){
    if (player1.score>player2.score){
        printf("player 1 is the winner\n");
        printf("player 1 name:\n");
        scanf("%s",player1.name);
    }
     else if (player2.score>player1.score){
        printf("player 2 is the winner\n");
        printf("player 2 name:\n");
        scanf("%s",player2.name);
    }
    else{
        printf("it's a draw");
    }
}
void newScore(){
    int count=0;

    FILE*nameFile;
    FILE*scoreFile;

    scoreFile=fopen("scores.bin","ab");
    nameFile=fopen("players.bin","ab");

    if (player1.score>player2.score){
      for(int i=0;i<100;i++){
        if(strcasecmp(names[i],player1.name)==0){
            high_scores[i]=player1.score;
            strcpy(names[i],player1.name);
            count=1;
            break;
          }
        }
        if(count==0){
         fprintf(scoreFile,"%d",player1.score);
         fprintf(scoreFile,"\n");
         fprintf(nameFile,"%s",player1.name);
         fprintf(nameFile,"\n");
         }
    }
     else if (player2.score>player1.score){
        for(int i=0;i<100;i++){
           if(strcasecmp(names[i],player2.name)==0){
              high_scores[i]=player2.score;
              strcpy(names[i],player2.name);
              count=1;
              break;
             }
        }
        if(count==0){
         fprintf(scoreFile,"%d",player2.score);
         fprintf(scoreFile,"\n");
         fprintf(nameFile,"%s",player2.name);
         fprintf(nameFile,"\n");
         }

    }
    fclose(nameFile);
    fclose(scoreFile);
}


void sorting_scores(){

    char temp_name[40];
    FILE*scoreFile;
    FILE*nameFile;
    scoreFile=fopen("scores.bin","rb");
    nameFile=fopen("players.bin","rb");
    for (int i=0;i<100;i++){
      fscanf(scoreFile,"%d",&high_scores[i]);
      fscanf(scoreFile,"\n");
      fscanf(nameFile,"%s",names[i]);
      fscanf(nameFile,"\n");
      }
    for(int i=0;i<100;++i){
       for(int j=i+1;j<100;++j){
            if(high_scores[i]<high_scores[j]){
               int temp=high_scores[i];
               high_scores[i]=high_scores[j];
               high_scores[j]=temp;

                strcpy(temp_name,names[i]);
                strcpy(names[i],names[j]);
                strcpy(names[j],temp_name);
            }
       }
    }
    fclose(scoreFile);
    fclose(nameFile);
}
void printing_high_scores(){
    int mm;
    for(int i=0;i<high_score;i++){
        printf("[%d]%s     \tscore:%d",i+1,names[i],high_scores[i]);
        printf("\n");
    }

}
void sorting2()
{
    char temp_name[40];
    for(int i=0;i<100;++i){
       for(int j=i+1;j<100;++j){
            if(high_scores[i]<high_scores[j]){
               int temp=high_scores[i];
               high_scores[i]=high_scores[j];
               high_scores[j]=temp;

                strcpy(temp_name,names[i]);
                strcpy(names[i],names[j]);
                strcpy(names[j],temp_name);
            }
       }
    }
}
void modify_scores()
{   FILE*scoreFile;
    FILE*nameFile;
    scoreFile=fopen("scores.bin","wb");
    nameFile=fopen("players.bin","wb");
     for (int i=0;i<100;i++){
      fprintf(scoreFile,"%d",high_scores[i]);
      fprintf(scoreFile,"\n");
      fprintf(nameFile,"%s",names[i]);
      fprintf(nameFile,"\n");
      }
    fclose(scoreFile);
    fclose(nameFile);

}
void check_rank()
{
    if(player1.score>player2.score){
       for(int i=0;i<100;i++){
         if(high_scores[i]==player1.score){
           printf("\nyour rank is %d",i+1);
           break;
          }
        }
    }
    if(player2.score>player1.score){
        for(int j=0;j<100;j++){
         if(high_scores[j]==player1.score){
           printf("\nyour rank is %d",j+1);
           break;
          }
        }
    }
}

int main(){
    int cont;
    xml();
    start_menu();
    sorting_scores();

	check_winner();
    newScore();
    sorting_scores();

    check_rank();

    printf("\nDo you wanna go back to main menu?\n");
    printf("[1]main menu\n[2]quit");
    scanf("%d",&cont);
       if(cont==1){
           start_menu();
      }
       else if(cont ==2){
           exit(0);
      }


   // modify_scores();
    return 0;
}
