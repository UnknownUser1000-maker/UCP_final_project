#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include "main.h"
#include "linkedlist.h"
#include "terminal.h"
#include "fileIO.h"
#include "printMaze.h"

int* edit_player(char command, int player[2], char** maze){/* function to edit the coordinates of the player according to the command inputed*/
    int next[2]; /* int array to calculate the new coordinates of the player due to the input command*/
    if(command == 'w'){/* these set of if/else if statements check if the next coordinates are actually free for the player*/
        next[0] = player[0] -1; /*to move if they are then the actualy player coordinates are edited if not then they remain the same*/
        next[1] = player[1];
        if (maze[next[0]][next[1]]== ' ' ||maze[next[0]][next[1]]== 'x'){ /* conditional statement saying that if the next cooridnates are a space of the x then update the player[2]*/
            player[0] = next[0]; 
            player[1]= next[1];
        }
    }
    else if(command == 'a'){
        next[0] = player[0];/* each command makes the next[2] according to the command using the old player coordinates*/
        next[1] = player[1]-1;
        if (maze[next[0]][next[1]]== ' ' ||maze[next[0]][next[1]]== 'x'){
            player[0] = next[0];/* same condition if next[2] is a free space update the player*/
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
    /* do not need an else statement because if a command is not recognised its filtered in the main()*/
    return player;
}
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

Llist* addMove(Llist* moves, int player[2], int snake[2], char command){/* this funciton adds a new move to the linked list so it can be read by the edit maze function and the maze ca be updated*/
    int int_command = (int)command; /* ASCII of the command character is stored as the comnand to know which command was put in last*/
    int* array = (int*)malloc(sizeof(int)*5); /* the data stored in the data feild of each listNd is a an int array*/
    array[0]= player[0];/* this data array stores the latest snake, plaer coordinates and the ASCII of the command that updates them*/
    array[1]= player[1];
    array[2] = snake[0];
    array[3] = snake[1];
    array[4]= int_command;
    void* data = (void*)array;/* type cast to void* as it is a generic linkeList*/
    insertStart(moves, data);/*every new move is added to the start of the linked list as so the latest moves are on the front of the movesList*/
    return moves;  /* updated linked list returned*/
}
char** editMaze(char** maze, Llist* moves, int row, int col, int player[2], int goal[2], int snake[2], char* fileName){
    int i,j;/*varialble for for loop*/
    for( i = 0; i < row; ++i){  /* this for loop iterates over the maze and clears the past symbols of player and snake so the new ones can be read in from the linked list and printed*/
            for( j =0; j < col; ++j){
                if (maze[i][j]== 'v' || maze[i][j]== '<' || maze[i][j]== '>' || maze[i][j]== '^' ||  maze[i][j]== '~'){
                    maze[i][j] = ' ';
                }
            }
    }
    if (moves->size == 0){/* if the movesList(linkedList) is empty which means if someone tries to undo first move it just prints the initial map*/
        printf("Start of the game reached \n"); /* prints a message*/
        maze = fileIO(&row, &col, player, goal, snake, fileName);
        return maze;/*the maze is just the original maze read from the input file*/ 
    }
    else{
        listNd* newMove = moves->head; /*since the maze the pointer points to has been wiped of its snake and player symbols*/
        listNd* oldmove = newMove->next;
        int* data = (int*)newMove->data;/* make newNode a pointer to the most recent snake and player data, extract the most recent 2d data array*/
        int player_x = data[0]; /* find new player coordinates*/
        int player_y = data[1];
        int snake_x = data[2];/* find new snake coordinates*/
        int snake_y = data[3];
        int type = data[4];/* type is the ascii representation of the command that was inputted which made those coordinates in this data arrat, if we know type we know which icon to use for the play icon*/
        
        maze[snake_x][snake_y] = '~';/* the snake is put on the maze*/
        if(type == 97){ /* this loop puts in an icon on the map according to the command*/
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
        return maze;
    }

}
Llist* undoList(char** maze, Llist* moves, int row, int col, int player[2], int goal[2], int snake[2], char* fileName){
    /* this is a funciton which is called only when the command 'u' is pressed it removes the front most move(listNd) in the movesList(linkedList)*/
    if(moves->size == 1){ /* if the moves list only has one move then the maze is reverted to its initial form from the map.txt file*/
        removeStart(moves);/* removes the front moves so that the linkedList is empty*/
        maze = fileIO(&row, &col, player, goal, snake, fileName);/* gets the initial maze from the fielIO funciton*/
    }
    else if(moves->size == 0){/* if the linkedList is already empty then we return the initial maze once again*/
        maze = fileIO(&row, &col, player, goal, snake, fileName);
    }
    else{/* if there are more than one move in the linked list then we remove the most latest move and we make the player and the snake coordinates equal to the new front of the lsit*/
        removeStart(moves);/* removes the latest move*/
        listNd* newNode = moves->head;/* the head of the linkedList is now what used to be the second move before the front was removed*/
        int* data = (int*)newNode->data;/* the data from the new head listNd is exrtracted*/
        player[0] = data[0]; /*player coordinates are updated with the old data*/
        player[1] = data[1];
        snake[0] = data[2];/*snake coordinates are updated with the old data*/
        snake[1] = data[3];
    }
    return moves; /* updated linked list is returned*/
}


int main(int argc, char* argv[]){
    char* fileName; /* fileNAme pointer - FREED*/
    int* player; /* pointer for the player coordinates - FREED*/
    int* snake;/* pointer for the snake coordinates - FREED*/
    int i; /* iterative variable*/
    int* goal;/* pointer for the goal coordinates - FREED*/
    char command; /* char for storing the input command*/
    int go = 1; /* as long as go == 1 the game will keep going on */
    int row, col;/* integers to store the row and column specifiactions of the maze from the input file*/
    char ** maze;/* char double pointer to point to the maze at every point of the game*/
    Llist* movesList = createLlist();/* creates the movesList whicch will store all the moves in the game*/
    player =(int*)malloc(sizeof(int)*2); /* allocate 2 integers memort to store all the coordinates of the snake, player , goal*/
    goal =(int*)malloc(sizeof(int)*2);
    snake =(int*)malloc(sizeof(int)*2);
    if(argc != 2){/* if not file name given*/
        printf("PLEASE GIVE THE FILENAME FOR THE INPUT FILE");
    }
    else if(argc == 2){/* a fileName is given*/
        fileName = argv[1]; 
        maze = fileIO(&row, &col, player, goal ,snake,fileName); /* the initial maze from the text file and make the maze char ** point to it*/
        system("clear");/* clear the screen*/
        disableBuffer();/* disable the buffer so commands can be given without Enter*/
        while(go ==1){/* as long as go == 1 the game will go on*/
            printmaze(maze, row, col);/* print the initial maze*/
            scanf(" %c", &command);/* scan commands from the stdin*/
            if( command != 'a' && command !='w' && command != 's' && command != 'd' && command != 'u'){
                /* if the command inputted isn't w,a,s,d, or u print an error message*/
                printf("\n Please provide the correct input, %c is not accepted\n", command);
            }
            else if(command != 'u'){
                /* if the command is w,a,s or d*/
                player = edit_player(command, player, maze); /*edit the player coordinates according to the command using the edit_player()*/
                snake = snakeAlgo(player,snake, maze); /* edit the snake coordinates according the new player coordinates, using the snakeAlgo()*/
                movesList = addMove(movesList, player, snake, command); /*add the new move to the front of the moves list as a listNd with the data field being an int array*/
                maze = editMaze(maze, movesList, row, col, player, goal, snake, fileName);/*edit the maze to update the place of the snake and the player icons by reading the first node of the movesList*/
                system("clear");
                /* clear the screen*/
            }
            else{/* if the command inputted from stdin is 'u' so the last move needs to be undone*/
                movesList = undoList(maze, movesList, row, col, player, goal, snake, fileName);/* use the undoList() to take the latest move out of the movesList*/
                maze = editMaze(maze, movesList, row, col, player, goal, snake, fileName);/*edit the maze by reading the new first node of the movesList*/
                system("clear"); /*clear the screen*/
            }
            if (player[0] == goal[0] && player[1] == goal[1]){/* checks if the player has reached the goal*/
                go = 2; /*means you won*/
            }
            else if (snake[0] == player[0] && snake[1] == player[1]){/* checks if the snake reached the player*/
                go = 0; /* you lost*/
            }
        }
        enableBuffer();/* buffer enabled again*/
        if(go == 2){/* if you exit the while loop with go == 2 that means you won*/
            printf("YOU WON YAYAYAYAYAY!!!!!");
        }
        else if (go == 0){ /* if you exit the while loop with g ==0, means the snake caught you*/
            printf("YOU LOST THE SNAKE ATE YOU");
        }
        /*section for freeeing all the pointers being used in the main function*/
        free(player);
        free(snake);
        free(goal);
        free(maze);
        goal= NULL;
        fileName = NULL;
        player= NULL;
        snake = NULL;
        maze = NULL;
        freeLlist(movesList, &freeNd);
        movesList = NULL;
    }
    return 0;
}