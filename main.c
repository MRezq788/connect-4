#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <time.h>
#define BETWEEN(value ,min, max)(value < max && value > min)


char disc[] = "XO ";
int top = -1;
int load_indic=0;
int rows, cols, mode, turn = 0 ,high_scores;

void xml(){
	int  i =0, tags_indx[8];
	char k, xml_txt[256], path[280];
	char con[]="<configurations>", con1[]="</configurations>", h[]="<height>", h1[]="</height>";
	char w[]="<width>", w1[]="</width>", hs[]="<highscores>", hs1[]="</highscores>";
	system(" ");
	FILE *fp = fopen("config.xml", "r");
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
		rows = 6;
		cols = 7;
		high_scores = 8;
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
			rows = 6;
			cols = 7;
			high_scores = 8;
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
			rows = 6;
			cols = 7;
			high_scores = 8;
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
			rows = 6;
			cols = 7;
			high_scores = 8;
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
			rows = atoi(temp);

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
   		 	cols = atoi(temp);
			
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
			high_scores = atoi(temp);	
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
void score(char grid[rows][cols]){
	static turn = 0;
	int i, j;
	int score = 0;
	//check horizontal
	for(i = rows - 1; i >= 0; i--){
		for(j = 0; j < (cols - 3); j++){
			if((grid[i][j] == disc[turn] )&&( grid[i][j + 1] == disc[turn] )
				&&( grid[i][j + 2] == disc[turn] )&&( grid[i][j + 3] == disc[turn])){
				score += 1;
			}
		}
	}
	//check vertical
	for(i = rows - 1; i > 2; i--){
		for(j = 0 ; j < cols ; j++){
			if((grid[i][j] == disc[turn] )&&( grid[i - 1][j] == disc[turn] )
				&&( grid[i - 2][j] == disc[turn] )&&( grid[i - 3][j] == disc[turn])){
				score += 1;
			}
		}
	}
	//check diagonal
	//check bottom left to right
	for(i = rows - 1; i > 2; i--){
		for(j = 0; j < cols - 3; j++){
			if((grid[i][j] == disc[turn] )&&( grid[i - 1][j + 1] == disc[turn] )
				&&( grid[i - 2][j + 2] == disc[turn] )&&( grid[i - 3][j + 3] == disc[turn])){
				score += 1;
			}
		}
	}
	//check bottom right to left
	for(i = rows - 1; i >= 3; i--){
		for(j = cols - 1; j >=3 ; j--){
			if((grid[i][j] == disc[turn] )&&( grid[i - 1][j - 1] == disc[turn] )
				&&( grid[i - 2][j - 2] == disc[turn] )&&( grid[i - 3][j - 3] == disc[turn])){
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
int isfull(char grid[rows][cols]){
	int j, counter = 0;
	for(j = 0; j < cols; j++ ){
		if(grid[0][j] != '\0'){
		counter++;
		}
	}
	if(counter == cols){
		return 0;
	}else{
		return 1;
	}

}
void undo(char grid[rows][cols], int savecol[cols * rows], int saverow[cols * rows], int lastrow[cols]){
		grid[ saverow[ top ] ][ savecol[ top ] - 1 ] = '\0';
		lastrow[ savecol[top] - 1 ] = lastrow[ savecol[top] - 1] + 1;
		top--;
		score(grid);
}
void redo(char grid[rows][cols], int savecol[cols * rows], int saverow[cols * rows], int lastrow[cols]){
		top++;
		if(top %2 == 0){
			grid[ saverow[top] ][ savecol[ top ] - 1] = disc[0];
		}else{
			grid[ saverow[top] ][ savecol[ top ] - 1] = disc[1];
		}
	    lastrow[ savecol[top] - 1 ] = lastrow[ savecol[top] - 1] - 1;
		score(grid);
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
int last_row(int col, int lastrow[cols]){
	if(lastrow[col - 1] == 0){
		lastrow[col - 1 ] = rows - 1;
		return lastrow[col - 1];
	}else{
		lastrow[col - 1] = lastrow[col - 1] - 1;
		return lastrow[col - 1];
	}
}
//print_grid function
void print_grid(char grid[rows][cols]){
    int i ,j;
    system (" ");
	system ("cls");   //clear terminal
    timee();
    printf("\033[0;32m");                    //TO COLOR THE BOARD green
    for ( i = 0; i < rows; i++)
    {
        for ( j = 0; j < cols; j++)
        {
            printf("+---");
        }
        printf("+\n");
        for ( j = 0; j < cols; j++)
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
    for ( j = 0; j < cols; j++)
        {
            printf("+---");
        }
        printf("+\n");
        printf("[-1]Undo [-2]Redo [-3]Exit [-4]Save \n\n");
        printf("\033[0;37m");     // to color white
		if(mode == 1){
			printf("P1 score : %d  P2 score: %d\n",player1.score,player2.score);
        	printf("P1 moves : %d  P2 moves: %d\n\n",player1.moves,player2.moves);
		}else{
			printf("P1 score : %d  Computer score: %d\n",player1.score,player2.score);
        	printf("P1 moves : %d  Computer moves: %d\n\n",player1.moves,player2.moves);
		}
}
// moves count moves of each player
void moves(int turn, char grid[rows][cols]){
	 if(disc[turn]==disc[0]){     //count moves
            player1.moves++;
            score(grid);
        }else if(disc[turn]== disc[1]){
            	player2.moves++;
        		score(grid);
        }
}
// fill_grid
void fill_grid(int col,char grid[rows][cols], int savecol[cols * rows], int saverow[cols * rows], int lastrow[cols]){
    grid[last_row(col, lastrow)][col-1] = disc[turn];
	top++;
	savecol[ top ] = col;
	saverow[ top ] = lastrow[ col - 1];
	savecol[ top + 1 ] = 0;
	saverow[ top + 1] = 0;
	moves(turn, grid) ;
	}

void steering(char grid[rows][cols], int savecol[cols * rows], int saverow[cols * rows], int lastrow[cols]){
	int wheel;
	if(turn == 0){
		printf("\033[0;35m");
	}else{
		printf("\033[0;36m");
	}
	if((mode == 1) || (mode == 2 && turn == 0)){
		printf("Player %d , your turn :\n", turn + 1);
		scanf("%d", &wheel);
	}else{
		//computer will make a random move
		srand(time(0));
		wheel = (rand() % cols) + 1;
	}
	while( wheel > -5){
    	if(wheel == -1){  
			if(top > - 1 || savecol[top] > 0){
				undo(grid, savecol, saverow, lastrow );
				break;
			}else{
				printf("\033[0;31m");
				printf("NO LAST MOVE, CAN'T USE UNDO, PLEASE ENTER ANOTHER INPUT:\n");
	 			scanf("%d", &wheel);
			}
		}else if(wheel == -2 ){ 
			if(savecol[top + 1] != 0 ){
				redo(grid, savecol, saverow, lastrow );
				break;
			}else{
				printf("\033[0;31m");
				printf("NO LAST MOVE TO REDO, PLEASE ENTER ANOTHER INPUT:\n");
	 			scanf("%d", &wheel);
			}
		}else if(wheel == -3 ){
			printf("\n Are you sure you wanna exit?\n");
		  	printf("[1]yes [2] NO\n");
          	int exit;
          	scanf("%d",&exit);
          	if(exit==1){
            	system("cls");
            	start_menu();
        	}else if (exit==2){
            	break;
        	}else{
            	printf("\033[0;31m");
				printf("PLEASE ENTER A VALID INPUT :\n");
        }}else if(wheel == -4 ){   
			save();
			break;
		}else if( wheel > 0 && wheel <= cols){
				if(grid[0][wheel - 1] == '\0'){
					fill_grid(wheel, grid, savecol, saverow, lastrow);
					turn = 1 - turn;
					break;
				}else{
			 		if((mode == 1 )|| (mode == 2 && turn == 0)){
						printf("\033[0;31m");
			 			printf("THIS COLUMN IS FULL, PLEASE CHOOSE ANOTHER ONE:\n");
			 			scanf("%d", &wheel);	
					}else{
						//computer will make another random move
						srand(time(0));
						wheel = (rand() % cols) + 1;
					} 
				}
		}else{
			 printf("\033[0;31m");
			 printf("PLEASE ENTER A VALID INPUT :\n");
			 scanf("%d", &wheel);

		}
	}
}
void game_loop(char grid[rows][cols], int savecol[cols * rows], int saverow[cols * rows], int lastrow[cols]){
   if(load_indic==0){
    	timer.total=time(NULL);
   		while( isfull(grid) ){
		print_grid(grid);
		steering(grid, savecol, saverow, lastrow );
    	}
   }else{
    	while( isfull(grid) ){
		print_grid(grid);
		steering(grid, savecol, saverow, lastrow );
        }
   }
}
void start_menu(char grid[rows][cols], int savecol[cols * rows], int saverow[cols * rows], int lastrow[cols]){
    int select;
    system(" ");
    sleep(3);
    system("cls");
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
                 game_loop(grid, savecol, saverow, lastrow );
                 
                 break;
        case 2:load_indic=1;
               load(grid, savecol, saverow, lastrow );
               break;

                /* else{

                 }*/
        case 4: exit(1);

    }
}
void saving_process(FILE *file,char grid[rows][cols], int savecol[cols * rows], int saverow[cols * rows], int lastrow[cols]){
    int ii, i, j;
    fprintf(file,"%d",player1.score);fprintf(file,"\n");
    fprintf(file,"%d",player2.score);fprintf(file,"\n");
    fprintf(file,"%d",player1.moves);fprintf(file,"\n");
    fprintf(file,"%d",player2.moves);fprintf(file,"\n");
    fprintf(file,"%d",timer.total);fprintf(file,"\n");
    fprintf(file,"%d",turn);fprintf(file,"\n");
    
    for( i=0;i<rows;i++){
        for(j=0;j<cols;j++){
            fprintf(file,"%c",grid[i][j]);
             fprintf(file,"\n");
        }
    }
    for(ii=0;ii<cols;ii++){
           fprintf(file,"%d",lastrow[ii]);
           fprintf(file,"\n");
    }
    fclose(file);
}
void save(char grid[rows][cols], int savecol[cols * rows], int saverow[cols * rows], int lastrow[cols]){
    int fileNumber;
    printf("\nwhere do you wanna save this game?\n");
    printf("[1]file 1 \n[2]file 2\n[3]file 3  ");
    scanf("%d",&fileNumber);
     if(fileNumber==1){
            FILE *file1;
            file1=fopen("file1.bin","wb");
            saving_process(file1, grid, savecol, saverow, lastrow);
    }
    else if(fileNumber==2){
            FILE *file2;
            file2=fopen("file2.bin","wb");
            saving_process(file2, grid,savecol, saverow, lastrow);
    }
    else if(fileNumber==3){
            FILE *file3;
            file3=fopen("file3.bin","wb");
            saving_process(file3,grid,savecol, saverow, lastrow);
    }

}
void load_process(FILE *file,char grid[rows][cols], int savecol[cols * rows], int saverow[cols * rows], int lastrow[cols]){
        fscanf(file,"%d",&player1.score);fscanf(file,"\n");
        fscanf(file,"%d",&player2.score);fscanf(file,"\n");
        fscanf(file,"%d",&player1.moves);fscanf(file,"\n");
        fscanf(file,"%d",&player2.moves);fscanf(file,"\n");
        fscanf(file,"%d",&timer.total);fscanf(file,"\n");
        fscanf(file,"%d",&turn);fscanf(file,"\n");
        int ii, i, j;
        for(i=0;i<rows;i++){
            for(j=0;j<cols;j++){
                fscanf(file,"%c",&grid[i][j]);
                fscanf(file,"\n");
            }
        }
         for(ii=0;ii<cols;ii++){
           fscanf(file,"%d",&lastrow[ii]);
           fscanf(file,"\n");
    }
    fclose(file);
    game_loop( grid, savecol, saverow, lastrow);
}
void load(char grid[rows][cols], int savecol[cols * rows], int saverow[cols * rows], int lastrow[cols]){
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
                      start_menu( grid, savecol, saverow, lastrow);
                    }
                    else if (select==2){
                        load( grid, savecol, saverow, lastrow);
                    }
                }
                else{
                    load_process(file1p, grid, savecol, saverow, lastrow);
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
                      start_menu( grid, savecol, saverow, lastrow);
                    }
                    else if (select==2)
                        load( grid, savecol, saverow, lastrow);
                    }
                else{
                    load_process(file2p,grid, savecol, saverow, lastrow);
                }
        }
        else if(fileNumber==3){
                FILE *file3p;
                file3p=fopen("file3.bin","rb");

                if(file3p==NULL){
                    printf("the file is empty\n 1: main menu \n 2:select another file");
                    scanf("%d",&select);

                    if(select==1){
                     start_menu( grid, savecol, saverow, lastrow);
                    }
                    else if (select==2){
                        load( grid, savecol, saverow, lastrow);
                    }
                }
                else{
                    load_process(file3p,grid, savecol, saverow, lastrow);
                    fclose(file3p);
                }
     }
}
void check_winner(){
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
	char grid[rows][cols];
	int savecol[cols * rows];
	memset(savecol, 0, sizeof(savecol));
	int saverow[cols * rows];
	memset(saverow, 0, sizeof(saverow));
	int lastrow[cols];
	memset(lastrow, 0, sizeof(lastrow));
	xml();
	start_menu( grid, savecol, saverow, lastrow);
	check_winner();
    return 0;
}
