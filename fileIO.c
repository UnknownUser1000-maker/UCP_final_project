#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include "fileIO.h"
char** fileIO(int* row, int*col, int player[2], int goal[2], int snake[2],  char* fileName){
    int amount, mapRow, mapCol, Nread; /* variables to store the specifications of the maze read from test file*/
    int i, j; /* iterative variables*/
    char** actualMap; /* ponter that will point to the actual intial maze*/
    int x_coor, y_coor, type; 
    FILE* input = fopen(fileName, "r"); /* file pointer initialised*/
    if(input == NULL){ /* Error handling in opening the file - SIMPLE*/
        perror("Error opening 'file.txt'");
    }
    /* the error checking and opening of file is done */
    Nread = fscanf(input, "%d %d %d", &amount, &mapRow, &mapCol); /*reading frst line of the input file to get row, column and total items data*/
    if(Nread != 3){ /* simple error handing in reading the file*/
        printf("Error reading the input");
    }
    /*reading of the file for metadata started */
    *col = mapCol; /* col and row are int pointers which take the amount of row and column data to the main so it can be used in other funcitons such as printing maze*/
    *row = mapRow;
    actualMap = (char **)malloc(sizeof(char*)*mapRow); /* Malloced and FREED*/
    for(i = 0; i <mapRow;++i){ 
        actualMap[i] = (char*)malloc(sizeof(char)*mapCol); /* making the actual map a 2D char array*/
        for(j =0; j < mapCol; ++j){
            actualMap[i][j]= ' ';/* filling it initially with spaces*/
        }
    }
    actualMap[0][0] = '#';      /* designing the edges and borders of the mazze*/
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
    }                       /* designing finsihed*/
                      
    for(i=0; i<amount; ++i){/* reading of each line started from the input file*/
        Nread = fscanf(input, "%d %d %d", &x_coor, &y_coor, &type);
        if(Nread != 3){
            printf("Error reading the input, check input file format");/* simple error handling in reading file*/
        }
        if (type == 0){/* the function edits the maze as it reads the file to avoid extra complexity and only have one iterative loop in O(n) time*/
            actualMap[x_coor][y_coor] = '^';/* if type is 0 then its the player and inserting the ^ icon at the coodinates*/
            player[1] = y_coor;/*storing the player coordinates in the player array for while loop in the main*/
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
    fclose(input);
    input= NULL;
    return actualMap;
}