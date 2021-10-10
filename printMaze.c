#include <stdio.h>
#include "printMaze.h"
void printmaze(char** maze, int row, int col){
    int i,j;/*varialble for for loop*/
    for( i = 0; i < row; ++i){ /* iterative loop to porint every item of teh 2D char array*/
        for( j =0; j < col; ++j){
            printf("%c", maze[i][j]);
        }
        printf("\n");
    } 