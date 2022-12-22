#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
void print_grid(unsigned long long int row, unsigned long long int col, char grid[row][col] ){
	
	unsigned long long int i ,j ,k, n;

	char row_border[] = "+---", col_border[]="|  ",white_space[] = " ", modifiy[]=" -",alpha[]="XO";
	
	//int lenrow = strlen(row_borde vr);
	
	n = log10(col) + 1;
	
	// modifying the borders if needed 
	
	if(n > 1){
	
		for(i = 0 ; i < n - 1; i++){
	
			row_border[4 + i] = modifiy[1] ;
	
			white_space[ 1 + i] = modifiy[0];
	
		}
	
		row_border[4 + i] = modifiy[2];
	
		white_space[ 1 + i] = modifiy[2];
	
	}
	
	// printing the columns index
	
	for(i = 1; i <= col; i++){
		
		printf("  %llu",i);
		
		for(j = 0; j < (n - log10(i) ); j ++){
		
			printf("%c", white_space[0]);
		
		}
		
	}
	
	printf("\n");
	
	// print th grid
	
	for(i=0; i < row; i++){
	
		for(j=0; j < col; j++){
	
			printf("%s", row_border);
	
		}
	
		printf("+\n");
	
		for(k = 0; k < col; k++){
	
			if(grid[row][k] == alpha[0] || grid[row][k] == alpha[1]){
	
				printf("| %c%s", grid[row][k], white_space);
	
			}else{
	
				printf("%s%s", col_border, white_space);
	
			}
	
		}
	
		printf("|\n");
	
	}
	
	// print bottom border
	
	for(j=0; j < col; j++){
	
			printf("%s", row_border);
	
		}printf("+\n");

}



void input(int col, in
int main(){

	unsigned long long int row,col;

	scanf("%llu%llu", &row ,&col);

	char grid[row][col];

		print_grid(row,col,grid);	

	
	return 0;
}
