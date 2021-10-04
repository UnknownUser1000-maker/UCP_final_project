#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include "main.h"
#include "linkedlist.h"
#include "terminal.h"
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
void printmaze(char** maze, int row, int col){
    int i,j;/*varualble for for loop*/
    for( i = 0; i < row; ++i){
        for( j =0; j < col; ++j){
            printf("%c", maze[i][j]);
        }
        printf("\n");
    } 
}
int* edit_player(char command, int player[2], char** maze){
    int next[2];
    if(command == 'w'){
        next[0] = player[0] -1;
        next[1] = player[1];
        if (maze[next[0]][next[1]]== ' ' ||maze[next[0]][next[1]]== 'x'){
            player[0] = next[0];
            player[1]= next[1];
        }
    }
    else if(command == 'a'){
        next[0] = player[0];
        next[1] = player[1]-1;
        if (maze[next[0]][next[1]]== ' ' ||maze[next[0]][next[1]]== 'x'){
            player[0] = next[0];
            player[1]= next[1];
        }
        
    }
    else if(command == 's'){
        next[0] = player[0] +1;
        next[1] = player[1];
       if (maze[next[0]][next[1]]== ' ' ||maze[next[0]][next[1]]== 'x'){
            player[0] = next[0];
            player[1]= next[1];
        }
    }
    else if (command == 'd'){
        next[0] = player[0];
        next[1] = player[1]+1;
        if (maze[next[0]][next[1]]== ' ' ||maze[next[0]][next[1]]== 'x'){
            player[0] = next[0];
            player[1]= next[1];
        }
    }
    else{
        printf("\n Comman not recognised \n");
    }
    return player;
}
int* snakeAlgo(int player[2], int snake[2], char** maze){
    int rowDiff = player[0] - snake[0];
    int colDiff = player[1]- snake[1];
    int absRow = abs(rowDiff);
    int absCol = abs(colDiff);
    int next_snake[2];
    if (absRow > absCol){
        if(rowDiff< 0){
            next_snake[0] = snake[0]- 1;
            next_snake[1] = snake[1];
            if (maze[next_snake[0]][next_snake[1]]== ' ' || maze[next_snake[0]][next_snake[1]]== 'v' ||maze[next_snake[0]][next_snake[1]]== '>' || maze[next_snake[0]][next_snake[1]]== '<'||maze[next_snake[0]][next_snake[1]]== '^'){
                snake[0] = next_snake[0];
                snake[1]= next_snake[1];

            }  
        }
        else if(rowDiff > 0){
            next_snake[0] = snake[0] + 1;
            next_snake[1] = snake[1];
            if (maze[next_snake[0]][next_snake[1]]== ' ' || maze[next_snake[0]][next_snake[1]]== 'v' ||maze[next_snake[0]][next_snake[1]]== '>' || maze[next_snake[0]][next_snake[1]]== '<'||maze[next_snake[0]][next_snake[1]]== '^'){
                snake[0] = next_snake[0];
                snake[1]= next_snake[1];
            }
        }
    }
    else{
        if(colDiff< 0){
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
    return snake;
}

Llist* addMove(Llist* moves, int player[2], int snake[2], char command){
    int int_command = (int)command;
    int* array = (int*)malloc(sizeof(int)*5);
    array[0]= player[0];
    array[1]= player[1];
    array[2] = snake[0];
    array[3] = snake[1];
    array[4]= int_command;
    void* data = (void*)array;
    insertStart(moves, data);
    return moves;
}
char** editMaze(char** maze, Llist* moves, int row, int col, int player[2], int goal[2], int snake[2], char* fileName){
    int i,j;/*varualble for for loop*/
    for( i = 0; i < row; ++i){
            for( j =0; j < col; ++j){
                if (maze[i][j]== 'v' || maze[i][j]== '<' || maze[i][j]== '>' || maze[i][j]== '^' ||  maze[i][j]== '~'){
                    maze[i][j] = ' ';
                }
            }
    }
    if (moves->size == 0){
        maze = fileIO(&row, &col, player, goal, snake, fileName);
        return maze;
    }
    else if(moves->size == 1){
        listNd* newMove = moves->head;
    } 
    else{
        listNd* newMove = moves->head;
        listNd* old = newMove->next;
        int* old_data = (int*)old->data;
        maze[old_data[0]][old_data[1]] = ' ';
        maze[old_data[2]][old_data[3]]= ' ';
        }
    listNd* newMove = moves->head;  
    int* data = (int*)newMove->data;
    int player_x = data[0];
    int player_y = data[1];
    int snake_x = data[2];
    int snake_y = data[3];
    int type = data[4];
    maze[snake_x][snake_y] = '~';
    if(type == 97){
        maze[player_x][player_y] = '<';
    }
    else if (type ==119){
        maze[player_x][player_y] = '^';
    }
    else if(type == 100){
        maze[player_x][player_y]= '>';
    }
    else if(type == 115){
        maze[player_x][player_y] = 'v';
    }
    else{
        printf("\n FUCKEEEEEMEEEEE WRONG INPUT AGAIN CUNT: %d\n", type);
    }
    return maze;

}
Llist* undoList(char** maze, Llist* moves, int row, int col, int player[2], int goal[2], int snake[2], char* fileName){
    if(moves->size == 1){
        removeStart(moves);
        maze = fileIO(&row, &col, player, goal, snake, fileName);
    }
    else if(moves->size == 0){
        maze = fileIO(&row, &col, player, goal, snake, fileName);
    }
    else{
        removeStart(moves);
        listNd* newNode = moves->head;
        int* data = (int*)newNode->data;
        player[0] = data[0];
        player[1] = data[1];
        snake[0] = data[2];
        snake[1] = data[3];
    }
    return moves;
}


int main(int argc, char* argv[]){
    char* fileName;
    int* player;
    int* snake;
    int i;
    int* goal;
    char command;
    int go = 1;
    int row, col;
    char ** maze;
    Llist* movesList = createLlist();
    player =(int*)malloc(sizeof(int)*2);
    goal =(int*)malloc(sizeof(int)*2);
    snake =(int*)malloc(sizeof(int)*2);
    if(argc != 2){
        printf("PLEASE GIVE THE FILENAME FOR THE INPUT FILE");
    }
    else if(argc == 2){
        fileName = argv[1];
        maze = fileIO(&row, &col, player, goal ,snake,fileName); 
        system("clear");
        disableBuffer();
        while(go ==1){
            printmaze(maze, row, col);
            scanf(" %c", &command);
            if(command != 'u'){
                player = edit_player(command, player, maze);
                snake = snakeAlgo(player,snake, maze);
                movesList = addMove(movesList, player, snake, command);
                maze = editMaze(maze, movesList, row, col, player, goal, snake, fileName);
                system("clear");
            }
            else{
                movesList = undoList(maze, movesList, row, col, player, goal, snake, fileName);
                maze = editMaze(maze, movesList, row, col, player, goal, snake, fileName);
                system("clear");
            }

            if (player[0] == goal[0] && player[1] == goal[1]){
                go = 2; /*means you won*/
            }
            else if (snake[0] == player[0] && snake[1] == player[1]){
                go = 0; /* you lost*/
            }
        }
        enableBuffer();
        if(go == 2){
            printf("you WON");
        }
        else if (go == 0){
            printf("YOU LSOT");
        }

    }
    return 0;
}