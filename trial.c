#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include "terminal.h"
#include "trial.h"
char** fileIO(int* row, int*col, int player[2], int goal[2], int snake[2],  char* fileName){
    int amount, mapRow, mapCol, Nread;
    int i, j;
    char** actualMap;
    int x_coor, y_coor, type;
    FILE* input = fopen(fileName, "r");
    if(input == NULL){
        perror("Error opening 'file.txt'");
    }
    /* the error checking and openign of file is done */
    Nread = fscanf(input, "%d %d %d", &amount, &mapRow, &mapCol);
    if(Nread != 3){
        printf("Error reading the input");
    }
    /*reding of the file for metada started */
    *col = mapCol;
    *row = mapRow;
    actualMap = (char **)malloc(sizeof(char*)*mapRow);
    for(i = 0; i <mapRow;++i){
        actualMap[i] = (char*)malloc(sizeof(char)*mapCol);
        for(j =0; j < mapCol; ++j){
            actualMap[i][j]= ' ';
        }
    }
    actualMap[0][0] = '#';      
    actualMap[mapRow-1][0] = '#';
    actualMap[0][mapCol-1] = '#';
    actualMap[mapRow-1][mapCol-1] = '#';
    for (i = 1; i < (mapRow-1); ++i){
        actualMap[i][0]= '|';
        actualMap[i][mapCol -1] = '|';
    }               
    for(i=1; i< mapCol -1; ++i){
        actualMap[0][i] = '-';
        actualMap[mapRow-1][i] = '-';
    }
                      
    for(i=0; i<amount; ++i){
        Nread = fscanf(input, "%d %d %d", &x_coor, &y_coor, &type);
        if(Nread != 3){
            printf("Error reading the input, check input file format");
        }
        if (type == 0){
            actualMap[x_coor][y_coor] = '^';/* if type is 0 then its the player and inserting the ^ icon at the coodinates*/
            player[1] = y_coor;/*storing the plaer coordinates in the player array for while loop in the main*/
            player[0] = x_coor;
        }
        else if (type == 2){
            actualMap[x_coor][y_coor] = 'x';
            goal[0] = x_coor;/* if type is 1 then its the goal and inserting the ^ icon at the coodinates*/
            goal[1] = y_coor;/*storing the goal coordinates in the player array for while loop in the main*/
        }
        else if (type == 1){
            actualMap[x_coor][y_coor] = '~'; /* snake type*/
            snake[0] = x_coor; /* storing the snake coordinates for future use*/
            snake[1] = y_coor;
        }
        else
            actualMap[x_coor][y_coor] = 'o';/* same as above but with wall object*/
    }
    return actualMap;
}
void printMaze(char** maze, int row, int col){
    int i,j;/*varualble for for loop*/
    for( i = 0; i < row; ++i){
        for( j =0; j < col; ++j){
            printf("%c", maze[i][j]);
        }
        printf("\n");
    } 
}

void editLinkedList(Llist* movesList, char command, int*player , int*snake, int*goal, char** maze){
    int** array_coord = (int**)malloc(sizeof(int*)*4);
    int integer_command = (int)command;
    int* int_command = &integer_command;
    listNd* undoNode;
    if(command != 'u'){
        int next_snake[2];
        int next[2];/*2 int array to store coordinates of the next move*/
        if (command =='a'){             /*what to do if the command is 'a'*/
            next[0] = player[0];    /*determine where the coordinates of the player after the move*/
            next[1] = player[1]-1;
            next_snake[0] = snake[0];    /*determine where the coordinates of the player after the move*/
            next_snake[1] = snake[1]-1;
            if(maze[next[0]][next[1]] == ' ' || maze[next[0]][next[1]] == 'x'){
                player[0] = next[0];
                player[1]= next[1];
            }
        }
        else if (command == 'w'){/* repitition of the code above with a seperate command*/
            next[0] = player[0]-1;
            next[1] = player[1];
            if(maze[next[0]][next[1]] == ' ' || maze[next[0]][next[1]] == 'x'){
                player[0] = next[0];
                player[1]= next[1];
            }
        }
        else if (command == 's'){
            next[0] = player[0]+1;
            next[1] = player[1];
            if(maze[next[0]][next[1]] == ' ' || maze[next[0]][next[1]] == 'x'){
                player[0] = next[0];
                player[1]= next[1];
            }
        }
        else if (command == 'd'){
            next[0] = player[0];
            next[1] = player[1] +1;

            if(maze[next[0]][next[1]] == ' ' || maze[next[0]][next[1]] == 'x'){
                player[0] = next[0];
                player[1]= next[1];
            }
        }
        else if(command == ' '){
            player = player;
    
        }
        else
            printf("ERROR in the input");
        array_coord[0] = player;
        array_coord[1] = snake;
        array_coord[2]= goal;
        array_coord[3] = int_command;
        array_coord = (void*)(array_coord);
        insertStart(movesList, array_coord);
    }
    else{
        undoNode = removeStart(movesList);
    }
}
int main(int argc, char* argv[]){
    char* fileName;
    int* player;
    int* snake;
    int* goal;
    char command;
    int go = 1;
    int row, col;
    char ** maze;
    Llist* movesList;
    player =(int*)malloc(sizeof(int)*2);
    goal =(int*)malloc(sizeof(int)*2);
    snake =(int*)malloc(sizeof(int)*2);
    if(argc != 2){
        printf("PLEASE GIVE THE FILENAME FOR THE INPUT FILE");
    }
    else if(argc == 2){
        fileName = argv[1];
        maze = fileIO(&row, &col, player, goal ,snake,fileName);
        editLinkedList(movesList, ' ', player, snake, goal, maze);
        disableBuffer();
        system("clear");
    }
    printf("%d %d %d %d %d %d", player[0], player[1], snake[0], snake[1], goal[0], goal[1]);
    return 0;
}