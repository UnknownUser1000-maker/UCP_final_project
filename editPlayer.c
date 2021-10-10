#include <stdio.h>
#include <stdlib.h>
#include "editPlayer.h"
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
