#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
void disableBuffer()
{
    struct termios mode;

    tcgetattr(0, &mode);
    mode.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(0, TCSANOW, &mode);
}
void enableBuffer()
{
    struct termios mode;

    tcgetattr(0, &mode);
    mode.c_lflag |= (ECHO | ICANON);
    tcsetattr(0, TCSANOW, &mode);
}

int main(void){
    int i;
    disableBuffer();
    char command;
    for(i = 0; i<5; ++i){
        sscanf("%c", &command);
        printf("%d",(int)command);
    }
    enableBuffer();
    return 0;
}
