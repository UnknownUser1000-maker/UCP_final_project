#include <stdlib.h>
#include <stdio.h>
#include "editSnake.h"
int* snakeAlgo(int player[2], int snake[2], char** maze){/* simple snake algorithm to follow the player*/
    int rowDiff = player[0] - snake[0]; /*find the difference between the rows of the snake and the player*/
    int colDiff = player[1]- snake[1];  /* find the difference between the columns of the snake and the player*/
    int absRow = abs(rowDiff); /* find abs of the differece*/
    int absCol = abs(colDiff);/* find abs of the differece*/ 
    int next_snake[2]; /* int[2] array for the next snake coordinates*/
    if (absRow > absCol){ /*if the difference in rows is greater than the difference in columns*/
        if(rowDiff< 0){ /* if the player is above the snake then move the snake one up*/
            next_snake[0] = snake[0]- 1;
            next_snake[1] = snake[1];
            if (maze[next_snake[0]][next_snake[1]]== ' ' || maze[next_snake[0]][next_snake[1]]== 'v' ||maze[next_snake[0]][next_snake[1]]== '>' || maze[next_snake[0]][next_snake[1]]== '<'||maze[next_snake[0]][next_snake[1]]== '^'){
                snake[0] = next_snake[0];/* this condition does the same as the player update it checks if the next_snake[2] coordinates are free to move to*/
                snake[1]= next_snake[1];/* if they are then it updates the snake coordinates*/

            }  
        }
        else if(rowDiff > 0){ /* if the player is below the snake is moved down*/
            next_snake[0] = snake[0] + 1;
            next_snake[1] = snake[1]; /* same code as above*/
            if (maze[next_snake[0]][next_snake[1]]== ' ' || maze[next_snake[0]][next_snake[1]]== 'v' ||maze[next_snake[0]][next_snake[1]]== '>' || maze[next_snake[0]][next_snake[1]]== '<'||maze[next_snake[0]][next_snake[1]]== '^'){
                snake[0] = next_snake[0];
                snake[1]= next_snake[1];
            }
        }
    }
    else{
        if(colDiff< 0){ /* the same condition as the ones above are repeated but now for the difference in columns is greater or equal to the differencce in rows*/
            next_snake[0] = snake[0];
            next_snake[1] = snake[1]-1;
            if (maze[next_snake[0]][next_snake[1]]== ' ' || maze[next_snake[0]][next_snake[1]]== 'v' ||maze[next_snake[0]][next_snake[1]]== '>' || maze[next_snake[0]][next_snake[1]]== '<'||maze[next_snake[0]][next_snake[1]]== '^'){
                snake[0] = next_snake[0];
                snake[1]= next_snake[1];

            }  
        }
        else if(colDiff > 0){
            next_snake[0] = snake[0];
            next_snake[1] = snake[1]+1;
            if (maze[next_snake[0]][next_snake[1]]== ' ' || maze[next_snake[0]][next_snake[1]]== 'v' ||maze[next_snake[0]][next_snake[1]]== '>' || maze[next_snake[0]][next_snake[1]]== '<'||maze[next_snake[0]][next_snake[1]]== '^'){
                snake[0] = next_snake[0];
                snake[1]= next_snake[1];
            }
        }
    }
    return snake;/*the new snake coordinates are reutrned*/
}