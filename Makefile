# Makefile Variables
CC       = gcc
EXEC     = program
CFLAGS = -Wall -ansi -pedantic
OBJ      = main.o editSnake.o terminal.o editPlayer.o printMaze.o fileIO.o linkedlist.o
# Add FANCY to the CFLAGS and recompile the program

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o : main.c editSnake.h terminal.h printMaze.h linkedlist.h editPlayer.h fileIO.h
	$(CC) $(CFLAGS) main.c -c 

editPlayer.o : editPlayer.c editPlayer.h
	$(CC) $(CFLAGS) editPlayer.c -c

editSnake.o : editSnake.c editSnake.h
	$(CC) $(CFLAGS) editSnake.c -c

terminal.o : terminal.c terminal.h
	$(CC) $(CFLAGS) terminal.c -c

fileIO.o : fileIO.c fileIO.h
	$(CC) $(CFLAGS) fileIO.c -c	

printMaze.o : printMaze.c printMaze.h
	$(CC) $(CFLAGS) printMaze.c -c

linkedlist.o : linkedlist.c linkedlist.h
	$(CC) $(CFLAGS) linkedlist.c -c

clean:
	rm -f $(EXEC) $(OBJ)
