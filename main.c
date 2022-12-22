#include <stdio.h>
#include <stdlib.h>
#define ROWS 6
#define COLS 7
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void grid()
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

	grid();
	return 0;
}
